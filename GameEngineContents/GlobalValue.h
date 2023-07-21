#pragma once

// Ό³Έν :
struct Accuracy
{
	int s_iPerfect = 0;
	int s_iEarlyPerfect = 0;
	int s_iLatePerfect = 0;
};
class GlobalValue
{
public:

	static GlobalValue* GetInst()
	{
		static GlobalValue Inst;
		return &Inst;
	}
	// constrcuter destructer
	GlobalValue();
	~GlobalValue();

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;
	std::vector<Accuracy> vec_Accuracy;

protected:

private:
};

