#include "drawer.h"

float dr::WIDTH = 800;
float dr::HEIGHT = 600;
float dr::BOXSIZE = 50;
bool dr::initIsStarted = false;
bool dr::loopIsStarted = false;

void dr::init(int argc, char* argv[]) {
  if(!initIsStarted) {
    if(!loopIsStarted) {
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(WIDTH, HEIGHT);
      glutInitWindowPosition(0, 0);
      glutCreateWindow("Nonograma");

      glutReshapeFunc(resize);

      HSL(120, 60, 80, true);
      glViewport(0, 0, WIDTH, HEIGHT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, WIDTH, 0, HEIGHT);
    }
    initIsStarted = true;
  } else {
    throw std::logic_error("The function init() must be called once");
  }
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

void dr::setDisplayFunction(void displayFunction()) {
  if(initIsStarted) {
    if(!loopIsStarted) {
      glutDisplayFunc(displayFunction);
    } else {
      throw std::logic_error("The function setDisplayFunction() must be called before the initGlutMainLoop() function");
    }
  } else {
    throw std::logic_error("The function setDisplayFunction() must be called after the init() function");
  }
}

void dr::setKeyPressedFunction(void keyPressedFunction(unsigned char key, int x, int y)) {
  if(initIsStarted) {
    if(!loopIsStarted) {
      glutKeyboardFunc(keyPressedFunction);
    } else {
      throw std::logic_error("The function setKeyPressedFunction() must be called before the initGlutMainLoop() function");
    }
  } else {
    throw std::logic_error("The function setKeyPressedFunction() must be called after the init() function");
  }
}

void dr::initGlutMainLoop() {
  if(initIsStarted) {
    if(!loopIsStarted) {
      glutMainLoop();
      loopIsStarted = true;
    } else {
      throw std::logic_error("The function initGlutMainLoop() must be called once");
    }
  } else {
    throw std::logic_error("The function initGlutMainLoop() must be called after the init() function");
  }
}

dr::Drawer::Drawer(Nonogram& nonogram) {
  this->nonogram = &nonogram;

  dr::WIDTH = (nonogram.getColumns() + 3.0f) * dr::BOXSIZE;
  dr::HEIGHT = (nonogram.getRows() + 3.0f) * dr::BOXSIZE;
}

void dr::Drawer::drawNonogram() const {
  drawNonogramRows();
  drawNonogramColumns();
  drawNonogramMatrix();
  drawResult(nonogram->isCorrect());
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
  float x_i = x * BOXSIZE;
  float y_i = y * BOXSIZE;

  HSL(H, S, L);
  glPushMatrix();
    glTranslatef(x_i, y_i, 0.0f);
    glBegin(GL_POLYGON);
      glVertex2f(1.0f, 1.0f);
      glVertex2f(1.0f, BOXSIZE - 1.0f);
      glVertex2f(BOXSIZE - 1.0f, BOXSIZE - 1.0f);
      glVertex2f(BOXSIZE - 1.0f, 1.0f);
    glEnd();
  glPopMatrix();
}

void dr::Drawer::drawChar(const float& x, const float& y, const char& c) const {
  float x_i = x * BOXSIZE + BOXSIZE / 2.0f - 5.0f;
  float y_i = y * BOXSIZE + BOXSIZE / 2.0f - 5.0f;
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

void dr::Drawer::drawResult(const bool& result) const {
  if(result) {
    drawCube(0, -1, 88, 68, 33);
    HSL(0,0,0);
    glPushMatrix();
      glTranslatef(BOXSIZE * 0.5, BOXSIZE * -0.4, 0);
      glRotatef(-45, 0, 0, 1);
      glBegin(GL_QUADS);
        HSL(0, 100, 100);
        glVertex2f(BOXSIZE * 0.10, BOXSIZE * 0.30);
        glVertex2f(BOXSIZE * 0.20, BOXSIZE * 0.30);
        glVertex2f(BOXSIZE * 0.20, BOXSIZE * -0.3);
        glVertex2f(BOXSIZE * 0.10, BOXSIZE * -0.3);
        glVertex2f(BOXSIZE * -0.1, BOXSIZE * -0.2);
        glVertex2f(BOXSIZE * 0.20, BOXSIZE * -0.2);
        glVertex2f(BOXSIZE * 0.20, BOXSIZE * -0.3);
        glVertex2f(BOXSIZE * -0.1, BOXSIZE * -0.3);
      glEnd();
    glPopMatrix();
  } else {
    drawCube(0, -1, 351, 93, 56);
    HSL(0,0,0);
    glPushMatrix();
      glTranslatef(BOXSIZE * 0.5, BOXSIZE * -0.5, 0);
      glRotatef(-45, 0, 0, 1);
      glBegin(GL_QUADS);
        HSL(0, 100, 100);
        glVertex2f(BOXSIZE * -0.05, BOXSIZE *  0.30);
        glVertex2f(BOXSIZE *  0.05, BOXSIZE *  0.30);
        glVertex2f(BOXSIZE *  0.05, BOXSIZE * -0.3);
        glVertex2f(BOXSIZE * -0.05, BOXSIZE * -0.3);
        glVertex2f(BOXSIZE *  0.30, BOXSIZE * -0.05);
        glVertex2f(BOXSIZE *  0.30, BOXSIZE *  0.05);
        glVertex2f(BOXSIZE * -0.3, BOXSIZE *  0.05);
        glVertex2f(BOXSIZE * -0.3, BOXSIZE * -0.05);
      glEnd();
    glPopMatrix();
  }
}
