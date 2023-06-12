#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start()override;
	void Update(float _DeltaTime) override;

private:
	bool m_EventTrigger = false;
	std::shared_ptr<class GameEngineCollision> m_pCollision = nullptr;
	std::function<void()> m_Ptr = nullptr;

};

