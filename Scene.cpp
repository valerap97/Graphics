#include <GL/glut.h>
#include <math.h>
#include <string>
#include <FreeImage.h>

void renderScene(void);
void changeSize(int w, int n);
GLuint LoadTexture(std::string filename);
void createTree(GLfloat treeX, GLfloat treeY, GLfloat treeZ, GLfloat height);
void createBird(GLfloat birdX, GLfloat birdY, GLfloat birdZ, double dist);
void update(void);
void drawPlanet(double radiusOrb, double radiusPlanet, float height, double* angle, float r, float g, float b);
void drawSputnik(double radiusOrbPlanet, double radiusOrbSputnik, double radiusSputnik, float height, double* anglePlanet, double* angleSputnik, float r, float g, float b);
void drawEyes(double radiusOrbPlanet, double radiusOrbSputnik, double radiusSputnik, float height, double* anglePlanet, double* angleSputnik, float r, float g, float b);

GLuint textureBottom;
GLuint textureOther;
GLuint textureLeaves;
GLuint textureTrunk;
GLuint textureBody;
GLuint textureEyeballs;
GLuint textureDots;
GLuint textureBeak;
const float PI = 3.141592f;

double angle1 = 0;
double angle2 = 0;
double angle3 = 0;
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

	textureBottom = LoadTexture("grass.png");
	textureOther = LoadTexture("sky.png");
	textureLeaves = LoadTexture("leaves.png");
	textureTrunk = LoadTexture("wood.png");
	
	textureBody = LoadTexture("body.png");
	textureEyeballs = LoadTexture("eyeballs.png");
	textureDots = LoadTexture("dots.png");
	textureBeak = LoadTexture("beak.png");

	glutDisplayFunc(renderScene);
	glutIdleFunc(update);
	glutReshapeFunc(changeSize);
	
	glutMainLoop();

	return 0;
}


void renderScene(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 100, 0, 0, 0, 0, 0, 0, 1);
	glDisable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat position[] = { -80.f, 80.0f, 120.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glPushMatrix();
	GLfloat X[] = {-10.0f, -30.0f, 10.0f,50.0f};
	GLfloat Y[] = {-30.0f, -50.0f, -30.0f, -20.0f};
	createTree(X[0], Y[0], 0.0f, 15.0);
	createTree(X[1], Y[1], 6.0f, 30.0);
	createTree(X[2], Y[2], 2.0f, 20.0);
	createTree(X[3], Y[3], 4.0f, 25.0);
	glPopMatrix();

	drawPlanet(30, 10, 20.0f,&angle1, 1, 0, 0);
	drawSputnik(30, 10, 0, 20.0f, &angle1, &angle1, 0.5, 0.5, 0.5);
	drawEyes(30, 10, 0, 20.0f, &angle1, &angle1, 0.5, 0.5, 0.5);

	drawPlanet(20, 8, 10.0f,&angle2, 1, 0, 0);
	drawSputnik(20, 8, 0, 10.0f, &angle2, &angle2, 0.5, 0.5, 0.5);
	drawEyes(20, 8, 0, 10.0f, &angle2, &angle2, 0.5, 0.5, 0.5);

	 drawPlanet(30, 10, 30.0f,&angle3, 1, 0, 0);
	 drawSputnik(30, 10, 0, 30.0f, &angle3, &angle3, 0.5, 0.5, 0.5);
	drawEyes(30, 10, 0, 30.0f, &angle3, &angle3, 0.5, 0.5, 0.5);
	
	glPopMatrix();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureBottom);

	glNormal3f(0, 0, 1);
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-150.0f, -40.0f, -30.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-150.0f, 200.0f, -30.0f);
	glTexCoord2f(1, 1);
	glVertex3f(150.0f, 200.0f, -30.0f);
	glTexCoord2f(1, 0);
	glVertex3f(150.0f, -40.0f, -30.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureOther);

	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(150.0f, -38.0f, -30.0f);
	glTexCoord2f(1, 0);
	glVertex3f(-150.0f, -38.0f, -30.0f);
	glTexCoord2f(1, 1);
	glVertex3f(-150.0f, -38.0f, 100.0f);
	glTexCoord2f(0, 1);
	glVertex3f(150.0f, -38.0f, 100.0f);	

	glEnd();
	glDisable(GL_TEXTURE_2D);



	glutSwapBuffers();
	
}

GLuint LoadTexture(std::string filename)
{
	const char* charFilename = filename.c_str();
	GLuint texture;
	FIBITMAP* bitmap = FreeImage_Load(
		FreeImage_GetFIFFromFilename(charFilename),
		charFilename, PNG_DEFAULT);

	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight,
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FreeImage_Unload(pImage);

	return texture;
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 140.0f);
	glMatrixMode(GL_MODELVIEW);
}

void createTree(GLfloat treeX, GLfloat treeY, GLfloat treeZ, GLfloat height) {
  GLfloat x = 1;
  GLfloat y = 1;
  
  double twicePi = 2.0 * PI;
  float textureRotation = 0.3;
  float radiusCilinder = height/8;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureTrunk);

  glBegin(GL_QUADS);
  x = radiusCilinder * cos(0.0);
  y = radiusCilinder * sin(0.0);
  for (float i = 0; i < 360; i++) {
    glTexCoord2f(((1.0 / 360) * i) - textureRotation, 1.0);
    glNormal3f(treeX + x, treeY + y + height, treeZ);
    glVertex3d(treeX + x, treeY + y + height, treeZ);
    glTexCoord2f(((1.0 / 360) * i) - textureRotation, 0.0);
    glNormal3f(treeX + x, treeY + y + height, treeZ - 2*height);
    glVertex3d(treeX + x, treeY + y + height, treeZ - 2*height);

    x = radiusCilinder * cos((i + 1.0) * twicePi / 360);
    y = radiusCilinder * sin((i + 1.0) * twicePi / 360);
    glTexCoord2f(((1.0 / 360) * (i + 1.0)) - textureRotation, 0.0);
    glNormal3f(treeX + x, treeY + y + height, treeZ - 2*height);
    glVertex3d(treeX + x, treeY + y + height, treeZ - 2*height);
    glTexCoord2f(((1.0 / 360) * (i + 1.0)) - textureRotation, 1.0);
    glNormal3f(treeX + x, treeY + y + height, treeZ - 2*height);
    glVertex3d(treeX + x, treeY + y + height, treeZ);
  }
  glEnd();
  
   glTranslatef(treeX, treeY + height, treeZ);
   glBindTexture(GL_TEXTURE_2D, textureLeaves);
   glutSolidSphere(height / 2, 40, 20);
   glDisable(GL_TEXTURE_2D);
   glTranslatef(treeX, -treeY - height, treeZ);
   glDisable(GL_TEXTURE_2D);
}

void drawPlanet(double radiusOrb, double radiusPlanet, float height, double *angle, float r, float g, float b)
{
  glPushMatrix();
  double coordX = radiusOrb * cos(*angle * twicePi / 360);
  double coordY = radiusOrb * sin(*angle * twicePi / 360);
   glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureBody);
  glTranslatef(coordX, coordY, height);
  glutSolidSphere(radiusPlanet, 30, 30);
    glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  
}

void drawSputnik(double radiusOrbPlanet, double radiusOrbSputnik, double radiusSputnik, float height, double* anglePlanet, double* angleSputnik, float r, float g, float b)
{
  glPushMatrix();
  double coordX = radiusOrbPlanet * cos(*anglePlanet * twicePi / 360) +
    radiusOrbSputnik * cos(*angleSputnik * twicePi / 360);
  double coordY = radiusOrbPlanet * sin(*anglePlanet * twicePi / 360) +
    radiusOrbSputnik * sin(*angleSputnik * twicePi / 360);
   glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureBeak);
  glTranslatef(coordX, coordY, height);
  double coordX1 = 5.0 * cos(*angleSputnik * twicePi / 360);
  double coordY1 = 5.0 * sin(*angleSputnik * twicePi / 360);
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0f,5.0f, 0.0f);
  glVertex3f(0.0f,-5.0f, 0.0f);
  glVertex3f(coordX1+10.0f,coordY1+0.0f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}
void drawEyes(double radiusOrbPlanet, double radiusOrbSputnik, double radiusSputnik, float height, double* anglePlanet, double* angleSputnik, float r, float g, float b)
{
  glPushMatrix();
  double coordX = radiusOrbPlanet * cos(*anglePlanet * twicePi / 360) +
    radiusOrbSputnik * cos(*angleSputnik * twicePi / 360);
  double coordY = radiusOrbPlanet * sin(*anglePlanet * twicePi / 360) +
    radiusOrbSputnik * sin(*angleSputnik * twicePi / 360);
  glTranslatef(coordX, coordY, height);
  double coordX1 = 2.5*cos(*angleSputnik * twicePi / 360);
  double coordY1 = 2.5*sin(*angleSputnik * twicePi / 360);
 glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureEyeballs);
  glTranslatef(coordX1-4.0f, coordY1+5.0f, 0.0f);
  glutSolidSphere(2.5, 100, 20);
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureDots);
  glTranslatef(coordX1-1.5f, coordY1, 0.0f);
  glutSolidSphere(0.5, 40, 20);
  glDisable(GL_TEXTURE_2D);
  
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureEyeballs);
  //glColor3f(1, 1, 1);
  glTranslatef(coordX1-4.0f, coordY1-5.0f, 0.0f);
  glutSolidSphere(2.5, 100, 20);
  glDisable(GL_TEXTURE_2D);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureDots);
   //glColor3f(0, 0, 0);
  glTranslatef(coordX1-1.5f, coordY1, 0.0f);
  glutSolidSphere(0.5, 40, 20);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}


void update(void)
{
	angle1 += 3;
	if (angle1 >= 360.0)
		angle1 = -360.0;
	angle2 += 2;
	if (angle2 >= 360.0)
		angle2 = -360.0;
	 angle3 += 4;
	if (angle3 >= 360.0)
		angle3 = -360.0;
	glutPostRedisplay();
}
