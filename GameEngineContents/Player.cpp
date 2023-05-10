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

	//m_pRed->GetTransform()->SetParent(m_pWhite->GetTransform());

	m_pCenter = m_pRed;
	m_pTurn = m_pWhite;
}

void Player::Update(float _DeltaTime)
{
	//TransformData TurnData = {};
	//TurnData.Position = m_pCenter->GetTransform()->GetLocalPosition() + m_pTurn->GetTransform()->GetLocalPosition();
	//TurnData.Rotation = m_pTurn->GetTransform()->GetLocalRotation();
	//m_pTurn->GetTransform()->SetTransformData(TurnData);
	//TurnData.Rotation += float4{ 0.f,0.f,_DeltaTime * 100.f };
	
	m_pTurn->GetTransform()->SetWorldPosition(m_pCenter->GetTransform()->GetWorldPosition() + m_pTurn->GetTransform()->GetWorldPosition());


	m_pTurn->GetTransform()->AddLocalRotation({0.f,0.f,_DeltaTime*100.f});

	
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
};
