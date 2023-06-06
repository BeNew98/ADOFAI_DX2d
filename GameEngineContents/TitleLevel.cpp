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


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}


void TitleLevel::Update(float _DeltaTime)
{
	CamMoveLerp(_DeltaTime);
	CenterCheck();
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

		std::shared_ptr<BlackScreen> pBlackScreen = CreateActor<BlackScreen>(0);
		pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });

		std::shared_ptr<GameEngineSpriteRenderer> pStar0 = pBlackScreen->CreateComponent<GameEngineSpriteRenderer>();
		pStar0->SetScaleToTexture("starfields1.png");

		std::shared_ptr<GameEngineSpriteRenderer> pStar1 = pBlackScreen->CreateComponent<GameEngineSpriteRenderer>();
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


	for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
	{
		m_pStageInfo.AllTile[i].m_pTile->GetTransform()->AddWorldPosition({ -Tilepos.x, -Tilepos.y });
	}

	m_pRed->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[12].m_pTile->GetTransform()->GetWorldPosition());
}

void TitleLevel::LevelChangeEnd()
{
}


void TitleLevel::CenterCheck()
{
	if ((m_pRed->IsCenter() == true && m_pRed->GetTransform()->Collision({._OtherTrans = m_pStageInfo.AllTile[12].m_pTile->GetCol()->GetTransform()})) || (m_pBlue->IsCenter() == true && m_pBlue->GetTransform()->Collision({ ._OtherTrans = m_pStageInfo.AllTile[12].m_pTile->GetCol()->GetTransform() })))
	{
		for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
		{
			if (i==6|| i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18)
			{
				continue;
			}
			m_pStageInfo.AllTile[i].m_pTile->GetRender()->Off();
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
}
