#include "PrecompileHeader.h"
#include "EditLevel.h"
#include "EditGui.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tiles.h"
#include "MyMouse.h"

EditLevel::EditLevel() 
{
}

EditLevel::~EditLevel() 
{
}

void EditLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	if (nullptr == GameEngineGUI::FindGUIWindow("LevelEdit"))
	{
		std::shared_ptr<GameEngineGUIWindow> NewWindow = GameEngineGUI::GUIWindowCreate<EditGui>("LevelEdit");
		m_pEditor = std::dynamic_pointer_cast<EditGui>(NewWindow);
	}
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
	
	//if (GameEngineInput::IsDown("CenterLevel"))
	//{
	//	GameEngineCore::ChangeLevel("CenterLevel");
	//}

	if (ImGui::IsMouseDragging(1))
	{
		float4 CurMousePos = GameEngineInput::GetMouseDirection();
		CurMousePos.y = -CurMousePos.y;
		GetMainCamera()->GetTransform()->AddWorldPosition(-CurMousePos);
	}

}

void EditLevel::LevelChangeStart()
{


	m_pEditor->On();

	m_pMouse = CreateActor<MyMouse>();
}

void EditLevel::LevelChangeEnd()
{
	m_pEditor->Off();
}

