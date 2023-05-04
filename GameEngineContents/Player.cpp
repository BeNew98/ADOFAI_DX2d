#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Planet.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	m_pRed = GetLevel()->CreateActor<Planet>();
	m_pRed->GetTransform()->SetLocalPosition({ 100.f,0.f,0.f });

	m_pYellow = GetLevel()->CreateActor<Planet>();
	m_pYellow->GetTransform()->SetLocalPosition({ -100.f,0.f,0.f });
	

}

void Player::Update(float _DeltaTime)
{

	
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
};
