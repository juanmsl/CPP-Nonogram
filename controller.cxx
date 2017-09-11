#include "controller.h"

float cr::px = 0;
float cr::py = 0;
dr::Drawer* cr::drawer;
Nonogram* cr::nonogram;

void cr::display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float x = px + dr::BOXSIZE * ((nonogram->getRows() + 1.0f) / 2.0f);
  float y = py + dr::BOXSIZE * ((nonogram->getColumns() + 1.0f) / 2.0f);
  glPushMatrix();
    glTranslatef(-x, y, 0.0f);
    cr::drawer->drawNonogram();
  glPopMatrix();

  glutSwapBuffers();
}

void cr::keyPressed(unsigned char key, int x, int y) {
  switch(key) {
    case 'a': case 'A':
      if(px < dr::BOXSIZE)
        px += 10.0f;
    break;
    case 'd': case 'D':
      if(px > -dr::BOXSIZE)
        px -= 10.0f;
    break;
    case 'w': case 'W':
      if(py < dr::BOXSIZE)
        py += 10.0f;
    break;
    case 's': case 'S':
      if(py > -dr::BOXSIZE)
        py -= 10.0f;
    break;
    default:
    return;
  }
  glutPostRedisplay();
}

cr::Controller::Controller(int argc, char* argv[], Nonogram& nonogram, dr::Drawer& drawer) {
  cr::nonogram = &nonogram;
  cr::drawer = &drawer;

	dr::init(argc, argv);
	dr::setDisplayFunction(cr::display);
	dr::setKeyPressedFunction(cr::keyPressed);
	dr::initGlutMainLoop();
}
