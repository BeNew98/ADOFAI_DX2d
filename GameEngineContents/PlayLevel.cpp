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