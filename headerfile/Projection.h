/*
	���� ���Ͽ����� main �Լ��� �����Լ� ȣ���ϴ� ��

	void PerspectProjection() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

		// ���� ���ؼ� ��� �̻��ϰ� �ƴ� �� ������
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