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

	void SetFunction(std::function<void()> _Ptr)
	{
		m_Ptr = _Ptr;
	}

protected:
	void Start()override;
	void Update(float _DeltaTime) override;

private:
	std::function<void()> m_Ptr = nullptr;

};

