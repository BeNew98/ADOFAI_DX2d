#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include "EditGui.h"
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer m_BGM = nullptr;
	bool GetGameEnd()
	{
		return m_bGameEnd;
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
	std::shared_ptr<class TextObj> m_pCountText = nullptr;
	std::shared_ptr<class TextObj> m_pProgressText = nullptr;
	std::shared_ptr<class TextObj> m_pTitleNameText = nullptr;
	std::shared_ptr<class FireWorkEffect> m_pRedFire = nullptr;
	std::shared_ptr<class FireWorkEffect> m_pBlueFire = nullptr;
	std::shared_ptr<class FadeEffect> m_FadeEffect = nullptr;

	bool m_bGameStart = false;
	bool m_bPlaying = false;
	int m_iBPM = 0;
	float m_fReadyTime = 0.f;
	int m_iCurIndex = 0;
	float m_fStartTime = 0.f;

	float m_fProgressPer = 0.f;
	float m_fTotalProgress = 0.f;

	float m_fDistance = 150.f;

	bool m_bGameEnd = false;
	bool m_bGameFail = false;
	bool m_bFireEffectOn = false;
	float m_fFireEffectTime = 0.f;


	void PlanetSwap();
	void Reset();
	void StartMechanism(float _DeltaTime);
	void EndFireWork(float _DeltaTime);
	void TileEventSetting();
};

