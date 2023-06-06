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
	PlanetSwap();
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
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");


		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
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


	std::shared_ptr<GameEngineSpriteRenderer> pEffectRender = m_pBlackScreen->CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	pEffectRender->SetScaleToTexture("bottomglow_E2.png");
	pEffectRender->SetOrder(static_cast<int>(OrderNum::EFFECT));
	pEffectRender->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());


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
	if (m_pCenter->IsCenter() == true && m_pRed->GetTransform()->Collision({._OtherTrans = m_pStageInfo.AllTile[12].m_pTile->GetCol()->GetTransform()}))
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
		if (true == GameEngineInput::IsAnyKey())
		{

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
			

			std::shared_ptr<GameEngineSpriteRenderer> render = m_pBlackScreen->CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
			render->SetScaleToTexture("bottomglow_E2.png");
			render->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());

			m_fLerpTime = 0;

			++m_iCurIndex;
			m_fPrevTilePos = m_pStageInfo.AllTile[m_iCurIndex - 1].m_pTile->GetTransform()->GetWorldPosition();
			m_fCurTilePos = m_pStageInfo.AllTile[m_iCurIndex].m_pTile->GetTransform()->GetWorldPosition();
		}

}
