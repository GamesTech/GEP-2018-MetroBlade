#include "pch.h"

#include <functional>
#include "RenderData.h"
#include "UISprite.h"
#include "LobbySystem.h"

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

void UISprite::setSprite(std::string filename, std::string fighter)
{
	src_rect = std::make_shared<RECT>();
	sprite = new Sprite(false);
	sprite->setSpriteRECT(src_rect);
	sprite->setSpriteAnimationFile(filename);
	sprite->setAnimationState(fighter);
	object_components.addComponent(sprite);
	sprite = object_components.getComponentByType<Sprite>();
}


void UISprite::changeSpriteRect(std::string filename, std::string fighter)
{
	sprite->setAnimationState(fighter);
}


void UISprite::onCollision(MetroBrawlCollisionData col_data)
{
	interact = true;
}

void UISprite::Tick(GameStateData * _GSD)
{
	col->tickComponent(_GSD);
	col->setBoxOrigin(render_position);

	if (sprite != nullptr)
	{
		sprite->tickComponent(_GSD);
	}
}

void UISprite::Render(RenderData * _RD)
{
	Vector2 viewport = _RD->m_cam->get2DViewport();
	 render_position = Vector2(canvas_position.x * viewport.x, canvas_position.y * viewport.y);

	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(resource_number), GetTextureSize(texture.Get()), render_position, src_rect.get());
}


