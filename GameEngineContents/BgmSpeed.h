#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class BgmSpeed : public GameEngineActor
{
public:
	// constrcuter destructer
	BgmSpeed();
	~BgmSpeed();

	// delete Function
	BgmSpeed(const BgmSpeed& _Other) = delete;
	BgmSpeed(BgmSpeed&& _Other) noexcept = delete;
	BgmSpeed& operator=(const BgmSpeed& _Other) = delete;
	BgmSpeed& operator=(BgmSpeed&& _Other) noexcept = delete;

	void SetType(BpmType _Type)
	{
		m_eType = _Type;

		switch (m_eType)
		{
		case BpmType::NONE:
		{
			MsgAssert("NONE으로 세팅 할 수 없습니다.");
			return;
		}
			break;
		case BpmType::RABBIT:
		{
			m_pRenderer->SetScaleToTexture("tile_rabbit_light_new0_Sprite.png");
		}
			break;
		case BpmType::SNAIL:
		{
			m_pRenderer->SetScaleToTexture("tile_snail_light_new0_Sprite.png");
		}
			break;
		case BpmType::DOUBLE_RABBIT:
		{
			m_pRenderer->SetScaleToTexture("tile_rabbit_double_light_new0_Sprite.png");
		}
			break;
		case BpmType::DOUBLE_SNAIL:
		{
			m_pRenderer->SetScaleToTexture("tile_snail_double_light_new0_Sprite.png");
		}
			break;
		}
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool m_bTrigger = false;
	BpmType m_eType = BpmType::NONE;
	std::shared_ptr<class GameEngineSpriteRenderer> m_pRenderer = nullptr;
	std::shared_ptr<class GameEngineCollision> m_pCollision = nullptr;
};

