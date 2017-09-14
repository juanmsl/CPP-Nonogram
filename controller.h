#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "drawer.h"
#include "nonogram.h"

namespace cr {

	extern int i;
	extern int j;
	extern bool isPlaying;
	extern dr::Drawer* drawer;
	extern Nonogram* nonogram;

	extern void display();
	extern void keyPressed(unsigned char key, int x, int y);
	extern void specialKeys(int key, int x, int y);

	class Controller {
		public:
			Controller(int argc, char* argv[], Nonogram& nonogram, dr::Drawer& drawer);
			void solveNonogram();
	};
}

#endif
