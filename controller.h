#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "nonogram.h"

class Controller {
  protected:
    Nonogram* nonogram;

  public:
    Controller();
    Controller(Nonogram& nonogram);
};

#endif
