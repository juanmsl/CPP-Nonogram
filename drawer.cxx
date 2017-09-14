#include "drawer.h"

float dr::WIDTH = 800;
float dr::HEIGHT = 600;
float dr::BOXSIZE = 50;
bool dr::initIsStarted = false;
bool dr::loopIsStarted = false;

void dr::init(int argc, char* argv[]) {
	if(!initIsStarted) {
		if(!loopIsStarted) {
			glutInit(&argc, argv);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
			glutInitWindowSize(WIDTH, HEIGHT);
			glutInitWindowPosition(0, 0);
			glutCreateWindow("Nonograma");

			glutReshapeFunc(resize);

			HSL(120, 60, 80, true);
			glViewport(0, 0, WIDTH, HEIGHT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0, WIDTH, 0, HEIGHT);
		}
		initIsStarted = true;
	} else {
		throw std::logic_error("The function init() must be called once");
	}
}

void dr::resize(int w, int h) {
	WIDTH = w;
	HEIGHT = h;
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void dr::setDisplayFunction(void displayFunction()) {
	if(initIsStarted) {
		if(!loopIsStarted) {
			glutDisplayFunc(displayFunction);
		} else {
			throw std::logic_error("The function setDisplayFunction() must be called before the initGlutMainLoop() function");
		}
	} else {
		throw std::logic_error("The function setDisplayFunction() must be called after the init() function");
	}
}

void dr::setKeyPressedFunction(void keyPressedFunction(unsigned char key, int x, int y)) {
	if(initIsStarted) {
		if(!loopIsStarted) {
			glutKeyboardFunc(keyPressedFunction);
		} else {
			throw std::logic_error("The function setKeyPressedFunction() must be called before the initGlutMainLoop() function");
		}
	} else {
		throw std::logic_error("The function setKeyPressedFunction() must be called after the init() function");
	}
}

void dr::initGlutMainLoop() {
	if(initIsStarted) {
		if(!loopIsStarted) {
			glutMainLoop();
			loopIsStarted = true;
		} else {
			throw std::logic_error("The function initGlutMainLoop() must be called once");
		}
	} else {
		throw std::logic_error("The function initGlutMainLoop() must be called after the init() function");
	}
}

dr::Drawer::Drawer(Nonogram& nonogram) {
	this->nonogram = &nonogram;

	dr::WIDTH = (nonogram.getColumns() + 4.0f) * dr::BOXSIZE;
	dr::HEIGHT = (nonogram.getRows() + 4.0f) * dr::BOXSIZE;
}

void dr::Drawer::drawNonogram() const {
	float tx = BOXSIZE * ( 0.5f - (nonogram->getColumns() - 2.0f) / 2.0f);
	float ty = BOXSIZE * (-0.5f + (nonogram->getRows() - 2.0f) / 2.0f);

	glPushMatrix();
		glTranslatef(tx, ty, 0.0f);
		drawNonogramRows();
		drawNonogramColumns();
		drawNonogramMatrix();
		drawResult(-1.5f, 1.5f, nonogram->isCorrect(), 2.05f);
	glPopMatrix();
}

void dr::Drawer::drawNonogramRows() const {
	for(int i = 0, y = 0; i < nonogram->getRows(); i++, y--) {
		drawResult(-2, y, nonogram->isCorrect(ROW, i));
		drawCube(-1, y, 120, 100, 30);
		drawChar(-1, y, (char)(nonogram->get(ROW, i) + 48));
	}
}

void dr::Drawer::drawNonogramColumns() const {
	for(int j = 0, x = 0; j < nonogram->getColumns(); j++, x++) {
		drawResult(x, 2, nonogram->isCorrect(COL, j));
		drawCube(x, 1, 120, 100, 30);
		drawChar(x, 1, (char)(nonogram->get(COL, j) + 48));
	}
}

void dr::Drawer::drawNonogramMatrix() const {
	for(int i = 0, y = 0; i < nonogram->getRows(); i++, y--) {
		for(int j = 0, x = 0; j < nonogram->getColumns(); j++, x++) {
			drawCube(x, y, 240, 50, 70);
			if(nonogram->isOn(i, j)) {
				drawCube(x, y, 240, 50, 50, 0.8f);
			}
		}
	}
}

void dr::Drawer::drawCube(const float& x, const float& y, const float& H, const float& S, const float& L, const float& scale) const {
	float tx = x * BOXSIZE;
	float ty = y * BOXSIZE;
	float sx = BOXSIZE * 0.95f * scale;
	float sy = BOXSIZE * 0.95f * scale;

	HSL(H, S, L);
	glPushMatrix();
		glTranslatef(tx, ty, 0.0f);
		glScalef(sx, sy, 0.0f);
		glBegin(GL_POLYGON);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(-0.5f,  0.5f);
			glVertex2f( 0.5f,  0.5f);
			glVertex2f( 0.5f, -0.5f);
		glEnd();
	glPopMatrix();
}

void dr::Drawer::drawChar(const float& x, const float& y, const char& c) const {
	float tx = x * BOXSIZE - 5.0f;
	float ty = y * BOXSIZE - 5.0f;

	glPushMatrix();
		HSL(0, 0, 0);
		glRasterPos2f(tx, ty);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	glPopMatrix();
}

void dr::Drawer::drawText(const std::string& text, const float& x, const float& y) const {
	glRasterPos2f(x, y);
	for(auto c : text) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

void dr::Drawer::drawResult(const float& x, const float& y, const bool& result, const float& scale) const {
	if(result) {
		drawCube(x, y, 88, 68, 33, scale);
		HSL(0, 100, 100);
		drawCorrectSymbol(x, y, scale);
	} else {
		drawCube(x, y, 351, 93, 56, scale);
		HSL(0, 100, 100);
		drawIncorrectSymbol(x, y, scale);
	}
}

void dr::Drawer::drawCorrectSymbol(const float& x, const float& y, const float& scale) const {
	float tx = x * BOXSIZE;
	float ty = y * BOXSIZE + 5.0f;
	float sx = BOXSIZE * scale;
	float sy = BOXSIZE * scale;

	glPushMatrix();
		glTranslatef(tx, ty, 0.0f);
		glScalef(sx, sy, 0.0f);
		glRotatef(-45, 0, 0, 1);
		glBegin(GL_QUADS);
			glVertex2f(0.10, 0.30);
			glVertex2f(0.20, 0.30);
			glVertex2f(0.20, -0.3);
			glVertex2f(0.10, -0.3);
			glVertex2f(-0.1, -0.2);
			glVertex2f(0.20, -0.2);
			glVertex2f(0.20, -0.3);
			glVertex2f(-0.1, -0.3);
		glEnd();
	glPopMatrix();
}

void dr::Drawer::drawIncorrectSymbol(const float& x, const float& y, const float& scale) const {
	float tx = x * BOXSIZE;
	float ty = y * BOXSIZE;
	float sx = BOXSIZE * scale;
	float sy = BOXSIZE * scale;

	glPushMatrix();
		glTranslatef(tx, ty, 0.0f);
		glScalef(sx, sy, 0.0f);
		glRotatef(-45, 0, 0, 1);
		glBegin(GL_QUADS);
			glVertex2f(-0.05,  0.30);
			glVertex2f( 0.05,  0.30);
			glVertex2f( 0.05, -0.30);
			glVertex2f(-0.05, -0.30);
			glVertex2f( 0.30, -0.05);
			glVertex2f( 0.30,  0.05);
			glVertex2f(-0.30,  0.05);
			glVertex2f(-0.30, -0.05);
		glEnd();
	glPopMatrix();
}

void dr::Drawer::drawCell(const float& i, const float& j) const {
	float tx = BOXSIZE * ( j + 0.5f - (nonogram->getColumns() - 2.0f) / 2.0f);
	float ty = BOXSIZE * (-i - 0.5f + (nonogram->getRows() - 2.0f) / 2.0f);
	float sx = BOXSIZE;
	float sy = BOXSIZE;

	HSL(41, 88, 55);
	glPushMatrix();
		glLineWidth(BOXSIZE * 0.1f);
		glTranslatef(tx, ty, 0.0f);
		glScalef(sx, sy, 0.0f);
		glBegin(GL_LINES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(-0.5f,  0.5f);
			glVertex2f(-0.5f,  0.5f);
			glVertex2f( 0.5f,  0.5f);
			glVertex2f( 0.5f,  0.5f);
			glVertex2f( 0.5f, -0.5f);
			glVertex2f( 0.5f, -0.5f);
			glVertex2f(-0.5f, -0.5f);
		glEnd();
	glPopMatrix();
}
