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
		render->SetTexture("Level1BGTest.png");
		//render->ImageClippingX(0.23f,ClipXDir::Left);
		//render->ImageClippingX(0.45f, ClipXDir::Right);

		render->GetTransform()->SetLocalScale({ 1920.f,	1080,1.f });
		render->GetTransform()->AddLocalPosition({-100.f,0.f,10.f});


	//for (size_t i = 0; i < 5; i++)
	//{
	//	std::shared_ptr<BackGroundRenderer> render = CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
	//	render->SetScaleToTexture("testback"+GameEngineString::ToString(i+1)+".png");
	//	
	//	render->GetTransform()->AddLocalPosition({ render->GetTransform()->GetLocalScale().x * i, 0.f,0.f});
	//
	//}
}

