#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include "EditGui.h"


// Ό³Έν :

class EditLevel : public GameEngineLevel
{
	friend class EditGui;
public:
	// constrcuter destructer
	EditLevel();
	~EditLevel();

	// delete Function
	EditLevel(const EditLevel& _Other) = delete;
	EditLevel(EditLevel&& _Other) noexcept = delete;
	EditLevel& operator=(const EditLevel& _Other) = delete;
	EditLevel& operator=(EditLevel&& _Other) noexcept = delete;

	void SetTileInfo(StageInfo _Info)
	{
		m_pStageInfo = _Info;
	}
protected:
	void Start() override;
	void Update(float _Deltatime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	StageInfo m_pStageInfo = {};
	std::shared_ptr<class Planet> m_pRed = nullptr;
	std::shared_ptr<class Planet> m_pBlue = nullptr;
	std::shared_ptr<Planet> m_pCenter = nullptr;
	std::shared_ptr<Planet> m_pTurn = nullptr;

	std::shared_ptr<class EditGui> m_pEditor = nullptr;
	std::shared_ptr<class MyMouse> m_pMouse = nullptr;

	int m_iCurIndex = 0;

	void PlanetSwap();
	void Reset();
};

