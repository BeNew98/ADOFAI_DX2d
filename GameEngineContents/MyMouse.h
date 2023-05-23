#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MyMouse : public GameEngineActor
{
public:
	// constrcuter destructer
	MyMouse();
	~MyMouse();

	// delete Function
	MyMouse(const MyMouse& _Other) = delete;
	MyMouse(MyMouse&& _Other) noexcept = delete;
	MyMouse& operator=(const MyMouse& _Other) = delete;
	MyMouse& operator=(MyMouse&& _Other) noexcept = delete;
	
	static MyMouse* GetMyMouse()
	{
		static MyMouse inst;
		return &inst;
	}
protected:
	void Update(float _DeltaTime) override;

private:

};

