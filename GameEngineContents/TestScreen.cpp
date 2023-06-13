#include "PrecompileHeader.h"
#include "TestScreen.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TestScreen::TestScreen() 
{
}

TestScreen::~TestScreen() 
{
}

void TestScreen::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	render->SetScaleToTexture("Test1.png");
	render->GetTransform()->AddLocalPosition({ 400.f, 0.f });
}

