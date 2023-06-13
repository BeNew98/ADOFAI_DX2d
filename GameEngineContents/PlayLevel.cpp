#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "EditGui.h"
#include "Tiles.h"
#include "Planet.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Update(float _DeltaTime)
{
	GetLevel()->GetMainCamera()->GetTransform()->SetWorldPosition(m_pCenter->GetTransform()->GetWorldPosition());

}

void PlayLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}
void PlayLevel::LevelChangeStart()
{
	EditGui::Editor->LoadtoString("");

	m_pStageInfo = EditGui::Editor->GetStageInfo(0);

	m_pRed = CreateActor<Planet>(OrderNum::PLANET);
	m_pBlue = CreateActor<Planet>(OrderNum::PLANET);
	float4 Tilepos = m_pStageInfo.AllTile[12].m_pTile->GetTransform()->GetWorldPosition();
	m_pBlue->GetTransform()->SetParent(m_pRed->GetTransform());
	m_pBlue->GetTransform()->AddLocalPosition({ -100.f,0.f,0.f });
	m_pCenter = m_pRed;
	m_pTurn = m_pBlue;

}

void PlayLevel::LevelChangeEnd()
{
}

void PlayLevel::PlanetSwap()
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
			int CenterX = (ColCenterTile->m_fData.ix());
			int CenterY = (ColCenterTile->m_fData.iy());
			int TurnX = (ColTurnTile->m_fData.ix());
			int TurnY = (ColTurnTile->m_fData.iy());


			if (false == ((CenterX + 1 == TurnX && CenterY == TurnY) ||
				(CenterX == TurnX && CenterY + 1 == TurnY) ||
				(CenterX - 1 == TurnX && CenterY == TurnY) ||
				(CenterX == TurnX && CenterY - 1 == TurnY)) || ColTurnTile->m_fData.iz() == 361)
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

			//m_fLerpTime = 0;
			//
			//++m_iCurIndex;
			//m_fPrevTilePos = m_pStageInfo.AllTile[m_iCurIndex - 1].m_pTile->GetTransform()->GetWorldPosition();
			//m_fCurTilePos = m_pStageInfo.AllTile[m_iCurIndex].m_pTile->GetTransform()->GetWorldPosition();
		}
		CenterCheck();
		return;
	}

}