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
	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>();
	render->SetScaleToTexture("bottomglow_E2.png");
	render->SetOrder(static_cast<int>(OrderNum::EFFECT));
	//render->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());

	m_pRed = GetLevel()->CreateActor<Planet>();
	m_pRed->SetOrder(static_cast<int>(OrderNum::PLANET));
	m_pRed->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });
	m_pRed->SetName("Red");

	m_pBlue = GetLevel()->CreateActor<Planet>();
	m_pBlue->SetOrder(static_cast<int>(OrderNum::PLANET));
	m_pBlue->GetTransform()->SetLocalPosition({ -100.f,0.f,0.f });
	m_pBlue->SetName("Blue");

	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;

	m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());




	GameEngineInput::CreateKey("R", 'R');



	GameEngineInput::CreateKey("1", '1');
	GameEngineInput::CreateKey("2", '2');

	GameEngineInput::CreateKey("W", 'W');
	GameEngineInput::CreateKey("A", 'A');
	GameEngineInput::CreateKey("S", 'S');
	GameEngineInput::CreateKey("D", 'D');


	GameEngineInput::CreateKey("I", 'I');
	GameEngineInput::CreateKey("J", 'J');
	GameEngineInput::CreateKey("K", 'K');
	GameEngineInput::CreateKey("L", 'L');
}

void Player::Update(float _DeltaTime)
{
	TransformData red = m_pRed->GetTransform()->GetTransDataRef();
	TransformData blue = m_pBlue->GetTransform()->GetTransDataRef();
	int a = 0;

	if (true == GameEngineInput::IsAnyKey())
	{
		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>();
		render->SetScaleToTexture("bottomglow_E2.png");
		render->SetOrder(static_cast<int>(OrderNum::EFFECT));
		render->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
		m_pTurn->GetTransform()->SetParent(nullptr);
		if (false==m_bTurn)
		{
			m_pCenter = m_pBlue;
			m_pTurn = m_pRed;
			m_bTurn = true;
		}
		else
		{
			m_pCenter = m_pRed;
			m_pTurn = m_pBlue;
			m_bTurn = false;
		}

		m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());		
	}

	
	if (true == GameEngineInput::IsDown("1"))
	{
		m_bMoveControl = false;
	}
	if (true == GameEngineInput::IsDown("2"))
	{
		m_bMoveControl = true;
	}

	if (false == m_bMoveControl)
	{
		LocalMove(_DeltaTime);
	}
	else
	{
		WorldMove(_DeltaTime);
	}
	

	m_pCenter->GetTransform()->AddLocalRotation({ 0.f,0.f,300.f * _DeltaTime });
}

// 이건 디버깅용도나 
void Player::Render(float _DeltaTime)
{
}
void Player::LocalMove(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("W"))
	{
		m_pRed->GetTransform()->AddLocalPosition(float4::Up * 100.f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("A"))
	{
		m_pRed->GetTransform()->AddLocalPosition(float4::Left * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("S"))
	{
		m_pRed->GetTransform()->AddLocalPosition(float4::Down * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("D"))
	{
		m_pRed->GetTransform()->AddLocalPosition(float4::Right * 100.f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("I"))
	{
		m_pBlue->GetTransform()->AddLocalPosition(float4::Up * 100.f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("J"))
	{
		m_pBlue->GetTransform()->AddLocalPosition(float4::Left * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("K"))
	{
		m_pBlue->GetTransform()->AddLocalPosition(float4::Down * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("L"))
	{
		m_pBlue->GetTransform()->AddLocalPosition(float4::Right * 100.f * _DeltaTime);
	}
}
void Player::WorldMove(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("W"))
	{
		m_pRed->GetTransform()->AddWorldPosition(float4::Up*100.f*_DeltaTime);
	}

	if (true == GameEngineInput::IsPress("A"))
	{
		m_pRed->GetTransform()->AddWorldPosition(float4::Left * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("S"))
	{
		m_pRed->GetTransform()->AddWorldPosition(float4::Down * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("D"))
	{
		m_pRed->GetTransform()->AddWorldPosition(float4::Right * 100.f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("I"))
	{
		m_pBlue->GetTransform()->AddWorldPosition(float4::Up * 100.f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("J"))
	{
		m_pBlue->GetTransform()->AddWorldPosition(float4::Left * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("K"))
	{
		m_pBlue->GetTransform()->AddWorldPosition(float4::Down * 100.f * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("L"))
	{
		m_pBlue->GetTransform()->AddWorldPosition(float4::Right * 100.f * _DeltaTime);
	}
}
;
