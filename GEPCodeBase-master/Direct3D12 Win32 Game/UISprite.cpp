#include "pch.h"

#include <functional>
#include "RenderData.h"
#include "UISprite.h"

UISprite::UISprite(std::string filename, RenderData* _RD)
{
	using namespace std::placeholders;

	col = new Collider(m_pos, Vector2(100, 100), true);
	

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../DDS/" + filename + ".dds";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	ResourceUploadBatch resourceUpload(_RD->m_d3dDevice.Get());

	col->isColliderImmediate(true);
	col->addParentObjectRefrence(this);

	col->assignCollisionEvent(std::bind(&UISprite::onCollision, this, _1));

	object_components.addComponent(col);

	resourceUpload.Begin();

	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_RD->m_d3dDevice.Get(), resourceUpload, wFilename.c_str(),
			texture.ReleaseAndGetAddressOf()));

	CreateShaderResourceView(_RD->m_d3dDevice.Get(), texture.Get(),
		_RD->m_resourceDescriptors->GetCpuHandle(resource_number = _RD->m_resourceCount++));

	auto uploadResourcesFinished = resourceUpload.End(_RD->m_commandQueue.Get());

	uploadResourcesFinished.wait();

	
}

void UISprite::onCollision(MetroBrawlCollisionData col_data)
{
	interact = true;
}

void UISprite::Tick(GameStateData * _GSD)
{
	col->tickComponent(_GSD);
	col->setBoxOrigin(m_pos);
}

void UISprite::Render(RenderData * _RD)
{
	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(resource_number), GetTextureSize(texture.Get()), m_pos, src_rect.get());
}


