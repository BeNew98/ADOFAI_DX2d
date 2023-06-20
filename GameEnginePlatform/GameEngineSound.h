#pragma once
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>
#include <string_view>
#include <unordered_map> 

class GameEngineSoundPlayer
{
private:
	FMOD::Channel* Channel = nullptr;

public:
	GameEngineSoundPlayer()
	{

	}

	GameEngineSoundPlayer(FMOD::Channel* _Channel)
		: Channel(_Channel)
	{

	}

	void Stop()
	{
		Channel->stop();
	}
	void SetPitch(float _Pitch)
	{
		Channel->setPitch(_Pitch);
	}
	void SetVolume(float _Volume)
	{
		Channel->setVolume(_Volume);
	}
	void SetLoopCount(int _Count)
	{
		Channel->setLoopCount(_Count);
	}
	void SetMute(bool _Value)
	{
		Channel->setMute(_Value);
	}
	void SetPause(bool _Value)
	{
		Channel->setPaused(_Value);
	}
};

// ���� :
// �̳༮ ��ü�� ���� ���� ���ҵ� �մϴ�.
class GameEngineSound
{
private: // manager
	static std::unordered_map<std::string, std::shared_ptr<GameEngineSound>> AllSound;


public:
	static void ResourcesClear();

	static void SoundUpdate();

	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

	static void Load(const std::string_view& _Path);

	static void Load(const std::string_view& _Name, const std::string_view& _Path);

	static GameEngineSoundPlayer Play(const std::string_view& _Name);

protected:

private:
	void SoundLoad(const std::string_view& _Path);
	FMOD::Channel* SoundPlay();
	// ������
	// ����
	// ���

	// map ����� ���� �����̳�
	// Hash��� ���Դϴ�. 

	FMOD::Sound* FMODSound = nullptr;

};

