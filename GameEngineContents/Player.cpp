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

	m_pWhite = GetLevel()->CreateActor<Planet>();
	m_pWhite->GetTransform()->SetLocalPosition({ -200.f,0.f,0.f });

	m_pRed->GetTransform()->SetParent(m_pWhite->GetTransform());
}

void Player::Update(float _DeltaTime)
{
	bool check = GameEngineInput::IsAnyKey();
	if (true == GameEngineInput::IsAnyKey())
	{
		if (!m_bTurn)
		{
			m_pWhite->GetTransform()->SwitchParent(m_pRed->GetTransform());
		}
		else
		{
			m_pRed->GetTransform()->SwitchParent(m_pWhite->GetTransform());
		}

		m_bTurn = !m_bTurn;
	}

	if (m_bTurn)
	{
		m_pRed->GetTransform()->AddLocalRotation({ 0.f,0.f,_DeltaTime * 100.f });
	}
	else
	{
		m_pWhite->GetTransform()->AddLocalRotation({ 0.f,0.f,_DeltaTime * 100.f });
	}
	//m_pTurn->GetTransform()->SetWorldPosition(fResultPos);

	//m_pTurn->GetTransform()->AddLocalRotation({ 0.f,0.f,_DeltaTime *100.f });
	
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
};
