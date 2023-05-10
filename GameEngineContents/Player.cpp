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
	m_pRed->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });

	m_pBlue = GetLevel()->CreateActor<Planet>();
	m_pBlue->GetTransform()->SetLocalPosition({ -200.f,0.f,0.f });


	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;

	m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());

	GameEngineInput::CreateKey("R", 'R');

	GameEngineInput::CreateKey("W", 'W');
	GameEngineInput::CreateKey("A", 'A');
	GameEngineInput::CreateKey("S", 'S');
	GameEngineInput::CreateKey("D", 'D');
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("R"))
	{
		m_pTurn->GetTransform()->CutParent();
	
		std::shared_ptr<Planet> pTemp = m_pCenter;
		m_pCenter = m_pTurn;
		m_pTurn = pTemp;
	
		m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());
	}

	if (true == GameEngineInput::IsPress("W"))
	{
		m_pCenter->GetTransform()->AddWorldPosition(float4::Up*100.f*_DeltaTime);
	}

	if (true == GameEngineInput::IsPress("A"))
	{
		m_pCenter->GetTransform()->AddWorldPosition(float4::Left * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("S"))
	{
		m_pCenter->GetTransform()->AddWorldPosition(float4::Down * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("D"))
	{
		m_pCenter->GetTransform()->AddWorldPosition(float4::Right * 100.f * _DeltaTime);
	}
	//m_pCenter->GetTransform()->AddWorldRotation({ 0.f,0.f,100.f * _DeltaTime });

}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
};
