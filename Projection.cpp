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

	// 여기 안해서 계속 이상하게 됐던 거 같은데 이후 그래픽의 안정감
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}