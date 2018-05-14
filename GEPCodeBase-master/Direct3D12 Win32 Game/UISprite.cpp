#include "pch.h"

#include "RenderData.h"
#include "UISprite.h"
#include "LobbySystem.h"

UISprite::UISprite(std::string filename, RenderData* _RD)
{
	//object_components.addComponent(new LobbySystemComponent);

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../DDS/" + filename + ".dds";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	ResourceUploadBatch resourceUpload(_RD->m_d3dDevice.Get());

	resourceUpload.Begin();

	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_RD->m_d3dDevice.Get(), resourceUpload, wFilename.c_str(),
			texture.ReleaseAndGetAddressOf()));


	CreateShaderResourceView(_RD->m_d3dDevice.Get(), texture.Get(),
		_RD->m_resourceDescriptors->GetCpuHandle(resource_number = _RD->m_resourceCount++));

	auto uploadResourcesFinished = resourceUpload.End(_RD->m_commandQueue.Get());

	uploadResourcesFinished.wait();
}

void UISprite::Tick(GameStateData * _GSD)
{

}

void UISprite::Render(RenderData * _RD)
{
	Vector2 viewport = _RD->m_cam->get2DViewport();
	 render_position = Vector2(canvas_position.x * viewport.x, canvas_position.y * viewport.y);

	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(resource_number), GetTextureSize(texture.Get()), render_position, src_rect.get());
}
