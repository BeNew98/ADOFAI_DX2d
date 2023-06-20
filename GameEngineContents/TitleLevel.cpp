#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineResource.h>

#include "BackGroundRenderer.h"
#include "TitleLogo.h"
#include "EditGui.h"
#include "BlackScreen.h"
#include "Tiles.h"
#include "Planet.h"
#include "EditGui.h"
#include "SquareGlowEffect.h"
#include "Portal.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}


void TitleLevel::Update(float _DeltaTime)
{
	GlowTimeCheck(_DeltaTime);
	PlanetSwap();


	if (GameEngineInput::IsDown("CenterLevel"))
	{
		GameEngineCore::ChangeLevel("CenterLevel");
	}
	if (GameEngineInput::IsDown("Level1"))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
		EditGui::Editor->SetLevel(1);
	}
	//if (GameEngineInput::IsDown("Level2"))
	//{
	//	GameEngineCore::ChangeLevel("PlayLevel");
	//	EditGui::Editor->SetLevel(2);
	//}
}

void TitleLevel::Start()
{	
}

void TitleLevel::LevelChangeStart()
{
	{
		m_BGM = GameEngineSound::Play("1-X.wav");
		m_BGM.SetPitch(0.8f);
		m_BGM.SetLoop();
		std::shared_ptr<GameEngineCamera> BackCam = CreateNewCamera(-1);
		BackCam->SetProjectionType(CameraType::Perspective);
		BackCam->GetTransform()->SetLocalPosition({ 0.f,0.f,-750.f });

		GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
		GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

		m_pBlackScreen = CreateActor<BlackScreen>(OrderNum::BACKGROUND);
		m_pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });

		std::shared_ptr<BackGroundRenderer> pStar0 = m_pBlackScreen->CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
		pStar0->SetScaleToTexture("starfields1.png");

		std::shared_ptr<BackGroundRenderer> pStar1 = m_pBlackScreen->CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
		pStar1->SetScaleToTexture("starfields2.png");

		m_pLogo = CreateActor<TitleLogo>(OrderNum::BACKGROUND);
		m_pLogo->GetTransform()->SetLocalPosition({ 0.f,300.f,0.f });


		
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
	
	for (size_t i = 16; i < 21; i++)
	{
		int a = 0;
	}
	for (size_t i = 41; i < m_pStageInfo.AllTile.size(); i++)
	{
		std::shared_ptr<Tiles> tile = m_pStageInfo.AllTile[i].m_pTile;
		tile->SetTileEvent(EventType::ZOOM, 0.05f, 0.05f);
		tile->SetTileEvent(EventType::ZOOM, -0.05f, 0.1f);

		tile->SetTileEvent(EventType::MOVE, 1.f, 0.5f);
	}


	for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
	{
		m_pStageInfo.AllTile[i].m_pTile->GetTransform()->AddWorldPosition({ -Tilepos.x, -Tilepos.y });
	}
	m_pPortal1 = CreateActor<Portal>(OrderNum::MAP);
	m_pPortal1->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[30].m_pTile->GetTransform()->GetWorldPosition());
	m_pPortal1->SetFunction([]() 
		{
			GameEngineCore::ChangeLevel("PlayLevel"); 
			EditGui::Editor->SetLevel(1);
		});

	m_pRed->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[12].m_pTile->GetTransform()->GetWorldPosition());

	CenterCheck();

	EditGui::Editor->Off();
	//EditGui::Editor->On();
	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(float4::Zero);
}

void TitleLevel::LevelChangeEnd()
{
	m_BGM.Stop();
	AllActorDestroy();
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
			m_pStageInfo.AllTile[i].m_pTile->AlphaSwitch();
		}
		m_pLogo->AlphaSwitch();
	}
	else
	{
		for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
		{
			if (i == 6 || i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18)
			{
				continue;
			}
			if (m_pStageInfo.AllTile[i].m_pTile->GetAlphaValue() == false)
			{
				return;
			}
			m_pStageInfo.AllTile[i].m_pTile->AlphaSwitch();

		}
		m_pLogo->AlphaSwitch();
	}

}

void TitleLevel::PlanetSwap()
{
	if (true == GameEngineInput::IsAnyKey())
	{
		std::shared_ptr<GameEngineCollision> pCenterColTile = m_pCenter->GetCol()->Collision(ColNum::TILE);

		std::vector<std::shared_ptr<GameEngineCollision>> vecCol;
		m_pTurn->GetCol()->CollisionAll(ColNum::TILE, vecCol);

		std::shared_ptr<GameEngineCollision> pTurnColTile = nullptr;
		for (size_t i = 0; i < vecCol.size(); i++)
		{
			pTurnColTile = vecCol[i];

			if (nullptr == pTurnColTile)
			{
				continue;
			}

			std::shared_ptr<Tiles> ColCenterTile = pCenterColTile->GetActor()->DynamicThis<Tiles>();
			std::shared_ptr<Tiles> ColTurnTile = pTurnColTile->GetActor()->DynamicThis<Tiles>();
			int CenterX = (ColCenterTile->GetData().ix());
			int CenterY = (ColCenterTile->GetData().iy());
			int TurnX = (ColTurnTile->GetData().ix());
			int TurnY = (ColTurnTile->GetData().iy());


			if (false == ((CenterX + 1 == TurnX && CenterY == TurnY) ||
				(CenterX == TurnX && CenterY + 1 == TurnY) ||
				(CenterX - 1 == TurnX && CenterY == TurnY) ||
				(CenterX == TurnX && CenterY - 1 == TurnY)) || ColTurnTile->GetData().iz() == 361)
			{
				continue;
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
			ColTurnTile->EventOn();
		}
		CenterCheck();
		return;
	}


}
void TitleLevel::GlowTimeCheck(float _DeltaTime)
{
	if (m_fTime>=180.f)
	{
		m_fTime -= 180.f;
		m_bGlow = !m_bGlow;
	}

	m_fTime += 180.f * _DeltaTime;
}
