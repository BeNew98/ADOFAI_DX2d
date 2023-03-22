#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <list>
#include <memory>

// 설명 :
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject() = 0;

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	void Death()
	{
		IsDeath = true;
	}
	
	// 동적할당 1번을 줄이려고.
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	GameEngineObject* GetParent()
	{
		return Parent;
	}


protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	std::string Name = "";
	bool IsActive = true; // 켜졌다 꺼졌다
	bool IsDeath = false; // 죽었다 살았다.
	int Order = 0;

	GameEngineObject* Parent;

	std::list<std::shared_ptr<GameEngineObject>> Child;

	////////////////////////////////////////////////////////////// Transform 기하구조

public:
	float4 GetPos()
	{
		return Pos;
	}

private:
	float4 Pos;

};
