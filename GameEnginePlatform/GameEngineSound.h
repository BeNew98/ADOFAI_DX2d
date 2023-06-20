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
	void SetLoop(int _Count = -1)
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
	void SetPosition(float _StartSecond, FMOD_TIMEUNIT _TimeUnit = FMOD_TIMEUNIT_MS)
	{
		Channel->setPosition(static_cast<UINT>(_StartSecond * 1000.f), _TimeUnit);
	}
	void SetLoopPoint(float _StartSecond, float _EndSecond,FMOD_TIMEUNIT _TimeUnit = FMOD_TIMEUNIT_MS)
	{
		Channel->setLoopPoints(static_cast<UINT>(_StartSecond * 1000.f), _TimeUnit, static_cast<UINT>(_EndSecond * 1000.f), _TimeUnit);
	}
};

// 설명 :
// 이녀석 자체가 사운드 파일 역할도 합니다.
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
	// 시퀸스
	// 연관
	// 어뎁터

	// map 노드형 연관 컨테이너
	// Hash기반 맵입니다. 

	FMOD::Sound* FMODSound = nullptr;

};

