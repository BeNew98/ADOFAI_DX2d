#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Level1BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Level1BackGround();
	~Level1BackGround();

	// delete Function
	Level1BackGround(const Level1BackGround& _Other) = delete;
	Level1BackGround(Level1BackGround&& _Other) noexcept = delete;
	Level1BackGround& operator=(const Level1BackGround& _Other) = delete;
	Level1BackGround& operator=(Level1BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
};

