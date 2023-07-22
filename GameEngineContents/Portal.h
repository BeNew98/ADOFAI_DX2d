#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class Portal : public GameEngineActor
{
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;
	void EventOn()
	{
		m_EventTrigger = true;
	}
	void SetFunction(std::function<void()> _Ptr)
	{
		m_Ptr = _Ptr;
	}

	void SetText( std::shared_ptr<class TextObj> _Text)
	{
		m_pText = _Text;
	}

	float4 GetAccPosition()
	{
		return m_pAccuracyCol->GetTransform()->GetWorldPosition();
	}
	

	
protected:
	void Start()override;
	void Update(float _DeltaTime) override;

private:
	bool m_EventTrigger = false;
	float m_fTextTime = 0.f;
	
	std::shared_ptr<class GameEngineCollision> m_pCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_pAccuracyCol = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_pEffect = nullptr;
	std::function<void()> m_Ptr = nullptr;
	std::shared_ptr<class TextObj>  m_pText = nullptr;

};

