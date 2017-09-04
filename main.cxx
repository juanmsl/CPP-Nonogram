#include <iostream>
#include "nonogram.h"
#include "controller.h"
#include "drawer.h"

#define ANSI_COLOR_BLACK   "\033[1;30m"
#define ANSI_COLOR_RED     "\033[1;31m"
#define ANSI_COLOR_GREEN   "\033[1;32m"
#define ANSI_COLOR_YELLOW  "\033[1;33m"
#define ANSI_COLOR_BLUE    "\033[1;34m"
#define ANSI_COLOR_MAGENTA "\033[1;35m"
#define ANSI_COLOR_CYAN    "\033[1;36m"
#define ANSI_COLOR_WHITE   "\033[1;37m"
#define ANSI_COLOR_RESET   "\033[0m"

Nonogram nonogram;
dr::Drawer drawer(nonogram, 50);
Controller controller(nonogram);

void display();

int main(int argc, char* argv[]) {

	if(argc != 2) {
		std::cerr << ANSI_COLOR_RED << "Error: " << ANSI_COLOR_RESET << "Missing arguments\n";
    std::cerr << "Usage: " << argv[0]  << ANSI_COLOR_BLUE << " file\n"  << ANSI_COLOR_RESET;
		return -1;
	}

  nonogram.setMap(argv[1]);
	dr::init(argc, argv, display);

	return 0;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	drawer.drawNonogram();

	HSL(0, 100, 50);
	glPushMatrix();
		glTranslatef(0,0,0);
		glBegin(GL_POLYGON);
			glVertex2f(-1, -1); glVertex2f(-1,  1);
			glVertex2f( 1,  1); glVertex2f( 1, -1);
		glEnd();
	glPopMatrix();

  glutSwapBuffers();
}
