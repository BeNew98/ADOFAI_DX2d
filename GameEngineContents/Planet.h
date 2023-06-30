#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Planet : public GameEngineActor
{
public:
	// constrcuter destructer
	Planet();
	~Planet();

	// delete Function
	Planet(const Planet& _Other) = delete;
	Planet(Planet&& _Other) noexcept = delete;
	Planet& operator=(const Planet& _Other) = delete;
	Planet& operator=(Planet&& _Other) noexcept = delete;
	std::shared_ptr<class GameEngineCollision> GetCollision()
	{
		return m_pCollision;
	}

	bool IsCenter()
	{
		return m_bCenter;
	}
	void CenterChange()
	{
		m_bCenter = !m_bCenter;
	}

	void CreateEffect();
	std::shared_ptr<GameEngineCollision> GetCol()
	{
		return m_pCollision;
	}
	void SetGameStart(bool _Value)
	{
		m_bGameStart = _Value;
	}
	void SetGameEnd(bool _Value)
	{
		m_bGameEnd = _Value;
	}
	void SetDistance(float _Dist)
	{
		m_fDistance = _Dist;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	float m_fSpeed =360.f;
	float m_fDistance = 100.f;
	float m_fScaleRatio = 0.f;
	static int m_iUseCount;
	bool m_bCenter = false;
	bool m_bGameStart = false;
	bool m_bGameEnd = false;
	bool m_bStartDistance = false;

	std::shared_ptr<class GameEngineSpriteRenderer> pBall = nullptr;
	std::shared_ptr<GameEngineCollision> m_pCollision = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_pRing = nullptr;
	
};

