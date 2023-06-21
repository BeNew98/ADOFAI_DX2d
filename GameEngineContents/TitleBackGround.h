#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class TitleBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBackGround();
	~TitleBackGround();

	// delete Function
	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
	TitleBackGround& operator=(TitleBackGround&& _Other) noexcept = delete;

protected:
	void Start()override;
	void Update(float _DeltaTime)override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRender = nullptr;
};

