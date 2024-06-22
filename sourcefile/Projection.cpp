#include "Projection.h"
#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

Projection::Projection() {}

void Projection::Perspective() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, 1.0, 0.2, 5.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Projection::Ortho() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

	// ���� ���ؼ� ��� �̻��ϰ� �ƴ� �� ������ ���� �׷����� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}