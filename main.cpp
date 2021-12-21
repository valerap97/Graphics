#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>

double angle = 0;

void Display() {
  glEnable(GL_LIGHTING); // Подключаем настройку света
  glEnable(GL_COLOR_MATERIAL); // Цветной материал - планеты
  //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Подключаем свет с двух сторон
  //glEnable(GL_NORMALIZE); // ...нормализуем векторы для правильного окрашивания
  //glEnable(GL_DEPTH_TEST); // Убираем невидимые поверхности

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  GLfloat position[] = { 0, 0, 0, 1 }; // Точечный свет (из центра) - "искуственное солнце"
  glEnable(GL_LIGHT0); // Обращаение к первому источнику
  glLightfv(GL_LIGHT0, GL_POSITION, position); // Установка позиции

  gluLookAt(0, 0, 40 , 0, 0, 0, 1, 1, 1);

  glutSwapBuffers();
  glutPostRedisplay();
}
void changeSize(int width, int height) { // Создаем функцию изменения размеров окна
  glMatrixMode(GL_PROJECTION); // Используем матрицу проекции
  glLoadIdentity(); // Сбросить матрицу проекции
  glViewport(0, 0, width, height); // Определяем окно просмотра
  glOrtho(-100, 100, -100, 100, -100, 100); // Установить корректную перспективу
  glMatrixMode(GL_MODELVIEW); // Выбираем матрицу просмотра модели
}

int main(int argc, char** argv) {
  glutInit(&argc, argv); // Инициализация GLUT
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Режим отображения
  glutInitWindowPosition(200, 50); // Режим отображения
  glutInitWindowSize(900, 900); // Размер окна
  glutCreateWindow("Project"); // Создаем окно "Solar system"
  glClearColor(0, 0, 0, 0.5); // Черный фон
  glClearDepth(1.0f); // Настройка буфера глубины
  glEnable(GL_DEPTH_TEST); // Включаем проверку глубины
  glDepthFunc(GL_LEQUAL);

  glutDisplayFunc(Display); // Вызов отрисовки
  glutReshapeFunc(changeSize); // Вызов функции изменения размеров окна
  glutMainLoop(); //Главный цикл
}
