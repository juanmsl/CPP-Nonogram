#ifndef __COLORS_H__
#define __COLORS_H__

#define WHITE HSL(0, 100, 100)
#define BLACK HSL(0, 0, 0)

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

float mod(float a, float b);

void RGB(float R, float G, float B, bool fondo = false);

void RGBA(float R, float G, float B, float alpha);

void HSL(float H, float S, float L, bool fondo = false);

void HSLA(float H, float S, float L, float alpha);

#endif
