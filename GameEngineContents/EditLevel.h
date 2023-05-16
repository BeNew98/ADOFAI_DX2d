#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// ���� :
class EditLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EditLevel();
	~EditLevel();

	// delete Function
	EditLevel(const EditLevel& _Other) = delete;
	EditLevel(EditLevel&& _Other) noexcept = delete;
	EditLevel& operator=(const EditLevel& _Other) = delete;
	EditLevel& operator=(EditLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Deltatime) override;

private:

};
