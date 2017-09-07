#ifndef __DRAWER_H__
#define __DRAWER_H__

#define ANSI_COLOR_BLACK   "\033[1;30m"
#define ANSI_COLOR_RED     "\033[1;31m"
#define ANSI_COLOR_GREEN   "\033[1;32m"
#define ANSI_COLOR_YELLOW  "\033[1;33m"
#define ANSI_COLOR_BLUE    "\033[1;34m"
#define ANSI_COLOR_MAGENTA "\033[1;35m"
#define ANSI_COLOR_CYAN    "\033[1;36m"
#define ANSI_COLOR_WHITE   "\033[1;37m"
#define ANSI_COLOR_RESET   "\033[0m"

#define PI 3.14159265f
#define RAD PI / 180.0f
#define FPS 60.0f

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <vector>
#include <stdexcept>
#include "nonogram.h"
#include "colors.h"

namespace dr {

  extern float WIDTH;
  extern float HEIGHT;
  extern float BOXSIZE;
  extern bool initIsStarted;
  extern bool loopIsStarted;

  extern void init(int argc, char* argv[]);
  extern void resize(int w, int h);
  extern void setDisplayFunction(void displayFunction());
  extern void setKeyPressedFunction(void keyPressedFunction(unsigned char key, int x, int y));
  extern void initGlutMainLoop();

  class Drawer {
    protected:
      Nonogram* nonogram;

    public:
      Drawer(Nonogram& nonogram);
      void setNonogram(Nonogram& nonogram);
      void drawNonogram() const;
      void drawNonogramRows() const;
      void drawNonogramColumns() const;
      void drawNonogramMatrix() const;
      void drawCube(const float& x, const float& y, const float& H, const float& S, const float& L) const;
      void drawChar(const float& x, const float& y, const char& c) const;
      void drawText(const std::string& text, const float& x, const float& y) const;
  };
}


#endif
