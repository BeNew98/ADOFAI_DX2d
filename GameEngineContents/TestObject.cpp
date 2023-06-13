#include "PrecompileHeader.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

TestObject::TestObject()
{
}

TestObject::~TestObject()
{
}


void TestObject::Update(float _DeltaTime)
{

}

void TestObject::Start()
{
	{
		std::shared_ptr<GameEngineSpriteRenderer> pRender = CreateComponent<GameEngineSpriteRenderer>();
		pRender->SetScaleToTexture("bottomglow_E2.png");
		pRender->GetTransform()->SetLocalPosition({ 0.f, 300.0f });
	}

	{
		// HPBar
		std::shared_ptr<GameEngineUIRenderer> pRender = CreateComponent<GameEngineUIRenderer>();
		pRender->SetScaleToTexture("bottomglow_E2.png");
		pRender->GetTransform()->SetLocalPosition({ 0.0f, -300.0f });
	}
}