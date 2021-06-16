#pragma once

#include "parameter.h"

class GamePhysics
{
public:
	POINTF Pos;
	POINTF V;
	POINTF A;
public:
	void SetPos(float x, float y);
	void SetV(float vx, float vy);
	void SetA(float ax, float ay);
	void ShiftMove();
	void UniformMove();
	GamePhysics(float posx, float posy, float vx, float vy, float ax, float ay);
	GamePhysics();
	~GamePhysics();
};

