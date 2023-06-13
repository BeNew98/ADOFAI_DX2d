#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestScreen : public GameEngineActor
{
public:
	// constrcuter destructer
	TestScreen();
	~TestScreen();

	// delete Function
	TestScreen(const TestScreen& _Other) = delete;
	TestScreen(TestScreen&& _Other) noexcept = delete;
	TestScreen& operator=(const TestScreen& _Other) = delete;
	TestScreen& operator=(TestScreen&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

