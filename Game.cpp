#include "Game.h"

float rotate_x, rotate_y, rotate_z,trans_x,trans_y,trans_z=0;
int windows;
//menu
static int menu;


Game::Game(QWidget* parent) :QOpenGLWidget(parent)
{
	fakeglut();
	connect(&time, SIGNAL(timeout()), this, SLOT(update()));
	time.start(16);
	setMouseTracking(true);
}
void Game::GlSetting(void)
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_SPECULAR);
	glEnable(GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DIFFUSE);
	glEnable(GL_SHININESS);
	glEnable(GL_COLOR);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
}
void Game::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, (float)w / h, 0.01, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}
void Game::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	//GLUquadric* quad;
	//quad = gluNewQuadric();
	glTranslatef(0, 0, -30);
	//gluSphere(quad, 10, 100, 20);
}
void Game::fakeglut()
{
	int argc = 1;
	char* argv[1] = { (char*)"Something" };
	glutInit(&argc, argv);
}
void Game::initializeGL()
{
	GlSetting();
}

void Game::drawteapot(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSolidTeapot(10);
	
}
