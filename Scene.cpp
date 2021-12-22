#include <GL/glut.h>
#include <math.h>
#include <string>
#include <FreeImage.h>

void renderScene(void);
void changeSize(int w, int n);
GLuint LoadTexture(std::string filename);
void createTree(GLfloat treeX, GLfloat treeY, GLfloat treeZ, GLfloat height);
void createBird(GLfloat birdX, GLfloat birdY, GLfloat birdZ, double dist);


GLuint textureBottom;
GLuint textureOther;
GLuint textureLeaves;
GLuint textureTrunk;
const float PI = 3.141592f;


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

	glutDisplayFunc(renderScene);
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
	
	createBird(10.0f, 10.0f, 20.0f, 40.0);
	
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
void createBird(GLfloat birdX, GLfloat birdY, GLfloat birdZ, double dist) {
  // Башка
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureBody);
  glTranslatef(birdX + dist, birdY, birdZ);
  glutSolidSphere(5, 100, 20);
  glDisable(GL_TEXTURE_2D);
  //glColor3f(1.0, 1.0, 0.0);

  // Клюв
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureBeak);
  glBegin(GL_TRIANGLES);
  glVertex3f(2.5f, 0.0f, 5.0f);
  glVertex3f(2.5f, 0.0f, -5.0f);
  glVertex3f(15.0f, 0, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  // Глаза
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureEyeballs);
  glTranslatef(2.5f, 2.5f, 2.5f);
  glutSolidSphere(2.5, 100, 20);
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureDots);
  //glColor3f(0, 0, 0);
  glTranslatef(2.0f, 0, 2.0f);
  glutSolidSphere(0.5, 40, 20);
  glTranslatef(-2.0f, 2.0, -2.0f);
  glTranslatef(-2.5f, -2.5f, -2.5f);
  glDisable(GL_TEXTURE_2D);
  
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureEyeballs);
  //glColor3f(1, 1, 1);
  glTranslatef(2.5f, 2.5f, -2.5f);
  glutSolidSphere(2.5, 100, 20);
  glDisable(GL_TEXTURE_2D);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureDots);
   //glColor3f(0, 0, 0);
  glTranslatef(2.0f, 0, -2.0f);
  glutSolidSphere(0.5, 40, 20);
  glTranslatef(-2.0f, 0, 2.0f);
  glTranslatef(-2.5f, -2.5f, 2.5f);
  glDisable(GL_TEXTURE_2D);
  
  glTranslatef(-birdX - dist, -birdY, -birdZ);
}
