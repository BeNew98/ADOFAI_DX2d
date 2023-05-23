#include "PrecompileHeader.h"
#include "MyMouse.h"

MyMouse::MyMouse() 
{
}

MyMouse::~MyMouse() 
{
}

void MyMouse::Update(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(GameEngineInput::GetMousePosition());
}

