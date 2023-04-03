#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <list>
#include <memory>
#include "GameEngineTransform.h"

// 설명 :
class GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineObject();
	// 소멸자에 virtual => 자식소멸자가 호출되게 하기 위해
	// 순수가상함수 쓰는 이유	=> 자식에게 인터페이스를 강요하기 위해서
	//						=> 그 클래스를 객체화 할수 없게 만들기 위해
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

	GameEngineTransform& GetTransform()
	{
		return Transform;
	}


protected:

private:
	std::string Name = "";
	bool IsActive = true; // 켜졌다 꺼졌다
	bool IsDeath = false; // 죽었다 살았다
	int Order = 0;
	////////////////////////////////////////////////////////////// Transform 기하구조

private:
	GameEngineTransform Transform;

};
