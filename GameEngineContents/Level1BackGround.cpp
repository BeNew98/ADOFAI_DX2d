#include "PrecompileHeader.h"
#include "Level1BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BlackScreen.h"
#include "BackGroundRenderer.h"

Level1BackGround::Level1BackGround() 
{
}

Level1BackGround::~Level1BackGround() 
{
}	

void Level1BackGround::Start()
{
	std::shared_ptr<BackGroundRenderer> render = CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
	render->SetTexture("Level1BGTest.png");

	render->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize() * 1.2f);

}

void Level1BackGround::Update(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition());
}

