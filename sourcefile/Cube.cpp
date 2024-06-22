#include "Cube.h"
#include <GL/glut.h>

Cube::Cube(float xPos, float yPos, float zPos) {
	x = xPos; y = yPos; z = zPos;
}

void Cube::DrawCube() {
	glPushMatrix();

	glTranslatef(x, y, z);

	glBegin(GL_POLYGON);
	//Sets the current normal vector.
	glNormal3f(0.0f, 1.0f, 0.0f);	// normalization 0~1 여기선 이 정규화가 아님을.
	glVertex3f(0.0f, 0.0f, 0.0f);	// top face (checked)
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);	// front face(checked)
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);// right face(checked)
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);	// bottom face
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);// back face
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	glPopMatrix();
}

void Cube::DrawHammerCube() {
	glPushMatrix();

	glTranslatef(x, y, z);

	glBegin(GL_POLYGON);
	//Sets the current normal vector.
	glNormal3f(0.0f, 1.0f, 0.0f);	// normalization 0~1 여기선 이 정규화가 아님을.
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// top face (checked)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// front face(checked)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);// right face(checked)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);	// bottom face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);// back face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	glPopMatrix();
}