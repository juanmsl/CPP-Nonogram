#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "drawer.h"
#include "nonogram.h"

namespace cr {

  extern float px;
  extern float py;
  extern int rows;
  extern int columns;
  extern dr::Drawer* drawer;
  extern Nonogram* nonogram;

  extern void display();
  extern void keyPressed(unsigned char key, int x, int y);

  class Controller {
    public:
      Controller();
      Controller(int argc, char* argv[], Nonogram& nonogram, dr::Drawer& drawer);
  };
}

#endif
