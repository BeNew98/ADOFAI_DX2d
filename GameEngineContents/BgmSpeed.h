#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BgmSpeed : public GameEngineActor
{
public:
	// constrcuter destructer
	BgmSpeed();
	~BgmSpeed();

	// delete Function
	BgmSpeed(const BgmSpeed& _Other) = delete;
	BgmSpeed(BgmSpeed&& _Other) noexcept = delete;
	BgmSpeed& operator=(const BgmSpeed& _Other) = delete;
	BgmSpeed& operator=(BgmSpeed&& _Other) noexcept = delete;

	void SetType(BpmType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool m_bTrigger = false;
	BpmType m_eType = BpmType::NONE;
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class GameEngineCollision> m_pCollision = nullptr;
};

