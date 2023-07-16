#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CenterLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CenterLevel();
	~CenterLevel();

	// delete Function
	CenterLevel(const CenterLevel& _Other) = delete;
	CenterLevel(CenterLevel&& _Other) noexcept = delete;
	CenterLevel& operator=(const CenterLevel& _Other) = delete;
	CenterLevel& operator=(CenterLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	std::shared_ptr<class FireWorkEffect> ptr = nullptr;
	std::shared_ptr<class TestEffect>ptr2 = nullptr;
};

