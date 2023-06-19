#pragma once

enum class OrderNum
{
	BACKGROUND,
	MAP,
	EFFECT,
	PLANET,

};

enum class ColNum
{
	TILE,
	PLANET,
	PORTAL,
};

enum class TileDeg
{
	Deg0	= 0,
	Deg45	= 45,
	Deg60	= 60,
	Deg90	= 90,
	Deg120	= 120,
	Deg135	= 135,
	Deg225	= 225,
	Deg240	= 240,
	Deg270	= 270,
	Deg300	= 300,
	Deg315	= 315,
	Square = 360,
	Blank,
};

enum class EventType
{
	NONE,
	ZOOM,
	CAMMOVE,
	BLACK,
	ROTATION,

};
