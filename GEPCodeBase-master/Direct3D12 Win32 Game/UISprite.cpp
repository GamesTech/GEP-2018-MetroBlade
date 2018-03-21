#include "pch.h"

#include "RenderData.h"
#include "UISprite.h"

UISprite::UISprite(std::string filename, RenderData* _RD)
{
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
	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(resource_number), GetTextureSize(texture.Get()), m_pos, src_rect.get());
}
