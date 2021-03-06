//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "Scene.h"

#include "SpriteAnimFileReader.h"

#include "UILabel.h"
#include "UISprite.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game() :
	m_window(nullptr),
	m_outputWidth(1920),
	m_outputHeight(1080),
	m_featureLevel(D3D_FEATURE_LEVEL_11_0),
	m_backBufferIndex(0),
	m_fenceValues{}
{
}

Game::~Game()
{
	if (m_audEngine)
	{
		m_audEngine->Suspend();
	}

	// Ensure that the GPU is no longer referencing resources that are about to be destroyed.
	WaitForGpu();

	// delete the scene and clear the memory.
	scene.clearScene();

	//delete the sounds
	for (vector<Sound *>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		delete (*it);
	}
	m_sounds.clear();

	delete m_RD;
	delete m_GSD;

	m_keyboard.reset();
	m_mouse.reset();

	m_graphicsMemory.reset();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_window = window;
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateDevice();
	CreateResources();

	//GEP::init Audio System
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audEngine = std::make_unique<AudioEngine>(eflags);

	m_GSD = new GameStateData;

//GEP::set up keyboard & mouse input systems
	m_inputManager.reset(new InputManager);
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window); // mouse device needs to linked to this program's window
	m_mouse->SetMode(Mouse::Mode::MODE_RELATIVE); // gives a delta postion as opposed to a MODE_ABSOLUTE position in 2-D space
	//m_gamePad = std::make_unique<DirectX::GamePad>();
	m_RD = new RenderData;

	m_RD->m_d3dDevice = m_d3dDevice;
	m_RD->m_commandQueue = m_commandQueue;
	m_RD->m_commandList = m_commandList;

	m_RD->m_resourceDescriptors = std::make_unique<DescriptorHeap>(m_d3dDevice.Get(),
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
		1000);

	//stuff for SDKMeshGO3D renderer
	m_RD->m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	ResourceUploadBatch resourceUpload(m_d3dDevice.Get());

	resourceUpload.Begin();
	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);

	SpriteBatchPipelineStateDescription pd(rtState);
	pd.blendDesc = m_RD->m_states->NonPremultiplied;
	m_RD->m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dDevice.Get(), resourceUpload, pd);
	m_RD->m_font = std::make_unique<SpriteFont>(m_d3dDevice.Get(), resourceUpload,
		L"courier.spritefont",
		m_RD->m_resourceDescriptors->GetCpuHandle(m_RD->m_resourceCount),
		m_RD->m_resourceDescriptors->GetGpuHandle(m_RD->m_resourceCount));
	m_RD->m_resourceCount++;

	auto uploadResourcesFinished = resourceUpload.End(m_commandQueue.Get());

	D3D12_VIEWPORT viewport = { 0.0f, 0.0f,
		static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight),
		D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
	m_RD->m_spriteBatch->SetViewport(viewport);

	m_RD->m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dDevice.Get());

	EffectPipelineStateDescription pd2(
		&VertexPositionColor::InputLayout,
		CommonStates::Opaque,
		CommonStates::DepthDefault,
		CommonStates::CullNone,
		rtState);

	m_RD->m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get(), EffectFlags::VertexColor, pd2);

	EffectPipelineStateDescription pd3(
		&GeometricPrimitive::VertexType::InputLayout,
		CommonStates::Opaque,
		CommonStates::DepthDefault,
		CommonStates::CullNone,
		rtState);
	m_RD->m_GPeffect = std::make_unique<BasicEffect>(m_d3dDevice.Get(), EffectFlags::Lighting, pd3);
	m_RD->m_GPeffect->EnableDefaultLighting();

	scene.assignRenderData(m_RD);
	scene.Init();
	//objectList.reserve(20);
	collider.init();


	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	//GEP::This is where I am creating the test objects
	Loop *loop = new Loop(m_audEngine.get(), "NightAmbienceSimple_02");
	loop->SetVolume(0.1f);
	loop->Play();
	m_sounds.push_back(loop);

	/*TestSound* TS = new TestSound(m_audEngine.get(), "Explo1");
	m_sounds.push_back(TS);*/
}

//GEP:: Executes the basic game loop.
void Game::Tick()
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	Render();
}

//GEP:: Updates all the Game Object Structures
void Game::Update(DX::StepTimer const& timer)
{
	if (scene.shouldQuit())
	{
		PostQuitMessage(0);
	}

	ReadInput();
	m_GSD->m_dt = float(timer.GetElapsedSeconds());

	//this will update the audio engine but give us chance to do somehting else if that isn't working
	if (!m_audEngine->Update())
	{
		if (m_audEngine->IsCriticalError())
		{
			// We lost the audio device!
		}
	}
	else
	{
		//update sounds playing
		for (vector<Sound *>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
		{
			(*it)->Tick(m_GSD);
		}
	}

	if (m_keyboard->GetState().P)
	{
		m_player_objects.clear();
		m_obstacle_objects.clear();
		collider.reset();
		Scene*  newScene = new Scene;
		scene.loadScene(newScene);


		Camera* camera = new Camera(static_cast<float>(800), static_cast<float>(600), 1.0f, 1000.0f);
		camera->set2DViewport(Vector2(m_outputWidth, m_outputHeight));
		scene.setMainCamera(camera);
		scene.instanciate3DObject(camera);
		//m_3DObjects.push_back(camera);

		Player2D* testPlay = new Player2D(m_RD, "Fighter_1", 0);
		testPlay->SetDrive(1000.0f);
		testPlay->SetDrag(0.5f);
		testPlay->getCollider(0)->setTag(m_player_objects.size());
		testPlay->getCollider(1)->setTag(m_player_objects.size());
		collider.addCollider((testPlay->getCollider(0)));
		collider.addCollider((testPlay->getCollider(1)));
		testPlay->SetPos(Vector2(1500, 200));
		scene.instanciate2DObject(testPlay);
		m_player_objects.push_back(testPlay);

		Player2D* testPlay2 = new Player2D(m_RD, "Fighter_2", 1);
		testPlay2->SetDrive(1000.0f);
		testPlay2->SetDrag(0.5f);
		
		testPlay2->getCollider(0)->setTag(m_player_objects.size());
		testPlay2->getCollider(1)->setTag(m_player_objects.size());
		collider.addCollider((testPlay2->getCollider(1)));
		collider.addCollider((testPlay2->getCollider(0)));
		testPlay2->SetPos(Vector2(800, 200));
		scene.instanciate2DObject(testPlay2);
		m_player_objects.push_back(testPlay2);

		Player2D* testPlay3 = new Player2D(m_RD, "Fighter_3", 2);
		testPlay3->SetDrive(1000.0f);
		testPlay3->SetDrag(0.5f);
		testPlay3->getCollider(0)->setTag(m_player_objects.size());
		testPlay3->getCollider(1)->setTag(m_player_objects.size());
		collider.addCollider((testPlay3->getCollider(0)));
		collider.addCollider((testPlay3->getCollider(1)));
		testPlay3->SetPos(Vector2(1100, 500));
		scene.instanciate2DObject(testPlay3);
		m_player_objects.push_back(testPlay3);


		Obstacle2D* testPlatform = new Obstacle2D(m_RD, "Platform_Sprite");
		testPlatform->getCollider(0)->setTag(10);
		collider.addCollider((testPlatform->getCollider(0)));
		testPlatform->SetPos(Vector2(500, 600));
		scene.instanciate2DObject(testPlatform);//m_2DObjects.push_back(testPlay);
		m_obstacle_objects.push_back(testPlatform);

		scene.startGameManager();

		UILabel* test_label = new UILabel;
		test_label->setText("Kill your opponents.");
		scene.instanciateUIObject(test_label);

		//UISprite* test_sprite = new UISprite("twist", m_RD);
	//	scene.instanciateUIObject(test_sprite);
	}

	if (m_keyboard->GetState().T)
	{
		// Instantiation test.
		Player2D* testPlay = new Player2D(m_RD, "Fighter_1_ss", 0);
		testPlay->SetDrive(1000.0f);
		testPlay->SetDrag(0.5f);


		testPlay->getCollider(1)->setTag(m_player_objects.size());
		testPlay->getCollider(0)->setTag(m_player_objects.size());
		collider.addCollider((testPlay->getCollider(0)));
		collider.addCollider((testPlay->getCollider(1)));

		testPlay->SetPos(Vector2(0, 500));

		scene.instanciate2DObject(testPlay);//m_2DObjects.push_back(testPlay);
		m_player_objects.push_back(testPlay);

		Obstacle2D* testPlatform = new Obstacle2D(m_RD, "Block");
		testPlatform->getCollider(0)->setTag(10);
		collider.addCollider((testPlatform->getCollider(0)));

		testPlatform->SetPos(Vector2(0,600));

		scene.instanciate2DObject(testPlatform);//m_2DObjects.push_back(testPlay);
		m_obstacle_objects.push_back(testPlatform);

	}
	if (!m_player_objects.empty())
	{
		for (int i = 0; i < collider.GetSize(); i++)
		{
			int collider_tag = collider.checkCollisions(i);

			if (collider_tag != -1)
			{
				if (collider_tag != 10)
				{
					if (!collider.checkTrigger(i))
					{
						m_player_objects[collider_tag]->SetPos(m_player_objects[collider_tag]->GetPos() + collider.colliderOverlap() * 0.01);
						m_player_objects[collider_tag]->SetVelX(Vector2(0, 0));

						
					}
					if (collider.getTarget() == 10)
					{
						m_player_objects[collider_tag]->setStateGrounded();
					}
					
				}
				if (collider.checkTrigger(i) && collider.getTarget() != 10)
				{
					if (m_player_objects[collider_tag]->IsAttacking())
					{
						m_player_objects[collider.getTarget()]->punched(m_GSD, m_player_objects[collider_tag]->getDirection());
					}
					
				}
			}
		}
	}

	scene.Update(m_GSD);
}

//GEP:: Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	// Prepare the command list to render a new frame.
	Clear();

	//draw each type of 3D objects
	scene.Render(m_commandList.Get());

	// Show the new frame.
	Present();
	m_graphicsMemory->Commit(m_commandQueue.Get());
}

// Helper method to prepare the command list for rendering and clear the back buffers.
void Game::Clear()
{
	// Reset command list and allocator.
	DX::ThrowIfFailed(m_commandAllocators[m_backBufferIndex]->Reset());
	DX::ThrowIfFailed(m_commandList->Reset(m_commandAllocators[m_backBufferIndex].Get(), nullptr));

	// Transition the render target into the correct state to allow for drawing into it.
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_commandList->ResourceBarrier(1, &barrier);

	// Clear the views.
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptor(m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), m_backBufferIndex, m_rtvDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvDescriptor(m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	m_commandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);
	m_commandList->ClearRenderTargetView(rtvDescriptor, Colors::CornflowerBlue, 0, nullptr);
	m_commandList->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// Set the viewport and scissor rect.
	D3D12_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
	D3D12_RECT scissorRect = { 0, 0, m_outputWidth, m_outputHeight };
	m_commandList->RSSetViewports(1, &viewport);
	m_commandList->RSSetScissorRects(1, &scissorRect);
}

// Submits the command list to the GPU and presents the back buffer contents to the screen.
void Game::Present()
{
	// Transition the render target to the state that allows it to be presented to the display.
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &barrier);

	// Send the command list off to the GPU for processing.
	DX::ThrowIfFailed(m_commandList->Close());
	m_commandQueue->ExecuteCommandLists(1, CommandListCast(m_commandList.GetAddressOf()));

	// The first argument instructs DXGI to block until VSync, putting the application
	// to sleep until the next VSync. This ensures we don't waste any cycles rendering
	// frames that will never be displayed to the screen.
	WaitForGpu();
	HRESULT hr = m_swapChain->Present(0, 0);

	// If the device was reset we must completely reinitialize the renderer.
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		OnDeviceLost();
	}
	else
	{
		DX::ThrowIfFailed(hr);

		MoveToNextFrame();
	}
}

// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
	m_audEngine->Suspend();
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();
	m_audEngine->Resume();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 1920;
	height = 1080;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
	DWORD dxgiFactoryFlags = 0;

#if defined(_DEBUG)
	// Enable the debug layer (requires the Graphics Tools "optional feature").
	//
	// NOTE: Enabling the debug layer after device creation will invalidate the active device.
	{
		ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
		{
			debugController->EnableDebugLayer();
		}

		ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
		{
			dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

			dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
			dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
		}
	}
#endif

	DX::ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf())));

	ComPtr<IDXGIAdapter1> adapter;
	GetAdapter(adapter.GetAddressOf());

	// Create the DX12 API device object.
	DX::ThrowIfFailed(D3D12CreateDevice(
		adapter.Get(),
		m_featureLevel,
		IID_PPV_ARGS(m_d3dDevice.ReleaseAndGetAddressOf())
	));

#ifndef NDEBUG
	// Configure debug device (if active).
	ComPtr<ID3D12InfoQueue> d3dInfoQueue;
	if (SUCCEEDED(m_d3dDevice.As(&d3dInfoQueue)))
	{
#ifdef _DEBUG
		d3dInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		d3dInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
#endif
		D3D12_MESSAGE_ID hide[] =
		{
			D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
			D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE
		};
		D3D12_INFO_QUEUE_FILTER filter = {};
		filter.DenyList.NumIDs = _countof(hide);
		filter.DenyList.pIDList = hide;
		d3dInfoQueue->AddStorageFilterEntries(&filter);
	}
#endif

	// Create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	DX::ThrowIfFailed(m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf())));

	// Create descriptor heaps for render target views and depth stencil views.
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc = {};
	rtvDescriptorHeapDesc.NumDescriptors = c_swapBufferCount;
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	D3D12_DESCRIPTOR_HEAP_DESC dsvDescriptorHeapDesc = {};
	dsvDescriptorHeapDesc.NumDescriptors = 1;
	dsvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

	DX::ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&rtvDescriptorHeapDesc, IID_PPV_ARGS(m_rtvDescriptorHeap.ReleaseAndGetAddressOf())));
	DX::ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&dsvDescriptorHeapDesc, IID_PPV_ARGS(m_dsvDescriptorHeap.ReleaseAndGetAddressOf())));

	m_rtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// Create a command allocator for each back buffer that will be rendered to.
	for (UINT n = 0; n < c_swapBufferCount; n++)
	{
		DX::ThrowIfFailed(m_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_commandAllocators[n].ReleaseAndGetAddressOf())));
	}

	// Create a command list for recording graphics commands.
	DX::ThrowIfFailed(m_d3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[0].Get(), nullptr, IID_PPV_ARGS(m_commandList.ReleaseAndGetAddressOf())));
	DX::ThrowIfFailed(m_commandList->Close());

	// Create a fence for tracking GPU execution progress.
	DX::ThrowIfFailed(m_d3dDevice->CreateFence(m_fenceValues[m_backBufferIndex], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.ReleaseAndGetAddressOf())));
	m_fenceValues[m_backBufferIndex]++;

	m_fenceEvent.Attach(CreateEvent(nullptr, FALSE, FALSE, nullptr));
	if (!m_fenceEvent.IsValid())
	{
		throw std::exception("CreateEvent");
	}

	// TODO: Initialize device dependent objects here (independent of window size).

	m_graphicsMemory = std::make_unique<GraphicsMemory>(m_d3dDevice.Get());
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
	// Wait until all previous GPU work is complete.
	WaitForGpu();

	// Release resources that are tied to the swap chain and update fence values.
	for (UINT n = 0; n < c_swapBufferCount; n++)
	{
		m_renderTargets[n].Reset();
		m_fenceValues[n] = m_fenceValues[m_backBufferIndex];
	}

	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT;
	UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
	UINT backBufferHeight = static_cast<UINT>(m_outputHeight);

	// If the swap chain already exists, resize it, otherwise create one.
	if (m_swapChain)
	{
		HRESULT hr = m_swapChain->ResizeBuffers(c_swapBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			// If the device was removed for any reason, a new device and swap chain will need to be created.
			OnDeviceLost();

			// Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
			// and correctly set up the new device.
			return;
		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else
	{
		// Create a descriptor for the swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = backBufferFormat;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = c_swapBufferCount;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		// Create a swap chain for the window.
		ComPtr<IDXGISwapChain1> swapChain;
		DX::ThrowIfFailed(m_dxgiFactory->CreateSwapChainForHwnd(
			m_commandQueue.Get(),
			m_window,
			&swapChainDesc,
			&fsSwapChainDesc,
			nullptr,
			swapChain.GetAddressOf()
		));

		DX::ThrowIfFailed(swapChain.As(&m_swapChain));

		// This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut
		DX::ThrowIfFailed(m_dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
	}

	// Obtain the back buffers for this window which will be the final render targets
	// and create render target views for each of them.
	for (UINT n = 0; n < c_swapBufferCount; n++)
	{
		DX::ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(m_renderTargets[n].GetAddressOf())));

		wchar_t name[25] = {};
		swprintf_s(name, L"Render target %u", n);
		m_renderTargets[n]->SetName(name);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptor(m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), n, m_rtvDescriptorSize);
		m_d3dDevice->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvDescriptor);
	}

	// Reset the index to the current back buffer.
	m_backBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	// Allocate a 2-D surface as the depth/stencil buffer and create a depth/stencil view
	// on this surface.
	CD3DX12_HEAP_PROPERTIES depthHeapProperties(D3D12_HEAP_TYPE_DEFAULT);

	D3D12_RESOURCE_DESC depthStencilDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		depthBufferFormat,
		backBufferWidth,
		backBufferHeight,
		1, // This depth stencil view has only one texture.
		1  // Use a single mipmap level.
	);
	depthStencilDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
	depthOptimizedClearValue.Format = depthBufferFormat;
	depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
	depthOptimizedClearValue.DepthStencil.Stencil = 0;

	DX::ThrowIfFailed(m_d3dDevice->CreateCommittedResource(
		&depthHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthOptimizedClearValue,
		IID_PPV_ARGS(m_depthStencil.ReleaseAndGetAddressOf())
	));

	m_depthStencil->SetName(L"Depth stencil");

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = depthBufferFormat;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	m_d3dDevice->CreateDepthStencilView(m_depthStencil.Get(), &dsvDesc, m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
}

void Game::WaitForGpu() noexcept
{
	if (m_commandQueue && m_fence && m_fenceEvent.IsValid())
	{
		// Schedule a Signal command in the GPU queue.
		UINT64 fenceValue = m_fenceValues[m_backBufferIndex];
		if (SUCCEEDED(m_commandQueue->Signal(m_fence.Get(), fenceValue)))
		{
			// Wait until the Signal has been processed.
			if (SUCCEEDED(m_fence->SetEventOnCompletion(fenceValue, m_fenceEvent.Get())))
			{
				WaitForSingleObjectEx(m_fenceEvent.Get(), INFINITE, FALSE);

				// Increment the fence value for the current frame.
				m_fenceValues[m_backBufferIndex]++;
			}
		}
	}
}

void Game::MoveToNextFrame()
{
	// Schedule a Signal command in the queue.
	const UINT64 currentFenceValue = m_fenceValues[m_backBufferIndex];
	DX::ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), currentFenceValue));

	// Update the back buffer index.
	m_backBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	// If the next frame is not ready to be rendered yet, wait until it is ready.
	if (m_fence->GetCompletedValue() < m_fenceValues[m_backBufferIndex])
	{
		DX::ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceValues[m_backBufferIndex], m_fenceEvent.Get()));
		WaitForSingleObjectEx(m_fenceEvent.Get(), INFINITE, FALSE);
	}

	// Set the fence value for the next frame.
	m_fenceValues[m_backBufferIndex] = currentFenceValue + 1;
}

// This method acquires the first available hardware adapter that supports Direct3D 12.
// If no such adapter can be found, try WARP. Otherwise throw an exception.
void Game::GetAdapter(IDXGIAdapter1** ppAdapter)
{
	*ppAdapter = nullptr;

	ComPtr<IDXGIAdapter1> adapter;
	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != m_dxgiFactory->EnumAdapters1(adapterIndex, adapter.ReleaseAndGetAddressOf()); ++adapterIndex)
	{
		DXGI_ADAPTER_DESC1 desc;
		DX::ThrowIfFailed(adapter->GetDesc1(&desc));

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			// Don't select the Basic Render Driver adapter.
			continue;
		}

		// Check to see if the adapter supports Direct3D 12, but don't create the actual device yet.
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), m_featureLevel, _uuidof(ID3D12Device), nullptr)))
		{
			break;
		}
	}

#if !defined(NDEBUG)
	if (!adapter)
	{
		if (FAILED(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(adapter.ReleaseAndGetAddressOf()))))
		{
			throw std::exception("WARP12 not available. Enable the 'Graphics Tools' optional feature");
		}
	}
#endif

	if (!adapter)
	{
		throw std::exception("No Direct3D 12 device found");
	}

	*ppAdapter = adapter.Detach();
}

void Game::OnDeviceLost()
{
	m_RD->m_states.reset();
	//TODO: SDKMeshGO3D
	//m_fxFactory.reset();
	//m_modelResources.reset();
	//m_model.reset();
	//m_modelNormal.clear();

	// TODO: Perform Direct3D resource cleanup.
	m_graphicsMemory.reset();

	m_RD->m_font.reset();
	m_RD->m_resourceDescriptors.reset();
	m_RD->m_spriteBatch.reset();

	m_RD->m_effect.reset();
	m_RD->m_batch.reset();

	//TODO:: m_shape.reset() GPGO3D 
	m_RD->m_GPeffect.reset();

	for (UINT n = 0; n < c_swapBufferCount; n++)
	{
		m_commandAllocators[n].Reset();
		m_renderTargets[n].Reset();
	}

	m_depthStencil.Reset();
	m_fence.Reset();
	m_commandList.Reset();
	m_swapChain.Reset();
	m_rtvDescriptorHeap.Reset();
	m_dsvDescriptorHeap.Reset();
	m_commandQueue.Reset();
	m_d3dDevice.Reset();
	m_dxgiFactory.Reset();

	CreateDevice();
	CreateResources();
}

void Game::ReadInput()
{
	//GEP:: CHeck out the DirectXTK12 wiki for more information about these systems
	//https://github.com/Microsoft/DirectXTK/wiki/Mouse-and-keyboard-input

	//You'll also found similar stuff for Game Controllers here:
	//https://github.com/Microsoft/DirectXTK/wiki/Game-controller-input

	//Note in both cases they are identical to the DirectXTK for DirectX 11

	m_GSD->m_prevKeyboardState = m_GSD->m_keyboardState;
	m_GSD->m_keyboardState = m_keyboard->GetState();
	m_GSD->m_mouseState = m_mouse->GetState();
}
