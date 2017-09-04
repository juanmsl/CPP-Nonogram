#include "drawer.h"

float dr::WIDTH = 1200;
float dr::HEIGHT = 600;

float dr::px = 0;
float dr::py = 0;

void dr::init(int argc, char* argv[], void displayFunction()) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Nonograma");
  glutDisplayFunc(displayFunction);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyPressed);

  HSL(120, 60, 80, true);
  glViewport(0, 0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  glutMainLoop();
}

void dr::resize(int w, int h) {
  WIDTH = w;
  HEIGHT = h;
  glViewport(0, 0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}

void dr::keyPressed(unsigned char key, int x, int y) {
  switch(key) {
    case 'a': case 'A':
      px += 10.0f;
    break;
    case 'd': case 'D':
      px -= 10.0f;
    break;
    case 'w': case 'W':
      py += 10.0f;
    break;
    case 's': case 'S':
      py -= 10.0f;
    break;
    default:
    return;
  }
  glutPostRedisplay();
}

dr::Drawer::Drawer() {
  this->boxSize = 50.0f;
}

dr::Drawer::Drawer(Nonogram& nonogram) {
  this->nonogram = &nonogram;
  this->boxSize = 50.0f;
}

dr::Drawer::Drawer(Nonogram& nonogram, const float& boxSize) {
  this->nonogram = &nonogram;
  this->boxSize = boxSize;
}

void dr::Drawer::setNonogram(Nonogram& nonogram) {
  this->nonogram = &nonogram;
}

void dr::Drawer::drawNonogram() const {
  float rows = nonogram->getRows();
  float columns = nonogram->getColumns();
  float x = px + boxSize * ((rows + 1.0f) / 2.0f);
  float y = py + boxSize * ((columns + 1.0f) / 2.0f);
  glPushMatrix();
    glTranslatef(-x, y, 0.0f);
    drawNonogramRows();
    drawNonogramColumns();
    drawNonogramMatrix();
  glPopMatrix();
}

void dr::Drawer::drawNonogramRows() const {
  int rows = nonogram->getRows();
  int columns = nonogram->getColumns();
  int total_rows = rows + 1.0f;
  int total_columns = columns + 1.0f;

  for(int i = 0; i < rows; i++) {
    int row = nonogram->get(ROW, i);
    float x = -1 + total_columns - columns;
    float y = -i - 1 - total_rows + rows;
    drawCube(x, y, 120, 100, 30);
    HSL(0, 0, 0);
    drawChar(x, y, (char)(row + 48));
  }
}

void dr::Drawer::drawNonogramColumns() const {
  int rows = nonogram->getRows();
  int columns = nonogram->getColumns();
  int total_rows = rows + 1.0f;
  int total_columns = columns + 1.0f;

  for(int j = 0; j < columns; j++) {
    int column = nonogram->get(COL, j);
    float x = j + total_columns - columns;
    float y = -total_rows + rows;
    drawCube(x, y, 120, 100, 30);
    HSL(0, 0, 0);
    drawChar(x, y, (char)(column + 48));
  }
}

void dr::Drawer::drawNonogramMatrix() const {
  int rows = nonogram->getRows();
  int columns = nonogram->getColumns();
  int total_rows = rows + 1.0f;
  int total_columns = columns + 1.0f;

  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      float x = j + total_columns - columns;
      float y = -i - 1 - total_rows + rows;
      drawCube(x, y, 240, 50, ((nonogram->isOn(i, j)) ? 0 : 70));
    }
  }
}

void dr::Drawer::drawCube(const float& x, const float& y, const float& H, const float& S, const float& L) const {
  float x_i = x * boxSize;
  float y_i = y * boxSize;

  HSL(H, S, L);
  glPushMatrix();
    glTranslatef(x_i, y_i, 0.0f);
    glBegin(GL_POLYGON);
      glVertex2f(1.0f, 1.0f);
      glVertex2f(1.0f, boxSize - 1.0f);
      glVertex2f(boxSize - 1.0f, boxSize - 1.0f);
      glVertex2f(boxSize - 1.0f, 1.0f);
    glEnd();
  glPopMatrix();
}

void dr::Drawer::drawChar(const float& x, const float& y, const char& c) const {
  float x_i = x * boxSize + boxSize / 2.0f - 5.0f;
  float y_i = y * boxSize + boxSize / 2.0f - 5.0f;
  glPushMatrix();
    glRasterPos2f(x_i, y_i);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  glPopMatrix();
}

void dr::Drawer::drawText(const std::string& text, const float& x, const float& y) const {
  glRasterPos2f(x, y);
  for(auto c : text) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}
