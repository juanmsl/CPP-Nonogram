#ifndef __DRAWER_H__
#define __DRAWER_H__

#define PI 3.14159265f
#define RAD PI / 180.0f
#define FPS 60.0f

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <vector>
#include "nonogram.h"
#include "colors.h"

namespace dr {

  extern float WIDTH;
  extern float HEIGHT;

  extern float px;
  extern float py;
  extern float pz;

  extern void resize(int w, int h);
  extern void keyPressed(unsigned char key, int x, int y);
  extern void init(int argc, char* argv[], void displayFunction());

  class Drawer {
    protected:
      Nonogram* nonogram;
      float boxSize;

    public:
      Drawer();
      Drawer(Nonogram& nonogram);
      Drawer(Nonogram& nonogram, const float& boxSize);
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
