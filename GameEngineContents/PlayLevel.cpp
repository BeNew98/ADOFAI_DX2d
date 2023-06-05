#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "EditGui.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Update(float _DeltaTime)
{

}

void PlayLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}
void PlayLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	EditGui::Editor->LoadtoString("Level1");

	std::shared_ptr<Player> player = CreateActor<Player>(OrderNum::PLANET);

}

void PlayLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
}