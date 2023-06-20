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

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Update(float _DeltaTime)
{
	PlanetSwap();

	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(m_pCenter->GetTransform()->GetWorldPosition());
	GetLevel()->GetCamera(-1)->GetTransform()->SetWorldPosition(m_pCenter->GetTransform()->GetWorldPosition());

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
	GameEngineFont::Load("Ch2.0-1");


	std::shared_ptr<GameEngineCamera> BackCam = CreateNewCamera(-1);
	BackCam->SetProjectionType(CameraType::Perspective);
	BackCam->GetTransform()->SetLocalPosition({ 0.f,0.f,-750.f });

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//std::shared_ptr<BlackScreen> m_pBlackScreen = CreateActor<BlackScreen>(OrderNum::BACKGROUND);
	//m_pBlackScreen->GetTransform()->SetLocalPosition({ 0.f,0.f,0.f });


	std::shared_ptr<Level1BackGround> m_pLevel1BackGround = CreateActor<Level1BackGround>(OrderNum::BACKGROUND);
	//m_pLevel1BackGround->GetTransform()->AddLocalPosition({ -12500.f,0.f,0.f });


	EditGui::Editor->LoadtoString("");

	m_pStageInfo = EditGui::Editor->GetStageInfo(0);
	{
		for (size_t i = 0; i < m_pStageInfo.AllTile.size(); i++)
		{
			std::shared_ptr<Tiles> tile = m_pStageInfo.AllTile[i].m_pTile;
			tile->SetTileEvent(EventType::ZOOM, 0.1f, 0.05f);
			tile->SetTileEvent(EventType::ZOOM, -0.1f, 0.1f);

			tile->SetTileEvent(EventType::MOVE, 100.f, 1.f);

			tile->SetTileEvent(EventType::ROTATION,90.f, 1.f);
		}
		
	}

	m_pRed = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue->GetTransform()->SetParent(m_pRed->GetTransform());
	m_pBlue->GetTransform()->AddLocalPosition({ -150.f,0.f,0.f });
	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;

	m_pCenter->GetTransform()->SetWorldPosition(m_pStageInfo.AllTile[0].m_pTile->GetPivotPos());

	std::shared_ptr<Portal> m_pPortal1 = CreateActor<Portal>(OrderNum::MAP);
	m_pPortal1->GetTransform()->SetLocalPosition(m_pStageInfo.AllTile[m_pStageInfo.AllTile.size()-1].m_pTile->GetPivotPos());
	m_pPortal1->SetFunction([]()
		{
			GameEngineCore::ChangeLevel("CenterLevel");
		});

	EditGui::Editor->Off();
}

void PlayLevel::LevelChangeEnd()
{
	AllActorDestroy();
	Reset();
}

void PlayLevel::Reset()
{
	m_pStageInfo = {};
	m_pRed = nullptr;
	m_pBlue = nullptr;
	m_pCenter = nullptr;
	m_pTurn = nullptr;

	m_iCurIndex = 0;
}

void PlayLevel::PlanetSwap()
{
	if (true == GameEngineInput::IsAnyKey())
	{
		float4 f4CenterPos = m_pCenter->GetTransform()->GetWorldPosition();
		float4 f4TurnPos = m_pTurn->GetTransform()->GetWorldPosition();
		std::shared_ptr<Tiles> pNextTile = m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile;
		float4 f4NextTilePos = pNextTile->GetPivotPos();

		float fAngle = float4::GetAngleVectorToVectorDeg360(f4NextTilePos - f4CenterPos, f4TurnPos - f4CenterPos);

		if (fAngle>45.f|| fAngle<-45.f)
		{
			if (fAngle > 45.f && fAngle<180.f)
			{
				std::shared_ptr<WrongMark> pWorngMark = CreateActor<WrongMark>(OrderNum::MAP);
				pWorngMark->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
				pWorngMark->SetTxt("너무빠름");
			}
			else if (fAngle < -45.f && fAngle > -180.f)
			{
				std::shared_ptr<WrongMark> pWorngMark = CreateActor<WrongMark>(OrderNum::MAP);
				pWorngMark->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
				pWorngMark->SetTxt("너무 느림");
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

		m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile->GlowOn();

		pNextTile->EventOn();
		pNextTile->SetPrevRatio(GetMainCamera()->GetZoomRatio());

		++m_iCurIndex;
	}
}