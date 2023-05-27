#pragma once
#include <GameEngineCore\GameEngineLevel.h>


// Ό³Έν :

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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class EditGui> m_pEditor = nullptr;
	std::shared_ptr<class MyMouse> m_pMouse = nullptr;

};

