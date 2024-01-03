#pragma once
#include "Ball.hpp"
void setStartPos(Ball *ball);
bool updateBall(Ball *arr[16], int *scored);
void hittingTheBall(float x, float y, Ball *ball);