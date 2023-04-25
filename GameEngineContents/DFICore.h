#pragma once

// Ό³Έν :
class DFICore
{
public:
	// constrcuter destructer
	DFICore();
	~DFICore();

	// delete Function
	DFICore(const DFICore& _Other) = delete;
	DFICore(DFICore&& _Other) noexcept = delete;
	DFICore& operator=(const DFICore& _Other) = delete;
	DFICore& operator=(DFICore&& _Other) noexcept = delete;

	static void ContentsResourcesCreate();


	static void GameStart();
	static void GameEnd();

protected:

private:
};

