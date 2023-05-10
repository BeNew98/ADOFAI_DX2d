#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "TitleLogo.h"
#include "BlackScreen.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}


void TitleLevel::Update(float _DeltaTime)
{
}

void TitleLevel::Start()
{
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


	
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<BlackScreen> pBlackScreen = CreateActor<BlackScreen>(0);
	pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });

	std::shared_ptr<GameEngineSpriteRenderer> pStar0 = pBlackScreen->CreateComponent<GameEngineSpriteRenderer>();
	pStar0->SetScaleToTexture("starfields1.png");

	std::shared_ptr<GameEngineSpriteRenderer> pStar1 = pBlackScreen->CreateComponent<GameEngineSpriteRenderer>();
	pStar0->SetScaleToTexture("starfields2.png");

	std::shared_ptr<TitleLogo> pLogo = CreateActor<TitleLogo>(0);
	pLogo->GetTransform()->SetLocalPosition({ 0.f,200.f,0.f });


	std::shared_ptr<Player> pPlayer = CreateActor<Player>(0);
	pPlayer->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });
}

void TitleLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
}

void TitleLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
}

