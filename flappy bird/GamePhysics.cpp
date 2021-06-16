#include "GamePhysics.h"


GamePhysics::GamePhysics(){
	Pos.x = 0;
	Pos.y = 0;
	V.x = 0;
	V.y = 0;
	A.x = 0;
	A.y = 0;
}

GamePhysics::GamePhysics(float posx, float posy, float vx, float vy, float ax, float ay){
	Pos.x = posx;
	Pos.y = posy;
	V.x = vx;
	V.y = vy;
	A.x = ax;
	A.y = ay;
}

GamePhysics::~GamePhysics()
{
}

void GamePhysics::SetV(float vx, float vy){
	V.x = vx;
	V.y = vy;
}

void GamePhysics::SetA(float ax, float ay){
	A.x = ax;
	A.y = ay;
}

void GamePhysics::SetPos(float x, float y){
	Pos.x = x;
	Pos.y = y;
}

void GamePhysics::ShiftMove(){
	Pos = Pos + V;
	V = V + A;
}

void GamePhysics::UniformMove(){
	Pos = Pos + V;
}

