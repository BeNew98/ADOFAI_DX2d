#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineResource.h>

#include "TitleLogo.h"
#include "EditGui.h"
#include "BlackScreen.h"
#include "Tiles.h"
#include "Planet.h"
#include "EditGui.h"
#include "SquareGlowEffect.h"
#include "Portal.h"
#include "TitleBackGround.h"
#include "TextObj.h"
#include "BackGroundRenderer.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Update(float _DeltaTime)
{
	StartMechanism(_DeltaTime);
	GlowTimeCheck(_DeltaTime);
	PlanetSwap();

	if (GameEngineInput::IsDown("CenterLevel"))
	{
		GameEngineCore::ChangeLevel("CenterLevel");
	}
	if (GameEngineInput::IsDown("Level1"))
	{
		m_pCenter->GetTransform()->SetLocalPosition(m_pPortal1->GetAccPosition()); 
		CenterCheck();
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
	CreateNewCamera(-1);
	GetCamera(-1)->SetProjectionType(CameraType::Orthogonal);
	GetCamera(-1)->GetTransform()->SetWorldPosition(float4::Zero);
	{	/*
		std::shared_ptr<GameEngineCamera> BackCam = CreateNewCamera(-1);
		BackCam->SetProjectionType(CameraType::Perspective);
		BackCam->GetTransform()->SetLocalPosition({ 0.f,0.f,-750.f });*/
		m_BGM = GameEngineSound::Play("1-X.wav");

		GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
		GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

		//std::shared_ptr<TitleBackGround> pBG = CreateActor<TitleBackGround>(OrderNum::BACKGROUND);

		m_pBlackScreen = CreateActor<BlackScreen>(OrderNum::BACKGROUND);
		m_pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });
		
		std::shared_ptr<GameEngineSpriteRenderer> pStar0 = m_pBlackScreen->CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
		pStar0->SetScaleToTexture("starfields1.png");
		
		std::shared_ptr<GameEngineSpriteRenderer> pStar1 = m_pBlackScreen->CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
		pStar1->SetScaleToTexture("starfields2.png");

		m_pLogo = CreateActor<TitleLogo>(OrderNum::BACKGROUND);
		m_pLogo->GetTransform()->SetLocalPosition({ 0.f,300.f,0.f });


		
	}
	GlobalValue::GetInst()->vec_Accuracy.resize(2);
	EditGui::Editor->LoadtoString("Title1~2");
	EditGui::Editor->SetBPM(static_cast<int>(150.f * 0.8f));
	m_pStageInfo = EditGui::Editor->GetStageInfo(0);
	m_fSpeed = m_pStageInfo.RotSpeed*2.f;
	m_pRed = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue = CreateActor<Planet>(OrderNum::PLANET);
	float4 Tilepos = m_pStageInfo.AllTile[12].m_pTile->GetTransform()->GetWorldPosition();
	m_pBlue->GetTransform()->SetParent(m_pRed->GetTransform());
	//m_pBlue->GetTransform()->AddLocalPosition({ -100.f,0.f,0.f });
	m_pCenter = m_pRed;
	m_pCenter->SetDistance(m_fDistance);
	m_pTurn = m_pBlue;
	m_pTurn->SetDistance(m_fDistance);
	m_pCenter->GetTransform()->SetLocalRotation({ 0.f,0.f,-135.f });
	
	for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
	{
		std::shared_ptr<Tiles> tile = m_pStageInfo.AllTile[i].m_pTile;
		tile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);
		tile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);
		if (i >= 43)
		{
			tile->SetTileEvent(EventType::MOVE, 200.f, 0.5f);
		}

	}



	for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
	{
		m_pStageInfo.AllTile[i].m_pTile->GetTransform()->AddWorldPosition({ -Tilepos.x, -Tilepos.y });
	}
	m_pPortal1 = CreateActor<Portal>(OrderNum::MAP);
	m_pPortal1->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[30].m_pTile->GetTransform()->GetWorldPosition());
	m_pPortal1->SetFunction([this]() 
		{
			GameEngineCore::ChangeLevel("PlayLevel"); 
			EditGui::Editor->SetLevel(1);
			EditGui::Editor->SetBPM(150);
			PrevPosition = m_pPortal1->GetAccPosition();
		});
	//m_pPortal1->SetText(m_pAccuracyText);

	std::shared_ptr< GameEngineSpriteRenderer> pLevel1 = m_pStageInfo.AllTile[30].m_pTile->CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	pLevel1->SetTexture("1.png");
	pLevel1->GetTransform()->SetLocalPosition({ 0.f,250.f });
	pLevel1->GetTransform()->SetLocalScale({212.f,256.f,1.f });



	std::shared_ptr< GameEngineSpriteRenderer> pLevel1Name = m_pStageInfo.AllTile[30].m_pTile->CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	pLevel1Name->SetScaleToTexture("menu_names_lowres.png");
	pLevel1Name->GetTransform()->SetLocalPosition({ 0.f,550.f });
	//pLevel1Name->GetTransform()->SetLocalScale({ 212.f,256.f,1.f });

	m_pAccuracyText = CreateActor<TextObj>(OrderNum::TEXT);
	m_pAccuracyText->SetScale(50.f);
	m_pAccuracyText->SetPosition(pLevel1Name->GetTransform()->GetWorldPosition()-float4{0.f,20.f});
	m_pAccuracyText->SetTxt("1번째 세계");
	

	std::shared_ptr< GameEngineSpriteRenderer> pLevel1Fog = m_pStageInfo.AllTile[30].m_pTile->CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	pLevel1Fog->SetTexture("StageFog.png");
	pLevel1Fog->GetTransform()->SetLocalPosition(pLevel1->GetTransform()->GetLocalPosition());
	pLevel1Fog->GetTransform()->SetLocalScale({ 212.f*1.5f,256.f * 1.5f,1.f });
	pLevel1Fog->ColorOptionValue.PlusColor = float4{ 137.f / 255.f, 152.f / 255.f, 154.f / 255.f,0.f };
	pLevel1Fog->ColorOptionValue.MulColor = float4{ 137.f / 255.f, 152.f / 255.f, 154.f / 255.f,0.8f };

	m_pRed->GetTransform()->SetLocalPosition(PrevPosition);

	std::shared_ptr<SquareGlowEffect> pSGlow = GetLevel()->CreateActor<SquareGlowEffect>(OrderNum::EFFECT);
	pSGlow->GetTransform()->SetWorldPosition(PrevPosition);


	for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
	{
		if (i == 6 || i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18)
		{
			continue;
		}
		m_pStageInfo.AllTile[i].m_pTile->GetRender()->ColorOptionValue.MulColor = { 1.f, 1.f, 1.f, 0.f };
	}
	//m_pAccuracyText->SetScale(75.f);
	//m_pAccuracyText->GetTransform()->SetWorldPosition(pLevel1->GetTransform()->GetWorldPosition());
	////m_pAccuracyText->Off();
	//m_pAccuracyText->SetTxt("플레이 기록 없음");
	//m_pAccuracyText->SetPosition({ 0.f,64.f });
	//m_pAccuracyText->SetColor({ 255.f ,255.f ,255.f , 0.f});
	
	EditGui::Editor->Off();
	//EditGui::Editor->On();

	m_fReadyTime = EditGui::Editor->GetStageInfo(0).BPM / 60.f / 5.f;
	if (PrevPosition!=float4::Zero)
	{
		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(PrevPosition+float4{0.f,200.f});
	}
	else
	{
		GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(PrevPosition);
	}

	CenterCheck();
}

void TitleLevel::LevelChangeEnd()
{
	Reset();
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
			m_pStageInfo.AllTile[i].m_pTile->AlphaSwitch(true);
		}
		m_pLogo->AlphaSwitch(true);
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
			m_pStageInfo.AllTile[i].m_pTile->AlphaSwitch(false);

		}
		if (m_pLogo->GetAlphaValue() == false)
		{
			return;
		}
		m_pLogo->AlphaSwitch(false);
	}

}

void TitleLevel::Reset()
{
	m_BGM.Stop();
	m_pStageInfo = {};


	 m_iCurIndex = 0;
	 m_fLerpTime = 0.f;

	 m_fCurTilePos = float4::Zero;
	 m_fPrevTilePos = float4::Zero;

	 m_fTime = 0.f;
	 m_bGlow = false;
	 m_fGlowRatio = 0.f;
	 m_fSpeed = 0.f;
	 m_bGameStart = false;
	 m_fDistance = 100.f;

	 m_fTexttime = 0.f;
	 AllActorDestroy();
}

void TitleLevel::PlanetSwap()
{
	if (false == GameEngineInput::IsFree("Level1"))
	{
		return;
	}
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
void TitleLevel::StartMechanism(float _DeltaTime)
{
	if (m_bGameStart == false)
	{
		CenterCheck();
		m_bGameStart = true;
		m_pCenter->SetGameStart(m_bGameStart);
		m_pTurn->SetGameStart(m_bGameStart);
		m_BGM.SetPitch(0.8f);
		m_BGM.setPosition(0);
		m_BGM.SetLoop();
	}
	m_fReadyTime -= _DeltaTime;
	if (m_fReadyTime >= 0.f)
	{
		return;
	}
}
void TitleLevel::GlowTimeCheck(float _DeltaTime)
{
	if (m_fTime>= m_fSpeed)
	{
		m_fTime -= m_fSpeed;
		m_bGlow = !m_bGlow;
	}

	m_fTime += m_fSpeed * _DeltaTime*2.f;
}
