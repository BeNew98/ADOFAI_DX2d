#include "PrecompileHeader.h"
#include "EditLevel.h"
#include "EditGui.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tiles.h"
EditLevel::EditLevel() 
{
}

EditLevel::~EditLevel() 
{
}

void EditLevel::Start()
{
	std::shared_ptr<Tiles> TileEdit = CreateActor<Tiles>();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}

void EditLevel::Update(float _Deltatime)
{
	if (GameEngineInput::IsDown("TitleLevel"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsDown("PlayLevel"))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (GameEngineInput::IsDown("CenterLevel"))
	{
		GameEngineCore::ChangeLevel("CenterLevel");
	}
}

void EditLevel::LevelChangeStart()
{
	if (nullptr == GameEngineGUI::FindGUIWindow("LevelEdit"))
	{
		std::shared_ptr<GameEngineGUIWindow> NewWindow = GameEngineGUI::GUIWindowCreate<EditGui>("LevelEdit");
		m_pEditor = std::dynamic_pointer_cast<EditGui>(NewWindow);
	}

	m_pEditor->On();
}

void EditLevel::LevelChangeEnd()
{
	m_pEditor->Off();
}

