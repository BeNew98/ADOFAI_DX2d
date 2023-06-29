#include "PrecompileHeader.h"
#include "BlackScreen.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BackGroundRenderer.h"
#include <GameEngineCore/GameEngineLevel.h>

BlackScreen::BlackScreen() 
{
}

BlackScreen::~BlackScreen() 
{	
}

void BlackScreen::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	render->SetTexture("BlackScreen.png");
	render->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize()*1.2f);
}

void BlackScreen::Update(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition());
}

