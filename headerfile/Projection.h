/*
	기존 파일에서는 main 함수서 서브함수 호출하는 식

	void PerspectProjection() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

		// 여기 안해서 계속 이상하게 됐던 거 같은데
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void OrthoProjection() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(120, 1.0, 0.2, 5.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
*/

#pragma once
#ifndef PROJECTION_H
#define PROJECTION_H

class Projection {
public:
	Projection();
	void Perspective();
	void Ortho();
};

#endif