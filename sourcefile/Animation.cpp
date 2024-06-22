#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "GL/glaux.h"
//#include <GL/glaux.h>
#include <iostream>

GLfloat xrot = 0.9f, yrot = 0.8f, zrot = 1.0f;
unsigned int MyTextureObject[1];
AUX_RGBImageRec* pTextureImage[1];  //�ؽ��� ���� ������ ����Ű�� ������

// ��ü ����
#include "Cube.h"
#include "Projection.h"
#include "Light.h"
Cube cube(0.0, 0.0, 0.0);

// for walk
bool arm1_check = true;
bool arm2_check = false;
bool leg1_check = true;
bool leg2_check = false;
GLfloat arm_Delta[2] = { 0.0f, 0.0f };
GLfloat leg_Delta[2] = { 0.0f, 0.0f };

// for jump
bool jumpOn = true;
GLfloat jumpPos = 0.0f;

// walk distance
GLfloat walkThrough = -1.5f;
bool walkOn = true;

// for attack ready
enum myState {DOWN, UP, FINISH};

GLfloat arm_ar=0.0f;
GLfloat leg_ar=0.0f;
myState arm_check_ar = DOWN;
myState leg_check_ar = DOWN;

// for hammer
bool hammerOn = true;
GLfloat hammerAng = -90.0f;

// for VFX
const int vfx_count = 1000;

std::vector<std::vector<GLfloat>> v(3, std::vector<GLfloat>(vfx_count, 0.0f));

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(-0.5f, 0.5f);

int Scene = 0;

void DrawTorso(float xPos, float yPos, float zPos) {
	glPushMatrix();
	glColor3f(256.0 / 255.0, 218.0 / 255.0, 185.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 4.0f, 2.0f);
	cube.DrawCube();
	glPopMatrix();
}
void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(244.0/255.0, 164.0/ 255.0, 96.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 3.0f, 2.0f);	
	cube.DrawCube();

	/*
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);
	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(0.0f, -0.1f, 0.05f);
	cube.DrawCube();
	glPopMatrix();
	*/
	glPopMatrix();
}
void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(256.0 / 255.0, 218.0 / 255.0, 185.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glScalef(0.5f, 2.0f, 0.5f);
	cube.DrawCube();
	glPopMatrix();
}
void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(244.0 / 255.0, 164.0 / 255.0, 96.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glScalef(0.5f, 1.0f, 0.5f);		
	cube.DrawCube();
	glPopMatrix();
}
void DrawRobot(float xPos, float yPos, float zPos) {
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	DrawHead(1.5f, 3.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);

	// draw arm
	glPushMatrix();
	glRotatef(arm_Delta[0], 1.0f, 0.0f, 0.0f);
	DrawArm(-1.5f, 0.0f, -0.5f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(arm_Delta[1], 1.0f, 0.0f, 0.0f);
	DrawArm(2.0f, 0.0f, -0.5f);
	glPopMatrix();

	// draw leg
	glPushMatrix();
	glRotatef(leg_Delta[0], 1.0f, 0.0f, 0.0f);
	DrawLeg(0.75f, -4.0f, -0.5f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(leg_Delta[1], 1.0f, 0.0f, 0.0f);
	DrawLeg(-0.25f, -4.0f, -0.5f);
	glPopMatrix();

	glPopMatrix();
}
void DrawHammerHead(float xPos, float yPos, float zPos) {
	glPushMatrix();
	glColor3f(175.0 / 255.0, 238.0 / 255.0, 238.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 3.0f, 2.0f);		
	cube.DrawHammerCube();
	glPopMatrix();
}
void DrawHammerHand(float xPos, float yPos, float zPos) {
	glPushMatrix();
	glColor3f(240.0 / 255.0, 248.0 / 255.0, 255.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glScalef(0.5f, 4.0f, 0.5f);		
	cube.DrawHammerCube();
	glPopMatrix();
}
void DrawHammer(float xPos, float yPos, float zPos) {
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	DrawHammerHead(1.25f, 2.0f, 0.5f);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	DrawHammerHand(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}
void DrawAttackRobot(float xPos, float yPos, float zPos) {
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	DrawHead(1.5f, 3.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);

	// draw arm
	glPushMatrix();
	glRotatef(-arm_ar, 1.0f, 0.0f, 0.0f);
	DrawArm(-1.5f, 0.0f, -0.5f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-arm_ar, 1.0f, 0.0f, 0.0f);
	DrawArm(2.0f, 0.0f, -0.5f);
	glPopMatrix();

	// draw leg
	glPushMatrix();
	glRotatef(-leg_ar, 1.0f, 0.0f, 0.0f);
	DrawLeg(0.75f, -4.0f, -0.5f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-leg_ar, 1.0f, 0.0f, 0.0f);
	DrawLeg(-0.25f, -4.0f, -0.5f);
	glPopMatrix();

	// draw hammer
	glRotatef(hammerAng, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	DrawHammer(1.5f, 8.0f, 0.0f);

	glPopMatrix();
}
void DrawVFX(float xPos, float yPos, float zPos, float xrot, float yrot, float zrot) {
	glPushMatrix();
	glColor3f(176.0/255.0, 196.0 / 255.0, 222.0 / 255.0);
	glTranslatef(xPos, yPos, zPos);
	glTranslatef(xrot, yrot, zrot);
	glScalef(0.5f, 0.5f, 0.5f);
	cube.DrawCube();
	glPopMatrix();
}

/*
	�� �ݹ� �Լ��� ���� ��� ��ȭ�Ǵ� ������ ���� �ִ�
	��ü�� �����ϸ� private or public ������ �� ������ �����ϴ� �޼ҵ�
*/
void Walk_callback(int Value) {
	/*
		bool arm1_check = true;
		bool arm2_check = false;
		bool leg1_check = true;
		bool leg2_check = false;
		GLfloat arm_Delta[2] = { 0.0f, 0.0f };
		GLfloat leg_Delta[2] = { 0.0f, 0.0f };
	*/
	GLfloat speed = 0.8f;
	// arm1
	if (arm1_check) {
		arm_Delta[0] = arm_Delta[0] + speed;
	}
	else
	{
		arm_Delta[0] = arm_Delta[0] - speed;
	}
	if (arm_Delta[0] >= 15.0f) {
		arm1_check = false;
	}
	if (arm_Delta[0] <= -15.0f) {
		arm1_check = true;
	}
	//WalkAnimate(arm_Delta[0], arm1_check, 0.8f);
	// arm2
	if (arm2_check) {
		arm_Delta[1] = arm_Delta[1] + speed;
	}
	else
	{
		arm_Delta[1] = arm_Delta[1] - speed;
	}
	if (arm_Delta[1] >= 15.0f) {
		arm2_check = false;
	}
	if (arm_Delta[1] <= -15.0f) {
		arm2_check = true;
	}
	// leg1
	if (leg1_check) {
		leg_Delta[0] = leg_Delta[0] + speed;
	}
	else
	{
		leg_Delta[0] = leg_Delta[0] - speed;
	}
	if (leg_Delta[0] >= 15.0f) {
		leg1_check = false;
	}
	if (leg_Delta[0] <= -15.0f) {
		leg1_check = true;
	}
	// leg2
	if (leg2_check) {
		leg_Delta[1] = leg_Delta[1] + speed;
	}
	else
	{
		leg_Delta[1] = leg_Delta[1] - speed;
	}
	if (leg_Delta[1] >= 15.0f) {
		leg2_check = false;
	}
	if (leg_Delta[1] <= -15.0f) {
		leg2_check = true;
	}
	glutPostRedisplay();
	glutTimerFunc(10, Walk_callback, 1);
}
void WalkForward_callback(int Value) {
	/*
		GLfloat walkThrough = -1.5f;
		bool walkOn = true;
	*/
	if (walkOn) {
		walkThrough = walkThrough + 0.01f;
	}

	if (walkThrough >= 0.0f) {
		walkOn = false;
		Scene = 1;
		glutPostRedisplay();
	}
	else {
		glutPostRedisplay();
		glutTimerFunc(10, WalkForward_callback, 1);
	}
}
void Jump_callback(int value) {
	/*
		bool jumpOn = true;
		GLfloat jumpPos = 0.0f;
	*/
	if (Scene == 0) {
		//std::cout << "jump callback �� �����..." << std::endl;
		glutTimerFunc(10, Jump_callback, 1);
	}
	else {
		if (jumpOn) {
			jumpPos = jumpPos + 0.025f;
		}
		else {
			jumpPos = jumpPos - 0.025f;
		}
		if (jumpPos >= 0.5f) {
			jumpOn = false;
		}
		// �ٽ� �������� �� �� �Լ��� �ٽ� ȣ��Ǹ� �ȵǴµ�
		if (jumpPos > 0.0f) {
			glutPostRedisplay();
			glutTimerFunc(10, Jump_callback, 1);
		}
		else if (jumpPos <= 0.0f) {
			jumpPos = 0.0f;
			glutPostRedisplay();
		}
	}
}
void Attack_callback(int value) {
	/*
		GLfloat arm_ar=0.0f;
		GLfloat leg_ar=0.0f;
		myState arm_check_ar = DOWN;
		myState leg_check_ar = DOWN;

		bool hammerOn = true;
		GLfloat hammerAng = -90.0f;
	*/
	//std::cout << "attack start" << std::endl;
	if (Scene == 0) {
		//std::cout << "attack callback �� �����..." << std::endl;
		glutTimerFunc(10, Attack_callback, 1);
	}
	else {
		GLfloat armspeed = 5.0f;
		GLfloat legspeed = 2.0f;
		GLfloat hamspeed = 3.25f;
		// first, arm
		if (arm_check_ar == DOWN) {
			arm_ar = arm_ar + armspeed;
		}
		else if (arm_check_ar == UP) {
			arm_ar = arm_ar - armspeed;
		}
		if (arm_ar >= 150.0f) {
			arm_check_ar = UP;
		}
		if (arm_ar <= 0.0f) {
			// �ִϸ��̼��� ��������
			arm_ar = 0.0f;
			arm_check_ar = FINISH;
		}
		// second, leg
		if (leg_check_ar == DOWN) {
			leg_ar = leg_ar + legspeed;
		}
		else if (leg_check_ar == UP) {
			leg_ar = leg_ar - legspeed;
		}
		if (leg_ar >= 60.0f) {
			leg_check_ar = UP;
		}
		if (leg_ar <= 0.0f) {
			// �ִϸ��̼��� ��������
			leg_ar = 0.0f;
			leg_check_ar = FINISH;
		}

		// for hammer
		if (hammerOn) {
			// start : -90.0, end : 90.0
			hammerAng = hammerAng + hamspeed;
		}
		if (hammerAng >= 120.0f) {
			hammerOn = false;
			Scene = 2;
		}

		glutPostRedisplay();
		glutTimerFunc(10, Attack_callback, 1);
	}
}
void VFX_callback(int value) {
	if (Scene == 0 || Scene == 1) {
		glutTimerFunc(10, VFX_callback, 1);
	}
	else {
		for (int j = 0;j < vfx_count;j++) {
			v[0][j] = v[0][j] + dis(gen);
			v[1][j] = v[1][j] + dis(gen);
			v[2][j] = v[2][j] + dis(gen);
		}

		glutPostRedisplay();
		glutTimerFunc(10, VFX_callback, 1);
	}
}

/*
	�� ��鿡 �´� �ִϸ��̼�
*/
void WalkAnimation() {
	/*
		�ȱ�� Z Azis -1.5 -> 0.5 ���� �ɾ ������
	*/
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();		// ȸ�� ��� ���� ��ǥ�� �����ϱ�	
	glLoadIdentity();

	glRotatef(15.0f, 1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, walkThrough);
	glScalef(0.2f, 0.2f, 0.2f);
	DrawRobot(0.0f, 0.0f, 0.0f);

	glPopMatrix();
}
void AttackAnimation() {
	//glMatrixMode(GL_MODELVIEW);
	//sndPlaySound(TEXT("C/Users/himchan/Downloads/Pewsoundeffect.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();		// ȸ�� ��� ���� ��ǥ�� �����ϱ�	
	glLoadIdentity();

	glRotatef(15.0f, 1.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, jumpPos, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	DrawAttackRobot(0.0, 0.0, 0.0);	// �ȴٸ� ȸ���� ��� �Ǿ�� �ϴ� ��Ȳ�̹Ƿ� �� ��鿡���� Ÿ�̸Ӹ� ���� �������� ��

	glPopMatrix();
}
void VFXAnimation() {
	/*
		drawVFX �� �ϳ��� ����Ʈ�� ���Ǵµ�, �ִϸ��̼� ����Ǹ� ���� ���� �� ����Ʈ�� ������ �������� �����Ǿ�� ��
		�� ��ġ�� �������� �κп��� ���۵Ǿ� �� �������� ��� �̵��ϴ� ��.
	*/
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();		// ȸ�� ��� ���� ��ǥ�� �����ϱ�	
	glLoadIdentity();

	glPushMatrix();
	glRotatef(15.0f, 1.0f, 1.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	DrawRobot(0.0, 0.0, 0.0);	// �ȴٸ� ȸ���� ��� �Ǿ�� �ϴ� ��Ȳ�̹Ƿ� �� ��鿡���� Ÿ�̸Ӹ� ���� �������� ��
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < vfx_count; i++) {
		glRotatef(15.0f, 1.0f, 1.0f, 0.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		DrawVFX(0.0, 0.0, 0.0, v[0][i], v[1][i], v[2][i]);
	}
	glPopMatrix();

	glPopMatrix();
}

void RenderScene() {
	/*
		setupLight���� �ĸ� ���� ���μ���
		���⼭ ������ ���� �۾��� ���� ���� �۾��� �̷������ �Ǵµ� ���� �۾��� x

		������ ȭ���� �׸��� �Լ�
	*/
	glEnable(GL_DEPTH_TEST);				// enable depth testing (z-buffer?)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen and depth buffer(for new frame!!)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// clear to black
	glColor3f(0.5, 0.5, 0.5);

	glViewport(0, 0, 500, 500);
	if (Scene == 0) {
		WalkAnimation();
	}
	else if(Scene == 1) {
		AttackAnimation();
	}
	else if (Scene == 2) {
		VFXAnimation();
	}

	glutSwapBuffers();
}
AUX_RGBImageRec* LoadBMP(const char* szFilename) {
	FILE* pFile = NULL;
	if (!szFilename) {
		return NULL;
	}
	fopen_s(&pFile, szFilename, "r");
	if (pFile) {
		fclose(pFile);
		return auxDIBImageLoad(szFilename);     //���Ϸκ��� �޸𸮷�
	}
	return NULL;
}
int LoadGLTextures(const char* szFilePath) {       //������ �ε��ϰ� �ؽ��ķ� ��ȯ
	int Status = FALSE;
	glClearColor(0.0, 0.0, 0.0, 0.5);
	memset(pTextureImage, 0, sizeof(void*) * 1);    //�����͸� �η�

	if (pTextureImage[0] = LoadBMP(szFilePath)) {   //��Ʈ���� �ε��ϰ� ����Ȯ��
		Status = TRUE;                              //���� �÷��� True��
		glGenTextures(1, &MyTextureObject[0]);      //�ؽ��� ����
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
	if (pTextureImage[0]) {                 //�ؽ��İ� �����ϸ�
		if (pTextureImage[0]->data) {       //�ؽ��� ������ �����ϸ�
			free(pTextureImage[0]->data);   //�ؽ��� ������� �ݳ�
		}
		free(pTextureImage[0]);             //�ؽ��� �ݳ�
	}
	return Status;
}
void AnimationTimerController() {
	/*
		main �Լ��� �Ϻκ��� ���ȭ
		��� timer  �Լ��� main �� �����ϵ�, �� �ݹ� �Լ����� ����� ��ȭ�� ���� ���ǿ� �°� �ڵ带 �����ϸ� ��
	*/
	glutTimerFunc(10, Walk_callback, 1);
	glutTimerFunc(10, WalkForward_callback, 1);
	glutTimerFunc(10, Jump_callback, 1);
	glutTimerFunc(10, Attack_callback, 1);
	glutTimerFunc(10, VFX_callback, 1);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// using double buffer and true color mode
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2019305083 Ȳ����");
	Projection projection;
	projection.Ortho();
	Light InitLight;
	glutDisplayFunc(RenderScene);

	// �ݹ� �Լ��� ����غ���. �ѹ��� �ݹ� �ϴ� �Ÿ� ���⼭ �ѹ��� ȣ���ϰ� �ݹ� �Լ� ���ο����� ȣ���� �ʿ� ����
	AnimationTimerController();
	
	/*
	// ���� �ؽ��� �۾�
	if (LoadGLTextures("")) {
		//glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glutMainLoop();
	}
	*/
	glutMainLoop();
	return 0;
}