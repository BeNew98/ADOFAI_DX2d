#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Planet.h"
#include "EditGui.h"
#include "Tiles.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	m_pEditor = EditGui::Editor;

	GetTransform()->AddLocalPosition({ 0.f,16.f,0.f });

	m_pRed = GetLevel()->CreateActor<Planet>(OrderNum::PLANET,"Red");
	m_pRed->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	m_pBlue = GetLevel()->CreateActor<Planet>(OrderNum::PLANET, "Blue");
	m_pBlue->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	m_pBlue->GetTransform()->AddLocalPosition({ -150.f,0.f,0.f });

	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;

	m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());

	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	render->SetScaleToTexture("bottomglow_E2.png");
	render->SetOrder(static_cast<int>(OrderNum::EFFECT));
	render->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());

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
	PlanetSwap(_DeltaTime);
	m_pCenter->GetTransform()->AddLocalRotation({ 0.f,0.f,-180.f * _DeltaTime });

	CamMoveLerp(m_fPrevCenterPos, m_fCurCenterPos, _DeltaTime);
}

// 이건 디버깅용도나 
void Player::Render(float _DeltaTime)
{
}

void Player::PlanetSwap(float _Deltatime)
{
	if (m_iCurIndex>= m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile.size()||
		m_iCurIndex + 1 >= m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile.size())
	{
		return;
	}
	std::shared_ptr<Tiles> pTile = m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile[m_iCurIndex + 1].m_pTile;


	if (true == GameEngineInput::IsAnyKey()
		&& m_pTurn->GetTransform()->Collision({ ._OtherTrans = pTile->GetCol()->GetTransform() }))
	{

		m_fPrevCenterPos = m_fCurCenterPos;
		m_pTurn->GetTransform()->SetParent(nullptr);
		if (false == m_bTurn)
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
		m_pCenter->GetTransform()->SetLocalPosition(pTile->GetCol()->GetTransform()->GetWorldPosition());

		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
		render->SetScaleToTexture("bottomglow_E2.png");
		render->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());
		++m_iCurIndex;

		m_fLerpTime = 0;
		m_fCurCenterPos = m_pCenter->GetTransform()->GetWorldPosition();

	}
}

void Player::CamMoveLerp(float4 _Start, float4 _End, float _Ratio)
{
	if (m_iCurIndex >= m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile.size() ||
		m_iCurIndex + 1 >= m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile.size())
	{
		return;
	}
	std::shared_ptr<Tiles> pCurTile = m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile[m_iCurIndex].m_pTile;
	std::shared_ptr<Tiles> pNextTile = m_pEditor->m_vecAllStage[m_pEditor->m_iCurLevel].AllTile[m_iCurIndex + 1].m_pTile;
	m_fLerpTime += _Ratio;
	//GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(_Start, _End, m_fLerpTime));

	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(pCurTile->GetTransform()->GetWorldPosition(), pNextTile->GetTransform()->GetWorldPosition(), m_fLerpTime));
	int a = 0;
}
