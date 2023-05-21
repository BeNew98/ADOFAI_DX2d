#include "PrecompileHeader.h"
#include "EditGui.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
}

void EditGui::OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
	if (Tile = nullptr)
	{
		Tile = Level->CreateActor<Tiles>();
	}


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
	}
	ImGui::SameLine();
	if (ImGui::Button("90"))
	{
	}
	ImGui::SameLine();
	if (ImGui::Button("270"))
	{
	}


	
}

