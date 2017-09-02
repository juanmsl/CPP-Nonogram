#include "controller.h"

Controller::Controller() {
  this->nonogram = NULL;
}

Controller::Controller(Nonogram& nonogram) {
  this->nonogram = &nonogram;
}
