#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
class Tiles : public GameEngineActor
{
	friend class Player;
public:
	// constrcuter destructer
	Tiles();
	~Tiles();

	// delete Function
	Tiles(const Tiles& _Other) = delete;
	Tiles(Tiles&& _Other) noexcept = delete;
	Tiles& operator=(const Tiles& _Other) = delete;
	Tiles& operator=(Tiles&& _Other) noexcept = delete;

	
	void CreateTile(TileDeg _TileDeg);

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_pRender;
	}


	float4 GetStartPivotPos()
	{
		return m_pStartPivot->GetTransform()->GetWorldPosition();
	}
	float4 GetEndPivotPos()
	{
		return m_pEndPivot->GetTransform()->GetWorldPosition();
	}

	float4 GetStartBetPos()
	{
		return m_fStartBetPos;
	}
	float4 GetEndBetPos()
	{
		return m_fEndBetPos;
	}

	std::shared_ptr<class GameEngineCollision> GetCol()
	{
		return m_pCollision;
	}

	void GlowOn()
	{
		m_bGlow = true;
	}
	
	void DeathPivot()
	{
		m_pStartPivot->Death();
		m_pEndPivot->Death();
	}

	std::shared_ptr<class GlowEffect> GetGlow()
	{
		return m_pGlow;
	}

	void PivotCal(float _Deg);
	void SetMulColor(float4 _Color);
	void SetPlusColor(float4 _Color);

	float4 m_fData = float4::Zero;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_pRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_pStartPivot = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_pEndPivot = nullptr;

	bool m_bGlow = false;
	std::shared_ptr<class GlowEffect> m_pGlow = nullptr;
	float4 m_fStartBetPos = float4::Zero;
	float4 m_fEndBetPos = float4::Zero;


	float4 m_fStartCal	= float4::Zero;
	float4 m_fEndCal	= float4::Zero;

	std::shared_ptr<class GameEngineCollision> m_pCollision;
};

