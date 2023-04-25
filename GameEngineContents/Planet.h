#pragma once

// Ό³Έν :
class Planet
{
public:
	// constrcuter destructer
	Planet();
	~Planet();

	// delete Function
	Planet(const Planet& _Other) = delete;
	Planet(Planet&& _Other) noexcept = delete;
	Planet& operator=(const Planet& _Other) = delete;
	Planet& operator=(Planet&& _Other) noexcept = delete;

protected:

private:

};

