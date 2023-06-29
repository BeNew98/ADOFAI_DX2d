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
	std::shared_ptr<class TextObj> m_pCount = nullptr;

	bool m_bGameStart = false;
	bool m_bPlaying = false;
	int m_iBPM = 0;
	float m_fReadyTime = 0.f;
	int m_iCurIndex = 0;
	float m_fStartTime = 0.f;


	float m_fDistance = 150.f;
	bool m_bStartDistance = false;

	bool m_bGameEnd = false;

	void PlanetSwap();
	void Reset();
};

