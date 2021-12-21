#include <GL/glut.h>
#include <math.h>
#include <string>

void renderScene(void);
void changeSize(int w, int n);
void drawPlanet(double radiusOrb, double radiusPlanet, double* angle, float r, float g, float b);
void drawSputnik(double radiusOrbPlanet, double radiusOrbSputnik, double radiusSputnik, double* anglePlanet, double* angleSputnik, float r, float g, float b);
void update(void);
double angle0 = 0;
double angle1 = 0;
double angle2 = 50;
double angle3 = -50;
double angle4 = 200;
double angle5 = 300;
double angle6 = 0;
double twicePi = 3.14159;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("OpenGL");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(update);
	
	glutMainLoop();

	return 0;
}


void renderScene(void)
{
	glClearColor(0.0, 0.0, 0.01, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 20, 0, 0, -2, -1, 0, 1);
	glDisable(GL_LIGHTING);
	drawPlanet(0, 1.0, &angle0, 1, 1, 0);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat position[] = { 0, 0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	drawPlanet(2, 0.1, &angle1, 1, 0, 0);
	drawPlanet(3, 0.3, &angle2, 0, 0, 1);
	drawSputnik(3, 0.5, 0.08, &angle2, &angle6, 0.5, 0.5, 0.5);
	drawPlanet(4.5, 0.4, &angle3, 0, 1, 0);
	drawPlanet(6, 0.5, &angle4, 0, 1, 1);
	drawPlanet(8, 0.2, &angle5, 1, 0, 1);

	glutSwapBuffers();

}

void drawPlanet(double radiusOrb, double radiusPlanet, double *angle, float r, float g, float b)
{
	glPushMatrix();
	double coordX = radiusOrb * cos(*angle * twicePi / 360);
	double coordY = radiusOrb * sin(*angle * twicePi / 360);
	glTranslatef(coordX, coordY, 0.0);
	glColor3f(r, g, b);
	glutSolidSphere(radiusPlanet, 30, 30);
	glPopMatrix();
}

void drawSputnik(double radiusOrbPlanet, double radiusOrbSputnik, double radiusSputnik, double* anglePlanet, double* angleSputnik, float r, float g, float b)
{
	glPushMatrix();
	double coordX = radiusOrbPlanet * cos(*anglePlanet * twicePi / 360) +
		radiusOrbSputnik * cos(*angleSputnik * twicePi / 360);
	double coordY = radiusOrbPlanet * sin(*anglePlanet * twicePi / 360) +
		radiusOrbSputnik * sin(*angleSputnik * twicePi / 360);
	glTranslatef(coordX, coordY, 0.0);
	glColor3f(r, g, b);
	glutSolidSphere(radiusSputnik, 30, 30);
	glPopMatrix();
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void update(void)
{
	angle1 += 1;
	if (angle1 >= 360.0)
		angle1 = -360.0;
	angle2 += 0.4;
	if (angle2 >= 360.0)
		angle2 = -360.0;
	angle3 += 1.2;
	if (angle3 >= 360.0)
		angle3 = -360.0;
	angle4 += 0.9;
	if (angle3 >= 360.0)
		angle3 = -360.0;
	angle5 += 0.7;
	if (angle3 >= 360.0)
		angle3 = -360.0;
	angle6 += 5;
	if (angle3 >= 360.0)
		angle3 = -360.0;

	glutPostRedisplay();
}
