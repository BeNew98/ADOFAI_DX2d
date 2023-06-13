#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestObject : public GameEngineActor
{
public:
	// constrcuter destructer
	TestObject();
	~TestObject();

	// delete Function
	TestObject(const TestObject& _Other) = delete;
	TestObject(TestObject&& _Other) noexcept = delete;
	TestObject& operator=(const TestObject& _Other) = delete;
	TestObject& operator=(TestObject&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
};

