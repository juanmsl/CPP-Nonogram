#include "controller.h"

int cr::i = 0;
int cr::j = 0;
bool cr::isPlaying = false;
dr::Drawer* cr::drawer;
Nonogram* cr::nonogram;

void cr::display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		cr::drawer->drawNonogram();
		if(cr::isPlaying) {
			cr::drawer->drawCell(i, j);
		}
	glPopMatrix();

	glutSwapBuffers();
}

void cr::keyPressed(unsigned char key, int x, int y) {
	switch(key) {
	case 'a': case 'A':
		if(isPlaying && j > 0) j--;
	break;
	case 'd': case 'D':
		if(isPlaying && j < nonogram->getColumns() - 1) j++;
	break;
	case 'w': case 'W':
		if(isPlaying && i > 0) i--;
	break;
	case 's': case 'S':
		if(isPlaying && i < nonogram->getRows() - 1) i++;
	break;
	case 'r': case 'R':
		isPlaying = !isPlaying;
	break;
	case ' ':
		if(isPlaying) {
			(*nonogram)[i][j] = !(*nonogram)[i][j];
		}
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
