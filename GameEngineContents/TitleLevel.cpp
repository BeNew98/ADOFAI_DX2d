#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "TitleLogo.h"
#include "EditGui.h"
#include "BlackScreen.h"
#include "Tiles.h"
#include "Planet.h"
#include "EditGui.h"
#include "GlowEffect.h"
#include "Portal.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}


void TitleLevel::Update(float _DeltaTime)
{
	//CamMoveLerp(_DeltaTime);
	//CenterCheck();
	PlanetSwap();
	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(m_pCenter->GetTransform()->GetWorldPosition());
}

void TitleLevel::Start()
{
	GameEngineInput::CreateKey("R", 'R');
	GameEngineInput::CreateKey("1", '1');
	GameEngineInput::CreateKey("2", '2');	
}

void TitleLevel::LevelChangeStart()
{
	
	{

		GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
		GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

		m_pBlackScreen = CreateActor<BlackScreen>(0);
		m_pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });

		std::shared_ptr<GameEngineSpriteRenderer> pStar0 = m_pBlackScreen->CreateComponent<GameEngineSpriteRenderer>();
		pStar0->SetScaleToTexture("starfields1.png");

		std::shared_ptr<GameEngineSpriteRenderer> pStar1 = m_pBlackScreen->CreateComponent<GameEngineSpriteRenderer>();
		pStar1->SetScaleToTexture("starfields2.png");

		std::shared_ptr<TitleLogo> pLogo = CreateActor<TitleLogo>(0);
		pLogo->GetTransform()->SetLocalPosition({ 0.f,300.f,0.f });


		
	}

	EditGui::Editor->LoadtoString("Title1~2");
	m_pStageInfo = EditGui::Editor->GetStageInfo(0);
	
	m_pRed = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue = CreateActor<Planet>(OrderNum::PLANET);
	float4 Tilepos = m_pStageInfo.AllTile[12].m_pTile->GetTransform()->GetWorldPosition();
	m_pBlue->GetTransform()->SetParent(m_pRed->GetTransform());
	m_pBlue->GetTransform()->AddLocalPosition({ -100.f,0.f,0.f });
	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;


	std::shared_ptr<GlowEffect> pGlow = CreateActor<GlowEffect>(OrderNum::EFFECT);
	pGlow->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());


	for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
	{
		m_pStageInfo.AllTile[i].m_pTile->GetTransform()->AddWorldPosition({ -Tilepos.x, -Tilepos.y });
	}
	std::shared_ptr<Portal> pPortal1 = CreateActor<Portal>(OrderNum::MAP);
	//5pPortal1->SetFunction([]()
	//5	{
	//5		GameEngineCore::ChangeLevel("PlayLevel");
	//5	});

	m_pRed->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[12].m_pTile->GetTransform()->GetWorldPosition());

	CenterCheck();
}

void TitleLevel::LevelChangeEnd()
{
}


void TitleLevel::CenterCheck()
{
	if (m_pCenter->IsCenter() == true && m_pCenter->GetTransform()->Collision({._OtherTrans = m_pStageInfo.AllTile[12].m_pTile->GetCol()->GetTransform()}))
	{
		for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
		{
			if (i == 6 || i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18)
			{
				continue;
			}
			m_pStageInfo.AllTile[i].m_pTile->GetRender()->Off();
			//m_pStageInfo.AllTile[i].m_pTile->SetPlusColor(float4{ 0.f,0.f,0.f, -1.f });
		}
	}
	else
	{
		for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
		{
			if (i == 6 || i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18)
			{
				continue;
			}

			m_pStageInfo.AllTile[i].m_pTile->GetRender()->On();
			//m_pStageInfo.AllTile[i].m_pTile->SetPlusColor(float4{ 0.f,0.f,0.f,1.f });
		}
	}

}

void TitleLevel::CamMoveLerp(float _Ratio)
{
	if (m_iCurIndex >= EditGui::Editor->GetStageInfo(0).AllTile.size() ||
		m_iCurIndex + 1 >= EditGui::Editor->GetStageInfo(0).AllTile.size())
	{
		return;
	}
	std::shared_ptr<Tiles> pCurTile = EditGui::Editor->GetStageInfo(0).AllTile[m_iCurIndex + 1].m_pTile;
	std::shared_ptr<Tiles> pNextTile = EditGui::Editor->GetStageInfo(0).AllTile[m_iCurIndex].m_pTile;
	m_fLerpTime += _Ratio;

	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::LerpClamp(m_fPrevTilePos, m_fCurTilePos, m_fLerpTime));
}

void TitleLevel::PlanetSwap()
{


		if (true == GameEngineInput::IsAnyKey())
		{
			std::shared_ptr<GameEngineCollision> pCenterColTile = m_pCenter->GetCollision()->Collision(OrderNum::MAP);


			std::shared_ptr<GameEngineCollision> pTurnColTile = m_pTurn->GetCollision()->Collision(OrderNum::MAP);



			if (nullptr==pTurnColTile)
			{
				return;
			}

			std::shared_ptr<Tiles> ColCenterTile = pCenterColTile->GetActor()->DynamicThis<Tiles>();
			std::shared_ptr<Tiles> ColTurnTile = pTurnColTile->GetActor()->DynamicThis<Tiles>();
			int CenterX =(ColCenterTile->m_fData.ix());
			int CenterY =(ColCenterTile->m_fData.iy());
			int TurnX	=(ColTurnTile->m_fData.ix());
			int TurnY	=(ColTurnTile->m_fData.iy());
			

			if (false == ((CenterX + 1 == TurnX && CenterY == TurnY) ||
				(CenterX == TurnX && CenterY + 1 == TurnY) ||
				(CenterX - 1 == TurnX && CenterY == TurnY) ||
				(CenterX == TurnX && CenterY - 1 == TurnY))|| ColTurnTile->m_fData.iz() == 361)
			{
				return;
			}




			m_pTurn->GetTransform()->SetParent(nullptr);
			if (true == m_pRed->IsCenter())
			{
				m_pRed->CenterChange();
				m_pBlue->CenterChange();
				m_pCenter = m_pBlue;
				m_pTurn = m_pRed;
			}
			else
			{
				m_pRed->CenterChange();
				m_pBlue->CenterChange();
				m_pCenter = m_pRed;
				m_pTurn = m_pBlue;
			}
			m_pTurn->GetTransform()->SetParent(m_pCenter->GetTransform());
			
			m_pCenter->GetTransform()->SetWorldPosition(ColTurnTile->GetTransform()->GetWorldPosition());

			ColTurnTile->GlowOn();

			m_fLerpTime = 0;

			++m_iCurIndex;
			m_fPrevTilePos = m_pStageInfo.AllTile[m_iCurIndex - 1].m_pTile->GetTransform()->GetWorldPosition();
			m_fCurTilePos = m_pStageInfo.AllTile[m_iCurIndex].m_pTile->GetTransform()->GetWorldPosition();
		}

		CenterCheck();
}
