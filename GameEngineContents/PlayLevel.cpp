#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineFont.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "EditGui.h"
#include "Tiles.h"
#include "Planet.h"
#include "BlackScreen.h"
#include "Portal.h"
#include "Level1BackGround.h"
#include "WrongMark.h"
#include "TextObj.h"
#include "FadeEffect.h"
#include "FireWorkEffect.h"
#include "RoundGlowEffect.h"
#include "BackGroundRenderer.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}
void PlayLevel::Update(float _DeltaTime)
{
	if (m_bPause != GetMainCamera()->IsFreeCamera())
	{
		m_bPause = GetMainCamera()->IsFreeCamera();
		m_BGM.SetPause(m_bPause);
	}
	StartMechanism(_DeltaTime);
	GameSuccess();
	EndFireWork(_DeltaTime);
	PlanetSwap();

	m_pTitleNameText->SetPosition(float4{ 0.f,400.f } + GetMainCamera()->GetTransform()->GetWorldPosition());

	if (GameEngineInput::IsDown("CenterLevel"))
	{
		GameEngineCore::ChangeLevel("CenterLevel");
	}
}

void PlayLevel::Start()
{
}


void PlayLevel::LevelChangeStart()
{
	m_pCountText = CreateActor<TextObj>(OrderNum::TEXT);
	m_pCountText->SetTxt("아무 키를 눌러 시작하세요");
	m_pCountText->GetRenderer()->SetScale(100.f);
	m_pCountText->SetPosition({ 0.f,100.f });

	m_pProgressText = CreateActor<TextObj>(OrderNum::TEXT);
	m_pProgressText->GetRenderer()->SetScale(150.f);

	m_pTitleNameText = CreateActor<TextObj>(OrderNum::TEXT);
	m_pTitleNameText->SetTxt("1-X A Dance of Fire and Ice");
	m_pTitleNameText->GetRenderer()->SetScale(70.f);
	m_BGM = GameEngineSound::Play("1-X.wav");
	m_BGM.SetPosition(0.f);
	m_BGM.SetPause(true);
	//m_BGM = GameEngineSound::Play("sndkick.wav");
	//std::shared_ptr<GameEngineCamera> BackCam = CreateNewCamera(-1);
	//BackCam->SetProjectionType(CameraType::Perspective);
	//BackCam->GetTransform()->SetLocalPosition({ 0.f,0.f,-750.f })08;

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	CreateNewCamera(-1);
	GetCamera(-1)->SetProjectionType(CameraType::Orthogonal);
	GetCamera(-1)->GetTransform()->SetWorldPosition(float4::Zero);
	//std::shared_ptr<BlackScreen> m_pBlackScreen = CreateActor<BlackScreen>(OrderNum::BACKGROUND);
	//m_pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });


	std::shared_ptr<Level1BackGround> m_pLevel1BackGround = CreateActor<Level1BackGround>(OrderNum::BACKGROUND);
	m_pLevel1BackGround->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });

	EditGui::Editor->LoadtoString("");

	m_pStageInfo = EditGui::Editor->GetStageInfo(0);

	std::shared_ptr<RoundGlowEffect> pRGlow = GetLevel()->CreateActor<RoundGlowEffect>(OrderNum::EFFECT);
	pRGlow->GetTransform()->SetWorldPosition(m_pStageInfo.AllTile[0].m_pTile->GetPivotPos());

	m_iBPM = m_pStageInfo.BPM;
	m_fReadyTime = m_iBPM / 60.f / 5.f * 3.f;

	TileEventSetting();




	m_pRed = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue = CreateActor<Planet>(OrderNum::PLANET);
	m_pCenter = m_pRed;
	m_pCenter->SetDistance(m_fDistance);
	m_pTurn = m_pBlue;
	m_pTurn->SetDistance(m_fDistance);
	m_pBlue->GetTransform()->SetParent(m_pRed->GetTransform());
	m_pCenter->GetTransform()->SetLocalRotation({ 0.f,0.f,-135.f });

	m_pCenter->GetTransform()->SetWorldPosition(m_pStageInfo.AllTile[0].m_pTile->GetPivotPos());

	std::shared_ptr<Portal> m_pPortal1 = CreateActor<Portal>(OrderNum::MAP);
	m_pPortal1->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[m_pStageInfo.AllTile.size() - 1].m_pTile->GetPivotPos());
	m_pPortal1->SetFunction([this]()
		{
			m_FadeEffect = GetLastTarget()->CreateEffect<FadeEffect>();
			m_FadeEffect->FadeIn();
			m_FadeEffect->SetWhite();
			m_FadeEffect->SetTimeRatio(5.f);
			m_pProgressText->SetTxt("축하합니다!");
			m_pProgressText->SetPosition(m_pStageInfo.AllTile[m_pStageInfo.AllTile.size() - 1].m_pTile->GetPivotPos()+float4{0,-200.f});
			m_fGameSuccess = true;
		});

	EditGui::Editor->Off();

	m_fProgressPer = 100.f / m_pStageInfo.AllTile.size();

	GetMainCamera()->GetTransform()->SetWorldPosition(float4::Zero);
}

void PlayLevel::LevelChangeEnd()
{
	Reset();
}

void PlayLevel::Reset()
{
	m_bPause = false;
	m_BGM.SetPause(true);
	m_pStageInfo = {};
	m_pRed = nullptr;
	m_pBlue = nullptr;
	m_pCenter = nullptr;
	m_pTurn = nullptr;
	m_BGM = nullptr;
	m_bGameStart = false;
	m_bPlaying = false;
	m_bGameEnd = false;
	m_bGameFail = false;
	m_bFireEffectOn = false;
	m_fGameSuccess = false;
	m_fProgressPer = 0.f;
	m_fTotalProgress = 0.f;
	m_fFireEffectTime = 0.f;

	m_fDistance = 150.f;
	
	m_iBPM = 0;
	m_fReadyTime = 0.f;
	m_iCurIndex = 0;
	m_fStartTime = 0.f;
	GlobalValue::GetInst()->BPM = 1.f;
	AllActorDestroy();
}

void PlayLevel::StartMechanism(float _DeltaTime)
{
	if (true == GameEngineInput::IsAnyKey() && m_bGameStart == false)
	{
		m_bGameStart = true;
		m_pCountText->GetRenderer()->SetScale(200.f);
		m_pCountText->SetPosition({ 0.f,200.f });
		m_BGM.SetPause(false);
		m_BGM.setPosition(0);
		m_pCenter->SetGameStart(m_bGameStart);
		m_pTurn->SetGameStart(m_bGameStart);
	}

	if (m_bGameStart == false)
	{
		return;
	}


	m_fReadyTime -= _DeltaTime;
	if (m_bPlaying == false)
	{

		if (m_fReadyTime <= 0.f)
		{
			m_pCountText->SetTxt("시작");
			m_pCountText->SetColor({ 255.f,255.f,255.f });
			m_pCountText->FadeOn();
			m_bPlaying = true;
		}
		else
		{

			if (m_fReadyTime * 3.f >= 4.f)
			{
				m_pCountText->SetTxt("준비");
			}
			else
			{
				m_pCountText->SetTxt(std::to_string(static_cast<int>(m_fReadyTime * 3.f)));
			}
		}
	}

	if (m_fStartTime < m_fReadyTime)
	{
		return;
	}
}

void PlayLevel::EndFireWork(float _DeltaTime)
{

	if (true == m_bGameFail && false == m_bFireEffectOn)
	{
		m_fFireEffectTime += _DeltaTime;
		if (m_fFireEffectTime <= 1.f)
		{
			return;
		}

		m_BGM.SetPause(true);
		
		m_fFireEffectTime = 0.f;
		m_pRedFire = GetLastTarget()->CreateEffect<FireWorkEffect>();
		m_pRedFire->SetColor(float4::Red);
		m_pRedFire->SetDir(float4{ -1.f,1.f,-1.f,0.f });

		m_pBlueFire = GetLastTarget()->CreateEffect<FireWorkEffect>();
		m_pBlueFire->SetColor(float4::Blue);
		m_pBlueFire->SetDir(float4{ 1.f,1.f,1.f,0.f });
		m_bFireEffectOn = true;


		GameEngineSound::Play("sndPlanetPreExplosion.wav");


		char cArray[20];
		sprintf_s(cArray, "%0.2f", m_fTotalProgress);
		std::string sProgress = cArray;
		m_pProgressText->SetTxt(sProgress + "%\n 아무 키나 눌러 다시 시작");
		m_pProgressText->SetPosition(GetMainCamera()->GetTransform()->GetWorldPosition() + float4(0.f, -100.f));
		m_pProgressText->SetScale(100.f);

	}
	if (true == m_bFireEffectOn)
	{
		m_fFireEffectTime += _DeltaTime;
		if (m_fFireEffectTime>=4.f&& m_pRedFire!=nullptr && m_pBlueFire != nullptr)
		{
			GetLastTarget()->ReleaseEffect(m_pRedFire);
			GetLastTarget()->ReleaseEffect(m_pBlueFire);
			m_pRedFire = nullptr;
			m_pBlueFire = nullptr;

		}
		else 
		{
			if (GameEngineInput::IsAnyKey())
			{
				GameEngineCore::ChangeLevel("PlayLevel");
			}
		}
	}
	else
	{
		return;
	}
}

void PlayLevel::GameSuccess()
{
	if (m_fGameSuccess && GameEngineInput::IsAnyKey())
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	else
	{
		return;
	}
}

void PlayLevel::TileEventSetting()
{
	if (1 == EditGui::Editor->GetLevelValue())
	{

		{
			for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
			{
				std::shared_ptr<Tiles> tile = m_pStageInfo.AllTile[i].m_pTile;
				tile->SetTileEvent(EventType::MOVE, 0.f, m_fReadyTime * 5.f);
			}
		}

		{
			for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
			{
				std::shared_ptr<Tiles> tile = m_pStageInfo.AllTile[i].m_pTile;

				if (i == 31 ||
					i == 32 ||
					i == 33 ||
					i == 47 ||
					i == 48 ||
					i == 49 ||
					i == 54 ||
					i == 55 ||
					i == 56 ||
					i == 71 ||
					i == 72 ||
					i == 73 ||
					i == 77 ||
					i == 78 ||
					i == 79 
					)
				{
					continue;
				}
				tile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);
				tile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);
			}
		}
		{
			m_pStageInfo.AllTile[31].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[47].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[63].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[71].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[92].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[31+1].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[47+1].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[63+1].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[71+1].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);
			m_pStageInfo.AllTile[92+1].m_pTile->SetTileEvent(EventType::ROTATION, 15.f, 1.5f);

			m_pStageInfo.AllTile[31].m_pTile->SetTileEvent(EventType::BLACK, 1.f,0.f);
			m_pStageInfo.AllTile[47].m_pTile->SetTileEvent(EventType::BLACK, 1.f,0.f);
			m_pStageInfo.AllTile[54].m_pTile->SetTileEvent(EventType::BLACK, 1.f,0.f);
			m_pStageInfo.AllTile[71].m_pTile->SetTileEvent(EventType::BLACK, 1.f,0.f);
			m_pStageInfo.AllTile[92].m_pTile->SetTileEvent(EventType::BLACK, 1.f,0.f);


			m_pStageInfo.AllTile[31+2].m_pTile->SetTileEvent(EventType::BLACK, 0.f, 0.f);
			m_pStageInfo.AllTile[47+2].m_pTile->SetTileEvent(EventType::BLACK, 0.f, 0.f);
			m_pStageInfo.AllTile[54+2].m_pTile->SetTileEvent(EventType::BLACK, 0.f, 0.f);
			m_pStageInfo.AllTile[71+2].m_pTile->SetTileEvent(EventType::BLACK, 0.f, 0.f);
			m_pStageInfo.AllTile[92+2].m_pTile->SetTileEvent(EventType::BLACK, 0.f, 0.f);

			m_pStageInfo.AllTile[31].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f, 0.01f);
			m_pStageInfo.AllTile[47].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f, 0.01f);
			m_pStageInfo.AllTile[54].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f, 0.01f);
			m_pStageInfo.AllTile[71].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f, 0.01f);
			m_pStageInfo.AllTile[92].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f, 0.01f);

			m_pStageInfo.AllTile[31+1].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f,  0.01f);
			m_pStageInfo.AllTile[47+1].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f,  0.01f);
			m_pStageInfo.AllTile[54+1].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f,  0.01f);
			m_pStageInfo.AllTile[71+1].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f,  0.01f);
			m_pStageInfo.AllTile[92+1].m_pTile->SetTileEvent(EventType::ZOOM, -0.1f,  0.01f);

			m_pStageInfo.AllTile[31 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.2f,  0.01f);
			m_pStageInfo.AllTile[47 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.2f,  0.01f);
			m_pStageInfo.AllTile[54 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.2f,  0.01f);
			m_pStageInfo.AllTile[71 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.2f,  0.01f);
			m_pStageInfo.AllTile[92 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.2f,  0.01f);


			m_pStageInfo.AllTile[31 + 2].m_pTile->SetTileEvent(EventType::ROTATION,0.f,  0.01f);
			m_pStageInfo.AllTile[47 + 2].m_pTile->SetTileEvent(EventType::ROTATION,0.f,  0.01f);
			m_pStageInfo.AllTile[54 + 2].m_pTile->SetTileEvent(EventType::ROTATION,0.f,  0.01f);
			m_pStageInfo.AllTile[71 + 2].m_pTile->SetTileEvent(EventType::ROTATION,0.f,  0.01f);
			m_pStageInfo.AllTile[92 + 2].m_pTile->SetTileEvent(EventType::ROTATION,0.f,  0.01f);

			m_pStageInfo.AllTile[31 + 2].m_pTile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);
			m_pStageInfo.AllTile[47 + 2].m_pTile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);
			m_pStageInfo.AllTile[54 + 2].m_pTile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);
			m_pStageInfo.AllTile[71 + 2].m_pTile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);
			m_pStageInfo.AllTile[92 + 2].m_pTile->SetTileEvent(EventType::ZOOM, -0.05f, 0.05f);

			m_pStageInfo.AllTile[31 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);
			m_pStageInfo.AllTile[47 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);
			m_pStageInfo.AllTile[54 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);
			m_pStageInfo.AllTile[71 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);
			m_pStageInfo.AllTile[92 + 2].m_pTile->SetTileEvent(EventType::ZOOM, 0.05f, 0.1f);

		}

		{
			m_pStageInfo.AllTile[161].m_pTile->SetSpeedObj(BpmType::DOUBLE_SNAIL);
		}
	}
}

void PlayLevel::PlanetSwap()
{

	if (m_iCurIndex + 1 >= m_pStageInfo.AllTile.size()|| true == m_bGameFail|| 0< m_fReadyTime)
	{
		return;
	}

	float4 f4CenterPos = m_pCenter->GetTransform()->GetWorldPosition();
	float4 f4TurnPos = m_pTurn->GetTransform()->GetWorldPosition();
	std::shared_ptr<Tiles> pNextTile = m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile;
	float4 f4NextTilePos = pNextTile->GetPivotPos();

	float fAngle = float4::GetAngleVectorToVectorDeg360(f4NextTilePos - f4CenterPos, f4TurnPos - f4CenterPos);
	if (fAngle>0.f&&true == m_bGameEnd)
	{
		m_bGameEnd = false;
	}
	else if(fAngle <-120.f&&false == m_bGameEnd)
	{
		m_pCenter->SetGameEnd(true);
		m_pTurn->SetGameEnd(true);
		m_bGameFail = true;
		m_pProgressText->SetColor(float4::Null);
		std::map<EventType, std::vector<TileEvent>>::iterator findPrevIter = EditGui::Editor->GetStageInfo(0).AllTile[m_iCurIndex].m_pTile->m_mapAllEvent.find(EventType::ROTATION);
		if (findPrevIter != EditGui::Editor->GetStageInfo(0).AllTile[m_iCurIndex].m_pTile->m_mapAllEvent.end())
		{
			findPrevIter->second[0].End = true;
		}

		return;
	}

	if (true == GameEngineInput::IsAnyKey())
	{
		if (fAngle >= 60.f || fAngle <= -60.f)
		{
			if ((fAngle >= 60.f && fAngle <= 180.f) /*|| (-180.f <= fAngle && fAngle <= -120.f)*/)
			{
				std::shared_ptr<WrongMark> pWorngMark = CreateActor<WrongMark>(OrderNum::MAP);
				pWorngMark->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
				pWorngMark->SetTxt("너무 빠름");
				pWorngMark->SetColor({ 255.f,0.f,0.f });
			}
			else if (fAngle <= -60.f && fAngle >= -180.f)
			{
				std::shared_ptr<WrongMark> pWorngMark = CreateActor<WrongMark>(OrderNum::MAP);
				pWorngMark->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
				pWorngMark->SetTxt("너무 느림");
				pWorngMark->SetColor({ 255.f,0.f,0.f });
			}
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

		m_pCenter->GetTransform()->SetWorldPosition(f4NextTilePos);

		std::shared_ptr<TextObj> pTextObj = CreateActor<TextObj>(OrderNum::TEXT);
		pTextObj->GetTransform()->SetLocalPosition(m_pCenter->GetTransform()->GetWorldPosition());
		pTextObj->SetScale(75.f);
		pTextObj->SetPosition({ 0.f,200.f });
		pTextObj->FadeOn();
		if ((fAngle < 60.f && fAngle >= 45.f))
		{

			pTextObj->SetTxt("빠름!");
			pTextObj->SetColor({ 196.f, 63.f, 38.f });
		}
		else if (fAngle > -60.f && fAngle <= -45.f)
		{
			pTextObj->SetTxt("느림!");
			pTextObj->SetColor({ 196.f, 63.f, 38.f });
		}

		else if ((fAngle < 45.f && fAngle >= 30.f))
		{
			//++GlobalValue::GetInst()->vec_Accuracy[0].s_iEarlyPerfect;
			pTextObj->SetTxt("빠름");
			pTextObj->SetColor({ 152.f, 244.f, 73.f });
		}
		else if (fAngle > -45.f && fAngle <= -30.f)
		{
			//++GlobalValue::GetInst()->vec_Accuracy[0].s_iLatePerfect;
			pTextObj->SetTxt("느림");
			pTextObj->SetColor({ 152.f, 244.f, 73.f });
		}

		else
		{
			//++GlobalValue::GetInst()->vec_Accuracy[0].s_iPerfect;
			pTextObj->SetTxt("정확");
			pTextObj->SetColor({ 92.f, 248.f, 74.f });
		}

		m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile->GlowOn();

		pNextTile->EventOn();
		m_fTotalProgress += m_fProgressPer;
		++m_iCurIndex;

		m_bGameEnd = true;
	}
}