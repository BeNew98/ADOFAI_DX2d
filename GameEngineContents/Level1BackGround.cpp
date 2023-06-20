#include "PrecompileHeader.h"
#include "Level1BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
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
		render->SetTexture("TestBack.png");
		render->GetTransform()->SetLocalScale({ 20000.f,2000.f,1.f });
		render->GetTransform()->AddLocalPosition({3500.f,0.f,1000.f});


	//for (size_t i = 0; i < 5; i++)
	//{
	//	std::shared_ptr<BackGroundRenderer> render = CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
	//	render->SetScaleToTexture("testback"+GameEngineString::ToString(i+1)+".png");
	//	
	//	render->GetTransform()->AddLocalPosition({ render->GetTransform()->GetLocalScale().x * i, 0.f,0.f});
	//
	//}
}

