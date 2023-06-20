#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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

	void SetSpeed(int BPM) 
	{
		if (BPM==0)
		{
			MsgAssert("BPM이 0입니다");
			return;
		}
		m_fSpeed = static_cast<float>(180.f * (BPM / 60.f));
	}



protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	float m_fSpeed =360.f;
	static int m_iUseCount;
	bool m_bCenter = false;
	std::shared_ptr<GameEngineCollision> m_pCollision = nullptr;
};

