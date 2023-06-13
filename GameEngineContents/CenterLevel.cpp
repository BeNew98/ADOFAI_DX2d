#include "PrecompileHeader.h"
#include "CenterLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "EditGui.h"
#include "TestScreen.h"
#include "TestObject.h"

CenterLevel::CenterLevel() 
{
}

CenterLevel::~CenterLevel() 
{
}

void CenterLevel::Start()
{
	GameEngineInput::CreateKey("TitleLevel", '1');
	GameEngineInput::CreateKey("PlayLevel", '2');
	GameEngineInput::CreateKey("EditLevel", '3');
	GameEngineInput::CreateKey("CenterLevel", '4');

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");


		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		std::shared_ptr<TestScreen> render = CreateActor<TestScreen>();
	}

	{
		std::shared_ptr<TestObject> render = CreateActor<TestObject>();
		render->GetTransform()->AddLocalPosition({-500.f,0.f});
	} 
	{
		std::shared_ptr<TestObject> render = CreateActor<TestObject>();
		render->GetTransform()->AddLocalPosition({ 500.f,0.f });
	}


}


void CenterLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("TitleLevel"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsDown("PlayLevel"))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
		EditGui::Editor->SetLevel(1);
	}

	if (GameEngineInput::IsDown("EditLevel"))
	{
		GameEngineCore::ChangeLevel("EditLevel");
	}
}

