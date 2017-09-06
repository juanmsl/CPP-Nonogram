#include <iostream>
#include "nonogram.h"
#include "controller.h"
#include "drawer.h"

#define boxSize 50

float px, py;
int rows, columns;

Nonogram nonogram;
dr::Drawer drawer(nonogram, boxSize);
Controller controller(nonogram);

void display();
void keyPressed(unsigned char key, int x, int y);

int main(int argc, char* argv[]) {

	if(argc != 2) {
		std::cerr << ANSI_COLOR_RED << "Error: " << ANSI_COLOR_RESET << "Missing arguments\n";
    std::cerr << "Usage: " << argv[0]  << ANSI_COLOR_BLUE << " file\n"  << ANSI_COLOR_RESET;
		return -1;
	}

  nonogram.setMap(argv[1]);

	rows = nonogram.getRows();
  columns = nonogram.getColumns();

  int width = (columns + 3.0f) * boxSize;
  int height = (rows + 3.0f) * boxSize;

	dr::init(argc, argv, width, height);
	dr::setDisplayFunction(display);
	dr::setKeyPressedFunction(keyPressed);
	dr::initGlutMainLoop();

	return 0;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float x = px + boxSize * ((rows + 1.0f) / 2.0f);
  float y = py + boxSize * ((columns + 1.0f) / 2.0f);
  glPushMatrix();
    glTranslatef(-x, y, 0.0f);
    drawer.drawNonogram();
  glPopMatrix();

  glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
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
