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
	int m_iCurIndex = 0;
	float m_fAngle = 0.0f;
	bool m_bTurn = false;
	bool m_bMoveControl = false;
	float m_fLerpTime = 0.f;

	class EditGui* m_pEditor = nullptr;

	std::shared_ptr<Planet> m_pRed;
	std::shared_ptr<Planet> m_pBlue;
	std::shared_ptr<Planet> m_pCenter;
	std::shared_ptr<Planet> m_pTurn;

	void PlanetSwap(float _Deltatime);
	void CamMoveLerp(float _Ratio);
};

