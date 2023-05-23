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
	AllStage.resize(LevelSize);

	CreateTile(GameEngineCore::GetCurLevel(), TileDeg::Start);
	
}

void EditGui::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{


	ImGui::BeginListBox("LevelSelect",ImVec2(80,90));
	for (int i = 0; i < LevelSize; i++)
	{	
		std::string text ="Level " + GameEngineString::ToString(i+1);
		if (ImGui::Button(text.c_str()))
		{
		}
	}
	ImGui::EndListBox();
	
	
	
	if (ImGui::Button("Start"))
	{
	}
	ImGui::SameLine();
	if (ImGui::Button("180"))
	{
		CreateTile(Level, TileDeg::Deg180);
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
	std::shared_ptr<Tiles> Tile = Level->CreateActor<Tiles>();
	Tile->CreateTile(_Deg);
	//Tile->GetTransform()->SetLocalPosition(GameEngineInput::GetMousePosition());
}

