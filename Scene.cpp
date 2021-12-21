#include <GL/glut.h>
#include <math.h>
#include <string>
#include <FreeImage.h>

void renderScene(void);
void changeSize(int w, int n);
GLuint LoadTexture(std::string filename);

GLuint textureBottom;
GLuint textureOther;

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
	GLfloat position[] = { 0, 38, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

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

