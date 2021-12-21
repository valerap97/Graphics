void createTree(GLfloat treeX, GLfloat treeY, GLfloat treeZ, GLfloat height) {
  glColor3f(0.4f, 0.25f, 0);
  GLfloat angle = 0.0;
  GLfloat angle_stepsize = 0.1;
  GLfloat radius = 0.25;
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
  glTranslatef(treeX, -treeY - height, treeZ);
}

void createBird(GLfloat birdX, GLfloat birdY, GLfloat birdZ, double dist) {
  // Башка
  glColor3f(1, 0, 0);
  glTranslatef(birdX + dist, birdY, birdZ);
  glutSolidSphere(0.5, 100, 20);
  glColor3f(1, 1, 0);

  // Клюв
  glBegin(GL_TRIANGLES);
  
  glVertex3f(0.25f, 0, 0.5f);
  glVertex3f(0.25f, 0, -0.5f);
  glVertex3f(1.5f, 0, 0);

  glEnd();

  // Глаза
  glColor3f(1, 1, 1);
  glTranslatef(0.25f, 0.25f, 0.25f);
  glutSolidSphere(0.25, 100, 20);

  glColor3f(0, 0, 0);
  glTranslatef(0.2f, 0, 0.2f);
  glutSolidSphere(0.1, 40, 20);
  glTranslatef(-0.2f, 0, -0.2f);
  
  glTranslatef(-0.25f, -0.25f, -0.25f);

  glColor3f(1, 1, 1);
  glTranslatef(0.25f, 0.25f, -0.25f);
  glutSolidSphere(0.25, 100, 20);
  
  glColor3f(0, 0, 0);
  glTranslatef(0.2f, 0, -0.2f);
  glutSolidSphere(0.1, 40, 20);
  glTranslatef(-0.2f, 0, 0.2f);
  glTranslatef(-0.25f, -0.25f, 0.25f);
  
  glTranslatef(-birdX - dist, -birdY, -birdZ);
}
