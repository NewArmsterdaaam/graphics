#include "Light.h"
#include <GL/glut.h>

Light::Light() {
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//GLfloat	 lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 0.0f, 100.0f, 1.0f };

	/*
		���⼭ ������ �ĸ� ���Ű� �̷�����µ�
		���� ��� ���������ΰ� ���� �̷������
	*/
	glEnable(GL_NORMALIZE);	//glNormal�� ������ �Ϲ� ���Ͱ� ���� ���̷� ����.
	glEnable(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);	//gl_cull_face�� enable�ϸ� �⺻������ ����.
	//glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}