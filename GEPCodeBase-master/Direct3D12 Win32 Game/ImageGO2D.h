#pragma once
#include <string>
#include "GameObject2D.h"
#include "Collider.h"
using std::string;
struct RenderData;

//GEP:: Builds on the Base Game Object 2D class to allow images to be displayed to screen.
// These need to made into dds format objects which can be done using the Images project in the Asset Pipeline solution folder.
// Based on this part of the DirectXTK12 wiki documentation
//https://github.com/Microsoft/DirectXTK12/wiki/Sprites-and-textures 

class ImageGO2D :
	public GameObject2D
{
public:
	ImageGO2D(RenderData* _RD, string _filename);
	virtual ~ImageGO2D();

	void Tick(GameStateData* _GSD) override;
	void Render(RenderData* _RD) override;

	void CentreOrigin();

protected:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;
	int m_resourceNum = -1;
	std::shared_ptr<RECT>   src_rect;
	int sheet_total = 0;
};

