#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Planet;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float4 TestColor;
private:
	float Angle = 0.0f;
	std::shared_ptr<Planet> m_pRed;
	std::shared_ptr<Planet> m_pYellow;


};

