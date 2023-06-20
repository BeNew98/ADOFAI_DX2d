#include "PrecompileHeader.h"
#include "EditLevel.h"
#include "EditGui.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tiles.h"
#include "MyMouse.h"
#include "Planet.h"
#include "WrongMark.h"


EditLevel::EditLevel() 
{
}

EditLevel::~EditLevel() 
{
}

void EditLevel::Start()
{

	if (nullptr == GameEngineGUI::FindGUIWindow("LevelEdit"))
	{
		std::shared_ptr<GameEngineGUIWindow> NewWindow = GameEngineGUI::GUIWindowCreate<EditGui>("LevelEdit");
		m_pEditor = std::dynamic_pointer_cast<EditGui>(NewWindow);
	}
}

void EditLevel::Update(float _Deltatime)
{
	PlanetSwap();
	if (GameEngineInput::IsDown("TitleLevel"))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	
	if (GameEngineInput::IsDown("PlayLevel"))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
	
	//if (GameEngineInput::IsDown("CenterLevel"))
	//{
	//	GameEngineCore::ChangeLevel("CenterLevel");
	//}

	if (ImGui::IsMouseDragging(1))
	{
		float4 CurMousePos = GameEngineInput::GetMouseDirection();
		CurMousePos.y = -CurMousePos.y;
		GetMainCamera()->GetTransform()->AddWorldPosition(-CurMousePos);
	}

	if (GameEngineInput::IsDown("CenterLevel"))
	{
		GameEngineCore::ChangeLevel("CenterLevel");
	}
}

void EditLevel::LevelChangeStart()
{	
	m_pEditor->On();

	m_pMouse = CreateActor<MyMouse>();

	
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}

void EditLevel::LevelChangeEnd()
{
	Reset();
	m_pEditor->Off();
}

void EditLevel::PlanetSwap()
{
	if (m_pCenter==nullptr|| m_pTurn==nullptr)
	{
		return;
	}
	if (true == GameEngineInput::IsAnyKey())
	{
		if (m_iCurIndex+1 >= m_pStageInfo.AllTile.size())
		{
			return;
		}
		float4 f4CenterPos = m_pCenter->GetTransform()->GetWorldPosition();
		float4 f4TurnPos = m_pTurn->GetTransform()->GetWorldPosition();
		std::shared_ptr<Tiles> pNextTile = m_pStageInfo.AllTile[m_iCurIndex + 1].m_pTile;
		float4 f4NextTilePos = pNextTile->GetPivotPos();

		float fAngle =float4::GetAngleVectorToVectorDeg360((f4NextTilePos - f4CenterPos),(f4TurnPos - f4CenterPos));

		if (fAngle > 45.f || fAngle < -45.f)
		{
			if (fAngle > 45.f && fAngle < 180.f)
			{
				std::shared_ptr<WrongMark> pWorngMark = CreateActor<WrongMark>(OrderNum::MAP);
				pWorngMark->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
				pWorngMark->SetTxt("너무빠름");
			}
			else if (fAngle < -45.f && fAngle > -180.f)
			{
				std::shared_ptr<WrongMark> pWorngMark = CreateActor<WrongMark>(OrderNum::MAP);
				pWorngMark->GetTransform()->SetLocalPosition(m_pTurn->GetTransform()->GetWorldPosition());
				pWorngMark->SetTxt("너무느림");
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

void EditLevel::Reset()
{
	AllActorDestroy();
	m_pStageInfo = {};
	m_pRed = nullptr;
	m_pBlue = nullptr;
	m_pCenter = nullptr;
	m_pTurn = nullptr;
	m_iCurIndex = 0;
}
