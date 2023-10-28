#include <stdio.h>
#include <string.h>
#include <cmath>
#include <glut.h>
#include <ctime>

int moveX = 500;
int moveY = 300;

int direction = GLUT_KEY_RIGHT;

//this is the method used to print text in OpenGL
//there are three parameters,
//the first two are the coordinates where the text is display,
//the third coordinate is the string containing the text to display
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//DRAW Circle
void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

// DRAW Player
void drawPlayer() {
	glPointSize(5);
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(moveX, moveY, 0);
	glScaled(1.3, 1.3, 0);
	glRotated(0, 0, 0, 1);

	if (direction == GLUT_KEY_RIGHT)
		glRotated(0, 0, 0, 1);
	if (direction == GLUT_KEY_UP)
		glRotated(90, 0, 0, 1);
	if (direction == GLUT_KEY_LEFT)
		glRotated(180, 0, 0, 1);
	if (direction == GLUT_KEY_DOWN)
		glRotated(270, 0, 0, 1);

	glColor3f(0.2, 0.2, 0.7);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, -10.0f, 0.0f);
	glVertex3f(10.0f, -10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(-10.0f, 10.0f, 0.0f);
	glVertex3f(-10.0f, -10.0f, 0.0f);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-10.0f, -10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, -10.0f, 0.0f);
	glVertex3f(-10.0f, 10.0f, 0.0f);
	glEnd();
	glColor3f(0.1, 0.1, 0.8);
	glBegin(GL_TRIANGLES);
	glVertex3f(10.0f, -10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(30.0f, 0.0f, 0.0f);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex3d(20, 0, 0);
	glEnd();

	glPopMatrix();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	char* p0s[20];
	sprintf((char*)p0s, "Score: %d", 50);
	print(500, 300, (char*)p0s);
	
	
	glFlush();
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);
	
	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1000, 0.0, 600);

	glutMainLoop();
}
