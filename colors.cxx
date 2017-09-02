#include "colors.h"

float mod(float a, float b) {
	int res = a/b;
	float md = (float)res * b;
	float m = a - md;
	return m;
}

void RGB(float R, float G, float B, bool fondo) {
	if(fondo) glClearColor(R/255.0, G/255.0, B/255.0, 1.0);
	else glColor4f(R/255.0, G/255.0, B/255.0, 1.0);
}

void RGBA(float R, float G, float B, float alpha) {
	glColor4f(R/255.0, G/255.0, B/255.0, alpha);
}

/*
	Algorithm implemented from the formula in
	http://www.rapidtables.com/convert/color/hsl-to-rgb.htm

	H: Hue [0 - 360]
	S: Saturation [0 - 100]
	L: Lightness [0 - 100]

	Colour wheel for HSL: https://bitsofco.de/img/blog/26/hsl.png
*/
void HSL(float H, float S, float L, bool fondo) {
	H /= 60;
	S /= 100;
	L /= 100;

	float C = (1 - fabs(2 * L - 1)) * S;
	float X = C * (float)(1 - fabs(mod(H, 2) - 1));
	float m = L - C/2;

	float R, G, B;

	int quadrant = H;

	switch(quadrant) {
		case 0: R=C; G=X; B=0; break;
		case 1: R=X; G=C; B=0; break;
		case 2: R=0; G=C; B=X; break;
		case 3: R=0; G=X; B=C; break;
		case 4: R=X; G=0; B=C; break;
		case 5: R=C; G=0; B=X; break;
	}

	R = (R + m) * 255;
	G = (G + m) * 255;
	B = (B + m) * 255;

	RGB(R, G, B, fondo);
}

void HSLA(float H, float S, float L, float alpha) {
	H /= 60;
	S /= 100;
	L /= 100;

	float C = (1 - fabs(2 * L - 1)) * S;
	float X = C * (float)(1 - fabs(mod(H, 2) - 1));
	float m = L - C/2;

	float R, G, B;

	int quadrant = H;

	switch(quadrant) {
		case 0: R=C; G=X; B=0; break;
		case 1: R=X; G=C; B=0; break;
		case 2: R=0; G=C; B=X; break;
		case 3: R=0; G=X; B=C; break;
		case 4: R=X; G=0; B=C; break;
		case 5: R=C; G=0; B=X; break;
	}

	R = (R + m) * 255;
	G = (G + m) * 255;
	B = (B + m) * 255;

	RGBA(R, G, B, alpha);
}