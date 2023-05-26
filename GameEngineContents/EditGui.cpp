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

	ImGui::BeginListBox("LevelSelect", ImVec2(60, static_cast<float>(m_LevelSize * 30)));
	for (int i = 0; i < m_LevelSize; i++)
	{	
		std::string text ="Level " + GameEngineString::ToString(i+1);
		if (ImGui::Button(text.c_str()))
		{
			m_CurLevel = i;
		}
	}
	ImGui::EndListBox();


	{
		std::string text ="CurDegree "+ GameEngineString::ToString(m_CurDegree);
			ImGui::Text(text.c_str());
	}

	if (ImGui::Button("0"))
	{
		CreateTile(Level, TileDeg::Deg0);
	}
	if (ImGui::Button("45"))
	{
		CreateTile(Level, TileDeg::Deg45);
	}
	if (ImGui::Button("60"))
	{
		CreateTile(Level, TileDeg::Deg60);
	}
	if (ImGui::Button("90"))
	{
		CreateTile(Level, TileDeg::Deg90);
	}
	if (ImGui::Button("120"))
	{
		CreateTile(Level, TileDeg::Deg120);
	}
	if (ImGui::Button("135"))
	{
		CreateTile(Level, TileDeg::Deg135);
	}
	if (ImGui::Button("225"))
	{
		CreateTile(Level, TileDeg::Deg225);
	}
	if (ImGui::Button("240"))
	{
		CreateTile(Level, TileDeg::Deg240);
	}
	if (ImGui::Button("270"))
	{
		CreateTile(Level, TileDeg::Deg270);
	}
	if (ImGui::Button("300"))
	{
		CreateTile(Level, TileDeg::Deg300);
	}
	if (ImGui::Button("310"))
	{
		CreateTile(Level, TileDeg::Deg315);
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
		//이전 타일
		std::shared_ptr<Tiles> PrevTile = AllStage[m_CurLevel].AllTile[m_CurTileSize - 1].Tile;

		{
			float4 PrevTilePos = AllStage[m_CurLevel].AllTile[m_CurTileSize - 1].Position;
			//float PrevTileScale = PrevTile->GetRender()->GetTransform()->GetLocalScale().hx();
			//float CurTileScale = pTile->GetRender()->GetTransform()->GetLocalScale().hx();
			//float AddScale = fabs(PrevTileScale) + fabs(CurTileScale);

			//현재 타일을 이전타일의 위치로 이동
			//pTile->GetTransform()->SetLocalPosition(PrevTilePos);
			//현재까지의 각도로 회전
			pTile->GetTransform()->SetLocalRotation({ 0.f,0.f,static_cast<float>(m_CurDegree) });

		
			//현재 타일의 세팅 위치를 가져오기
			//float4 CurSettingPos = float4{ static_cast<float>(AddScale),0.f,0.f,1.f };
			//CurSettingPos.RotaitonZDeg(m_CurDegree);
			//pTile->GetTransform()->AddLocalPosition(CurSettingPos);
		}
		float4 PrevEndPivot = PrevTile->m_fEndPivot;
		float4 CurStartPivot = pTile->m_fStartPivot;
		float4 CurBetweenPivot = pTile->m_fEndPivot- pTile->m_fStartPivot;

		pTile->m_fStartPivot = PrevEndPivot;

		float4 PivotDistance = pTile->m_fStartPivot - CurStartPivot;



		pTile->m_fEndPivot = (pTile->m_fStartPivot + CurBetweenPivot).RotaitonZDegReturn(m_CurDegree);
		pTile->GetTransform()->SetLocalPosition(PivotDistance);
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
	Level->GetMainCamera()->GetTransform()->SetWorldPosition(pTile->GetTransform()->GetWorldPosition());
}

