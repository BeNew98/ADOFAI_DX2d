#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	float4 TestColor;
private:
	float Angle = 0.0f;
	bool m_bTurn = false;
	bool m_bMoveControl = false;
	std::shared_ptr<Planet> m_pRed;
	std::shared_ptr<Planet> m_pBlue;
	std::shared_ptr<Planet> m_pCenter;
	std::shared_ptr<Planet> m_pTurn;

	void LocalMove(float _DeltaTime);
	void WorldMove(float _DeltaTime);


};

