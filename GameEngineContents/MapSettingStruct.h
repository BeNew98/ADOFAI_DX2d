#pragma once

struct TileInfo
{
	float NextRatio = 0;
	bool Slow = false;
	bool Fast = false;
	bool EndTile = false;
};

struct StageInfo
{
	std::vector<TileInfo> AllTile;
	int BPM = 0;
	float fitch = 0.f;
};