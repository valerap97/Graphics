#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <string>
#include <FreeImage.h>


GLuint textureBottom;
GLuint textureSky;

double dist = 0;

void createTree(GLfloat treeX, GLfloat treeY, GLfloat treeZ, GLfloat height) {
  glColor3f(0.4f, 0.25f, 0);
  GLfloat angle = 0.0;
  GLfloat angle_stepsize = 0.1;
  GLfloat radius = 4;
  GLfloat x = 1;
  GLfloat y = 1;
  
  glBegin(GL_QUAD_STRIP);
  angle = 0.0;
  while (angle < 2 * M_PI + angle_stepsize) {
      x = radius * cos(angle);
      y = radius * sin(angle);
      glVertex3f(treeX + x, treeY, treeZ + y);
      glVertex3f(treeX + x, treeY + height, treeZ + y);
      angle = angle + angle_stepsize;
  }
  glEnd();

  glColor3f(0, 1, 0);
  glTranslatef(treeX, treeY + height, treeZ);
  glutSolidSphere(height / 2, 40, 20);
  glTranslatef(-treeX, -treeY - height, -treeZ);
}

void createBird(GLfloat birdX, GLfloat birdY, GLfloat birdZ) {
  // Башка
  glColor3f(1, 0, 0);
  glTranslatef(birdX + dist, birdY, birdZ);
  glutSolidSphere(5, 100, 20);
  glColor3f(1, 1, 0);

  // Клюв
  glBegin(GL_TRIANGLES);
  
  glVertex3f(5, 1.5f, 0);
  glVertex3f(5, -1.5f, 0);
  glVertex3f(15, 0, 0);

  glEnd();

  // Глаза
  glColor3f(1, 1, 1);
  glTranslatef(2.5f, 2.5f, 2.5f);
  glutSolidSphere(2.5, 100, 20);

  glColor3f(0, 0, 0);
  glTranslatef(1.5f, 0, 1.5f);
  glutSolidSphere(1, 40, 20);
  glTranslatef(-1.5f, 0, -1.5f);
  
  glTranslatef(-2.5f, -2.5f, -2.5f);

  glColor3f(1, 1, 1);
  glTranslatef(2.5f, 2.5f, -2.5f);
  glutSolidSphere(2.5f, 100, 20);
  
  glColor3f(0, 0, 0);
  glTranslatef(1.5f, 0, -1.5f);
  glutSolidSphere(1, 40, 20);
  glTranslatef(-1.5f, 0, 1.5f);
  glTranslatef(-2.5f, -2.5f, 2.5f);
  
  glTranslatef(-birdX - dist, -birdY, -birdZ);
}

void Display() {
  glEnable(GL_LIGHTING); // Подключаем настройку света
  glEnable(GL_COLOR_MATERIAL);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(0, 40, 80, 0, 20, 0, 0, 1, 0);

  GLfloat position[] = { 0, 200, 0, 1 };
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureSky);
  glNormal3f(0, 0, 1);
  
  glBegin(GL_QUADS);

  glTexCoord2f(0, 0);
  glVertex3f(-100, 0, -100);
  glTexCoord2f(0, 1);
  glVertex3f(-100, 100, -100);
  glTexCoord2f(1, 1);
  glVertex3f(100, 100, -100);
  glTexCoord2f(1, 0);
  glVertex3f(100, 0, -100);
  
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureBottom);
  glNormal3f(0, 0, 1);
  
  glBegin(GL_QUADS);

  glTexCoord2f(0, 0);
  glVertex3f(-100, 0, -100);
  glTexCoord2f(0, 1);
  glVertex3f(-100, 0, 100);
  glTexCoord2f(1, 1);
  glVertex3f(100, 0, 100);
  glTexCoord2f(1, 0);
  glVertex3f(100, 0, -100);
  
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  createBird(-100, 50, -70);

  createBird(-120, 50, -90);
  
  createBird(-150, 50, -60);

  GLfloat height = 30;
  
  createTree(-50, 0, -20, height);

  createTree(0, 0, -40, height);

  createTree(50, 0, -20, height);

  createTree(30, 0, -50, height);

  height = 40;

  createTree(-40, 0, -50, height);
  

  if (dist < 300)
    dist += 0.3;
  else
    dist = 0;
  
  glutSwapBuffers();
  glutPostRedisplay();
}
void changeSize(int width, int height) { // Создаем функцию изменения размеров окна

  if (height == 0)
    height = 1;
  float ratio = width * 1.0 / height;
  glMatrixMode(GL_PROJECTION); // Используем матрицу проекции
  glLoadIdentity(); // Сбросить матрицу проекции
  glViewport(0, 0, width, height); // Определяем окно просмотра
  gluPerspective(45.0f, ratio, 0.1f, 10000.0f);
  glMatrixMode(GL_MODELVIEW); // Выбираем матрицу просмотра модели
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

int main(int argc, char** argv) {
  glEnable(GL_TEXTURE_2D);
  glutInit(&argc, argv); // Инициализация GLUT
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Режим отображения
  glutInitWindowPosition(200, 50); // Режим отображения
  glutInitWindowSize(900, 900); // Размер окна
  glutCreateWindow("Project"); // Создаем окно "Solar system"
  glClearColor(0, 0, 0, 0.5); // Черный фон
  glClearDepth(1.0f); // Настройка буфера глубины
  glEnable(GL_DEPTH_TEST); // Включаем проверку глубины
  glDepthFunc(GL_LEQUAL);

  textureBottom = LoadTexture("grass.png");
  textureSky = LoadTexture("sky.png");

  glutDisplayFunc(Display); // Вызов отрисовки
  glutReshapeFunc(changeSize); // Вызов функции изменения размеров окна
  glutMainLoop(); //Главный цикл
}
