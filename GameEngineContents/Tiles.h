#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "EditGui.h"

struct TileEvent
{
	friend class Tiles;
	friend class PlayLevel;
public:
	EventType Type = EventType::NONE;
	float Ratio=0.f;
	float Time=0.f;
private:
	bool End= false;
};
// 설명 :
class Tiles : public GameEngineActor
{
	friend class SquareGlowEffect;
	friend class Player;
	friend class PlayLevel;
public:
	// constrcuter destructer
	Tiles();
	~Tiles();

	// delete Function
	Tiles(const Tiles& _Other) = delete;
	Tiles(Tiles&& _Other) noexcept = delete;
	Tiles& operator=(const Tiles& _Other) = delete;
	Tiles& operator=(Tiles&& _Other) noexcept = delete;

	void SetSpeedObj(BpmType _Type);
	
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

	void AlphaSwitch(bool _Value)
	{
		m_bAlpha = _Value;
	}
	bool GetAlphaValue()
	{
		return m_bAlpha;
	}

	//Ratio는 Zoom = 증감 배율, Move = 이동속도(?), Rotation은 회전각도
	void SetTileEvent(EventType _Type, float _Ratio, float _Time)
	{
		TileEvent Evt = {};
		Evt.Type = _Type;
		Evt.Ratio=_Ratio;
		Evt.Time= _Time;

		m_mapAllEvent[Evt.Type].push_back(Evt);		
	}

	void SetPrevRatio(float _Ratio)
	{
		m_fPrevZoomRatio = _Ratio;
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
	float m_fPrevZoomRatio = 0.f;
	float m_fPrevRotRatio = 0.f;
	float m_fPrevPosRatio = 0.f;
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

	std::shared_ptr<class GameEngineCollision> m_pCollision= nullptr;
	std::map<EventType ,std::vector<TileEvent>> m_mapAllEvent;
	bool m_bEventTrigger = false;


	bool m_bZoomTrigger = false;
	bool m_bMoveTrigger = false;
	bool m_bRotTrigger = false;
	bool m_bMonoTrigger = false;

	void EventStart(float _DeltaTime);
	void ZoomEvent(float _DeltaTime);
	void MoveEvent(float _DeltaTime);
	void RotationEvent(float _DeltaTime);
	void MonoEvent();
};

