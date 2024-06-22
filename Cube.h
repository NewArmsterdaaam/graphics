#pragma once
#ifndef CUBE_H
#define CUBE_H

class Cube {
	float x, y, z;
public:
	Cube(float xPos, float yPos, float zPos);
	void DrawCube();
	void DrawHammerCube();
};

#endif