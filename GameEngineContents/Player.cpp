#include "Player.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>


Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Update(float _Delta)
{
}

float Angle = 0.0f;

void Player::Render(float _Delta)
{
	HDC dc = GameEngineWindow::GetWindowBackBufferHdc();

	const int VertexCount = 4;

	float4 Pos = { 640,360 };

	float4 ArrVerTex[VertexCount];

	ArrVerTex[0] = { -50,-50 };
	ArrVerTex[1] = { 50,-50 };
	ArrVerTex[2] = { 50,50 };
	ArrVerTex[3] = { -50,50 };

	POINT ArrPoint[VertexCount];

	Angle += _Delta *360.f;

	//ũ���̰���
	//	ũ��
	//	����
	//	�̵�
	//	����
	//	�θ�

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVerTex[i].RotaitonZDeg(Angle);
		ArrVerTex[i] += Pos;

		ArrPoint[i] = ArrVerTex[i].ToWindowPOINT();
	}

	Polygon(dc, ArrPoint, VertexCount);
}

