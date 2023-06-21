#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include "EditGui.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

	GameEnginePixelColor Color = {2,2,2,2};
	GameEngineSoundPlayer m_BGM = nullptr;

	float GetTime()
	{
		return m_fTime;
	}
	bool GetGlowValue()
	{
		return m_bGlow;
	}


protected:
	void Update(float _DeltaTime) override;
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	StageInfo m_pStageInfo = {};
	std::shared_ptr<class Planet> m_pRed = nullptr;
	std::shared_ptr<class Planet> m_pBlue = nullptr;
	std::shared_ptr<Planet> m_pCenter = nullptr;
	std::shared_ptr<Planet> m_pTurn = nullptr;

	std::shared_ptr<class BlackScreen> m_pBlackScreen = nullptr;
	std::shared_ptr<class TitleLogo> m_pLogo = nullptr;
	void CenterCheck();

	int m_iCurIndex = 0;
	float m_fLerpTime = 0.f;

	float4 m_fCurTilePos = float4::Zero;
	float4 m_fPrevTilePos = float4::Zero;

	float m_fTime = 0.f;
	bool m_bGlow = false;
	float m_fGlowRatio = 0.f;
	float m_fSpeed = 0.f;
	bool m_bGameStart = false;



	std::shared_ptr<class Portal> m_pPortal1 = nullptr;
	void PlanetSwap();

	void GlowTimeCheck(float _DeltaTime);
};

