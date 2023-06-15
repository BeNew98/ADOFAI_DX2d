#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
class Tiles : public GameEngineActor
{
	friend class SquareGlowEffect;
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

	std::shared_ptr<class RoundGlowEffect> GetRGlow()
	{
		return m_pRGlow;
	}

	std::shared_ptr<class SquareGlowEffect> GetSGlow()
	{
		return m_pSGlow;
	}

	float4 GetPivotPos()
	{
		return m_pCenterPivot->GetTransform()->GetWorldPosition();
	}

	void PivotCal(float _Deg);

	void EventOn()
	{
		m_bEventTrigger = true;
	}
	void SetFunction(std::function<void()> _Ptr)
	{
		m_vecPtr.push_back(_Ptr);
	}

	float4 GetData()
	{
		return m_fData;
	}

	void SetData(float4 _Data)
	{
		m_fData = _Data;
	}
	void SetIndex(int _Idx)
	{
		m_iIndex = _Idx;
	}
	int GetIndex()
	{
		return m_iIndex;
	}

	void AlphaSwitch()
	{
		m_bAlpha = !m_bAlpha;
	}
	bool GetAlphaValue()
	{
		return m_bAlpha;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_pRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_pStartPivot = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_pEndPivot = nullptr;
	std::shared_ptr<class GameEngineComponent> m_pCenterPivot = nullptr;


	float4 m_fData = float4::Zero;
	int m_iIndex = 0;

	bool m_bGlow = false;
	bool m_bAlpha = false;
	float m_fAlpha = 0.f;
	std::shared_ptr<class SquareGlowEffect> m_pSGlow = nullptr;
	std::shared_ptr<class RoundGlowEffect> m_pRGlow = nullptr;
	float4 m_fStartBetPos = float4::Zero;
	float4 m_fEndBetPos = float4::Zero;


	float4 m_fStartCal	= float4::Zero;
	float4 m_fEndCal	= float4::Zero;

	std::shared_ptr<class GameEngineCollision> m_pCollision;


	bool m_bEventTrigger = false;
	std::vector<std::function<void()>> m_vecPtr;

	void EventStart();
};

