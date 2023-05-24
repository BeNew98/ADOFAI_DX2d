#include "PrecompileHeader.h"
#include "EditGui.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Tiles.h"
#include "EditLevel.h"

EditGui::EditGui() 
{
}

EditGui::~EditGui() 
{
}

void EditGui::Start()
{
	AllStage.resize(m_LevelSize);
	for (size_t i = 0; i < AllStage.size(); i++)
	{
		AllStage[i].AllTile.resize(200);
	}
	
}

void EditGui::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{


	ImGui::BeginListBox("LevelSelect",ImVec2(80,90));
	for (int i = 0; i < m_LevelSize; i++)
	{	
		std::string text ="Level " + GameEngineString::ToString(i+1);
		if (ImGui::Button(text.c_str()))
		{
			m_CurLevel = i;
		}
	}
	ImGui::EndListBox();
	
	
	if (ImGui::Button("0"))
	{
		CreateTile(Level, TileDeg::Deg0);
	}
	ImGui::SameLine();
	if (ImGui::Button("90"))
	{
		CreateTile(Level, TileDeg::Deg90);
	}
	ImGui::SameLine();
	if (ImGui::Button("270"))
	{
		CreateTile(Level, TileDeg::Deg270);
	}


	
}

void EditGui::CreateTile(std::shared_ptr<class GameEngineLevel> Level, TileDeg _Deg)
{
	std::shared_ptr<Tiles> pTile = Level->CreateActor<Tiles>();
	pTile->CreateTile(_Deg);
	int iDeg = static_cast<int>(_Deg);

	int m_CurTileSize = AllStage[m_CurLevel].TileSize;
	if (m_CurTileSize != 0)
	{
		std::shared_ptr<Tiles> PrevTile = AllStage[m_CurLevel].AllTile[m_CurTileSize - 1].Tile;
		

		float PrevTileScale = PrevTile->GetRender()->GetTransform()->GetLocalScale().hx();
		float CurTileScale = pTile->GetRender()->GetTransform()->GetLocalScale().hx();
		float AddScale = fabs(PrevTileScale) + fabs(CurTileScale);

		pTile->GetTransform()->SetLocalPosition(AllStage[m_CurLevel].AllTile[m_CurTileSize - 1].Position);
		pTile->GetTransform()->SetLocalRotation({ 0.f,0.f,static_cast<float>(m_CurDegree) });
		switch (m_CurDegree)
		{
		case 0:
			pTile->GetTransform()->AddLocalPosition(float4{ AddScale, 0.f ,0.f });
			break;
		case 90:

			pTile->GetTransform()->AddLocalPosition(float4{ 0.f,  AddScale,0.f });
			break;
		case 180:
			pTile->GetTransform()->AddLocalPosition(float4{ -AddScale, 0.f ,0.f });
			break;
		case 270:
			pTile->GetTransform()->AddLocalPosition(float4{ 0.f,  -AddScale,0.f });
			break;
		default:
			break;
		}

		m_CurDegree += iDeg;

		if (m_CurDegree >=360)
		{
			m_CurDegree -= 360;
		}
	}

	AllStage[m_CurLevel].AllTile[m_CurTileSize].NextRatio = static_cast<float>(iDeg);

	AllStage[m_CurLevel].AllTile[m_CurTileSize].Tile = pTile;
	AllStage[m_CurLevel].AllTile[m_CurTileSize].Position = pTile->GetTransform()->GetWorldPosition();
	++AllStage[m_CurLevel].TileSize;
}

