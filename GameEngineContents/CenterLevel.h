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

	static class GameEngineSoundPlayer Bgm;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	float testtime = 0.f;
	std::shared_ptr<class FireWorkEffect> ptr = nullptr;
	std::shared_ptr<class FireWorkEffect> ptr2 = nullptr;
};

