#include <stdio.h>
#include <string.h>
#include <cmath>
#include <glut.h>
#include <ctime>

int moveX = 500;
int moveY = 300;

int direction = GLUT_KEY_RIGHT;

int lives = 5;

int score = 0;
int scoreInc = 1;

int timer = 100;

int win = 0;

int translatePowerUp = 10;
int anglePowerUp1 = 0;
int anglePowerUp2 = 0;
int angleCollectable = 0;
double doorX = 1;
double doorY = 1;
double doorZ = 1;
int change = 0;
double scaleGoal = 2;

int powerUp1 = 0;
int powerUpTimer1 = 5;
int powerUp2 = 0;
int powerUpTimer2 = 5;

double colorR = 0;
double colorG = 1;
double colorB = 0;
double xbegin = 20;
double xend = 170;
double ybegin = 555;
double yend = 575;

double angleBird = 0;

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

// Structure to represent GameObjects
struct GameObject {
	float x;
	float y;
	float size;
};

// Array to store obstacles
GameObject obstacles[10];
GameObject collectables[10];
GameObject powerUps1[3];
GameObject powerUps2[3];

// DRAW Obstacles
void drawObstacles() {
	glColor3f(0.8, 0.1, 0.1); // Set obstacle color

	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslated(obstacles[i].x, obstacles[i].y, 0);
		glColor3f(1, 0, 0);
		drawCircle(0, 0, 17.5);
		glColor3f(0, 0, 0);
		drawCircle(-2, 3, 6);
		drawCircle(15, 3, 6);
		glPointSize(3);
		glColor3f(1, 1, 1);
		glBegin(GL_POINTS);
		glVertex3d(-1, 3, 0);
		glVertex3d(15, 3, 0);
		glEnd();
		glColor3f(1, 0.2, 0);
		glBegin(GL_LINES);
		glVertex3f(0.0f, -17.5f, 0.0f);
		glVertex3d(-5.0f, -25.0f, 0.0f);
		glVertex3f(0.0f, -17.5f, 0.0f);
		glVertex3d(5.0f, -25.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
}

// DRAW Collectables
void drawCollectables() {
	glColor3f(0.1, 0.8, 0.1); // Set collectable color

	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslated(collectables[i].x, collectables[i].y, 0);
		glRotated(angleCollectable, 0, 0, 1);
		glColor3f(0, 1, 0);
		glBegin(GL_QUADS);
		glVertex3d(-10, -10, 0);
		glVertex3d(-10, 10, 0);
		glVertex3d(10, 10, 0);
		glVertex3d(10, -10, 0);
		glVertex3d(-10, -10, 0);
		glEnd();
		glPointSize(2);
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex3d(-5, -5, 0);
		glVertex3d(-5, 5, 0);
		glVertex3d(5, -5, 0);
		glVertex3d(5, 5, 0);
		glEnd();
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex3f(-10.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -10.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
}


void drawPowerUps1() {
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslated(powerUps1[i].x, powerUps1[i].y, 0);
		glRotated(anglePowerUp1, 0, 0, 1);

		glColor3f(1.0, 0.4, 0.0); // Set yellow color for the star

		// Left line
		glBegin(GL_LINES);
		glVertex3f(-30.0f, 0.0f + translatePowerUp, 0.0f);
		glVertex3f(-8.0f, 0.0f, 0.0f);
		glEnd();

		// Right line
		glBegin(GL_LINES);
		glVertex3f(8.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 0.0f - translatePowerUp, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		// Outer points of the star (scaled up)
		glVertex3f(0.0f, 20.0f, 0.0f);
		glVertex3f(-4.0f, 4.0f, 0.0f);
		glVertex3f(-20.0f, 4.0f, 0.0f);
		glVertex3f(-8.0f, -8.0f, 0.0f);
		glVertex3f(-12.0f, -20.0f, 0.0f);
		glVertex3f(0.0f, -12.0f, 0.0f);
		glVertex3f(12.0f, -20.0f, 0.0f);
		glVertex3f(8.0f, -8.0f, 0.0f);
		glVertex3f(20.0f, 4.0f, 0.0f);
		glVertex3f(4.0f, 4.0f, 0.0f);

		glEnd();

		// Draw small white points inside the star
		glPointSize(6);
		glColor3f(1.0, 1.0, 1.0); // Set white color for points
		glBegin(GL_POINTS);
		glVertex3f(0.0f, 4.0f, 0.0f);
		glVertex3f(-4.0f, 2.0f, 0.0f);
		glVertex3f(-12.0f, -8.0f, 0.0f);
		glVertex3f(0.0f, -4.0f, 0.0f);
		glVertex3f(12.0f, -8.0f, 0.0f);
		glVertex3f(4.0f, 2.0f, 0.0f);
		glEnd();

		glPopMatrix();
	}
}

// DRAW PowerUps1 as an even bigger star with purple color using triangles (polygon)
void drawPowerUps2() {
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslated(powerUps2[i].x, powerUps2[i].y, 0);
		glRotated(anglePowerUp2, 0, 0, 1);

		glColor3f(0.5, 0.0, 0.5); // Set purple color for the star

		glBegin(GL_LINES);
		glVertex3f(-30.0f, 0.0f + translatePowerUp, 0.0f);
		glVertex3f(-8.0f, 0.0f, 0.0f);
		glEnd();

		// Right line
		glBegin(GL_LINES);
		glVertex3f(8.0f, 0.0f, 0.0f);
		glVertex3f(30.0f, 0.0f - translatePowerUp, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		// Outer points of the star (scaled up)
		glVertex3f(0.0f, 20.0f, 0.0f);
		glVertex3f(-4.0f, 4.0f, 0.0f);
		glVertex3f(-20.0f, 4.0f, 0.0f);
		glVertex3f(-8.0f, -8.0f, 0.0f);
		glVertex3f(-12.0f, -20.0f, 0.0f);
		glVertex3f(0.0f, -12.0f, 0.0f);
		glVertex3f(12.0f, -20.0f, 0.0f);
		glVertex3f(8.0f, -8.0f, 0.0f);
		glVertex3f(20.0f, 4.0f, 0.0f);
		glVertex3f(4.0f, 4.0f, 0.0f);

		glEnd();

		// Draw small white points inside the star
		glPointSize(6);
		glColor3f(1.0, 1.0, 1.0); // Set white color for points
		glBegin(GL_POINTS);
		glVertex3f(0.0f, 4.0f, 0.0f);
		glVertex3f(-4.0f, 2.0f, 0.0f);
		glVertex3f(-12.0f, -8.0f, 0.0f);
		glVertex3f(0.0f, -4.0f, 0.0f);
		glVertex3f(12.0f, -8.0f, 0.0f);
		glVertex3f(4.0f, 2.0f, 0.0f);
		glEnd();

		glPopMatrix();
	}
}

struct Point {
	int x;
	int y;
};

Point obstaclePoints[10];

// Function to check if a point is within specified ranges
bool isWithinRanges(int x, int y) {
	// Check if the point is in the restricted range
	if ((470 <= x && x <= 530 && 270 <= y && y <= 330) ||
		(0 <= x && x <= 120 && 0 <= y && y <= 150)) {
		return true;
	}
	return false;
}

// Initialize Random Obstacles
void initObstacles() {
	for (int i = 0; i < 10; i++) {
		do {
			obstacles[i].x = rand() % 930 + 30;
			obstacles[i].y = rand() % 480 + 30;
			obstacles[i].size = 20;
		} while (isWithinRanges(obstacles[i].x, obstacles[i].y));
		obstaclePoints[i].x = obstacles[i].x;
		obstaclePoints[i].y = obstacles[i].y;
	}
}

// Initialize Random Collectables
void initCollectables() {
	for (int i = 0; i < 10; i++) {
		do {
			collectables[i].x = rand() % 930 + 30;  // Random x position
			collectables[i].y = rand() % 480 + 30;  // Random y position
			collectables[i].size = 20;
		} while (isWithinRanges(collectables[i].x, collectables[i].y));
	}
}

// Initialize Random PowerUps1
void initPowerUps1() {
	for (int i = 0; i < 3; i++) {
		do {
			powerUps1[i].x = rand() % 930 + 30;  // Random x position
			powerUps1[i].y = rand() % 480 + 30;  // Random y position
			powerUps1[i].size = 20;
		} while (isWithinRanges(powerUps1[i].x, powerUps1[i].y));
	}
}


void initPowerUps2() {
	for (int i = 0; i < 3; i++) {
		do {
			powerUps2[i].x = rand() % 930 + 30;  // Random x position
			powerUps2[i].y = rand() % 480 + 30;  // Random y position
			powerUps2[i].size = 20;
		} while (isWithinRanges(powerUps2[i].x, powerUps2[i].y));
	}
}

//DRAW Goal
void drawGoal() {
	glPushMatrix();
	glTranslated(40, 40, 0);
	glScalef(scaleGoal, scaleGoal, 1.0);

	// Draw the base of the home using GL_QUADS
	glColor3f(0.8f, 0.2f, 0.2f);  // Set the color to a reddish tone
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, -10.0f, 0.0f);
	glVertex3f(10.0f, -10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(-10.0f, 10.0f, 0.0f);
	glEnd();

	// Draw the roof of the home using GL_TRIANGLES
	glColor3f(0.3f, 0.6f, 0.2f);  // Set the color to a greenish tone
	glBegin(GL_TRIANGLES);
	glVertex3f(-10.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, 25.0f, 0.0f);
	glEnd();

	// Draw the door using GL_QUADS
	glColor3f(doorX, doorY, doorZ);  // Set the color to a brownish tone
	glBegin(GL_QUADS);
	glVertex3f(-4.0f, -10.0f, 0.0f);
	glVertex3f(4.0f, -10.0f, 0.0f);
	glVertex3f(4.0f, 5.0f, 0.0f);
	glVertex3f(-4.0f, 5.0f, 0.0f);
	glEnd();

	// Draw the window using GL_QUADS
	glColor3f(0.0f, 0.5f, 0.8f);  // Set the color to a bluish tone
	glBegin(GL_QUADS);
	glVertex3f(-3.5f, 7.0f, 0.0f);
	glVertex3f(3.5f, 7.0f, 0.0f);
	glVertex3f(3.5f, 11.0f, 0.0f);
	glVertex3f(-3.5f, 11.0f, 0.0f);
	glEnd();

	// Draw the chimney using GL_POLYGON
	glColor3f(0.5f, 0.5f, 0.5f);  // Set the color to gray
	glBegin(GL_POLYGON);
	glVertex3f(3.0f, 12.0f, 0.0f);
	glVertex3f(5.0f, 12.0f, 0.0f);
	glVertex3f(5.0f, 15.0f, 0.0f);
	glVertex3f(3.0f, 15.0f, 0.0f);
	glEnd();

	// Draw a point at the tip of the roof
	glColor3f(1.0f, 1.0f, 1.0f);  // Set the color to white
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 25.0f, 0.0f);
	glEnd();

	// Draw a line for the chimney
	glColor3f(0.5f, 0.5f, 0.5f);  // Set the color to gray
	glBegin(GL_LINES);
	glVertex3f(4.0f, 15.0f, 0.0f);
	glVertex3f(4.0f, 20.0f, 0.0f);
	glEnd();

	// Draw a line strip around the window
	glColor3f(0.0f, 0.0f, 0.0f);  // Set the color to black
	glBegin(GL_LINE_STRIP);
	glVertex3f(-3.5f, 7.0f, 0.0f);
	glVertex3f(3.5f, 7.0f, 0.0f);
	glVertex3f(3.5f, 11.0f, 0.0f);
	glVertex3f(-3.5f, 11.0f, 0.0f);
	glVertex3f(-3.5f, 7.0f, 0.0f);
	glEnd();

	glPopMatrix();
}


void drawBoundaries() {

	glPushMatrix();
	// Set the color for the boundaries
	glColor3f(0.0, 0.0, 0.0);

	// Define the boundary offsets
	float leftBoundary = 10.0;
	float rightBoundary = 1000.0 - 10.0;
	float topBoundary = 540 - 10.0;
	float bottomBoundary = 10.0;

	// Draw the left boundary
	glBegin(GL_LINES);
	glVertex2f(leftBoundary, topBoundary);
	glVertex2f(leftBoundary, bottomBoundary);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(leftBoundary + 2.0, topBoundary);
	glVertex2f(leftBoundary + 2.0, bottomBoundary);
	glEnd();

	for (float i = bottomBoundary; i < topBoundary; i += 10.0) {
		glBegin(GL_POINTS);
		glVertex2f(leftBoundary + 1.0, i);
		glEnd();
	}

	// Draw the right boundary
	glBegin(GL_LINES);
	glVertex2f(rightBoundary, topBoundary);
	glVertex2f(rightBoundary, bottomBoundary);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(rightBoundary - 2.0, topBoundary);
	glVertex2f(rightBoundary - 2.0, bottomBoundary);
	glEnd();

	for (float i = bottomBoundary; i < topBoundary; i += 10.0) {
		glBegin(GL_POINTS);
		glVertex2f(rightBoundary - 1.0, i);
		glEnd();
	}

	// Draw the top boundary
	glBegin(GL_LINES);
	glVertex2f(leftBoundary, topBoundary);
	glVertex2f(rightBoundary, topBoundary);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(leftBoundary, topBoundary - 2.0);
	glVertex2f(rightBoundary, topBoundary - 2.0);
	glEnd();

	for (float i = leftBoundary; i < rightBoundary; i += 10.0) {
		glBegin(GL_POINTS);
		glVertex2f(i, topBoundary - 1.0);
		glEnd();
	}

	// Draw the bottom boundary
	glBegin(GL_LINES);
	glVertex2f(leftBoundary, bottomBoundary);
	glVertex2f(rightBoundary, bottomBoundary);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(leftBoundary, bottomBoundary + 2.0);
	glVertex2f(rightBoundary, bottomBoundary + 2.0);
	glEnd();

	for (float i = leftBoundary; i < rightBoundary; i += 10.0) {
		glBegin(GL_POINTS);
		glVertex2f(i, bottomBoundary + 1.0);
		glEnd();
	}
	glPopMatrix();
}

void drawBird1() {
	glPushMatrix();
	glTranslated(150, 450, 0);
	glRotated(angleBird, 0, 0, 1);

	// Set the bird's body color
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	// Draw the bird's body (a single point)
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f); // Draw the bird at the origin
	glEnd();

	// Set the wing color
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	// Draw the left wing (a curve using lines)
	glBegin(GL_LINE_STRIP);
	for (int i = -30; i <= 0; i++) {
		float x = i;
		float y = 10.0f * sinf(i * 0.1f); // Adjust the wing size and curvature
		glVertex2f(x, y);
	}
	glEnd();

	// Draw the right wing (a curve using lines)
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++) {
		float x = i;
		float y = 10.0f * sinf(i * 0.1f); // Adjust the wing size and curvature
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void drawBird2() {
	glPushMatrix();
	glTranslated(500, 450, 0);
	glRotated(angleBird, 0, 0, 1);

	// Set the bird's body color
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	// Draw the bird's body (a single point)
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f); // Draw the bird at the origin
	glEnd();

	// Set the wing color
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	// Draw the left wing (a curve using lines)
	glBegin(GL_LINE_STRIP);
	for (int i = -30; i <= 0; i++) {
		float x = i;
		float y = 10.0f * sinf(i * 0.1f); // Adjust the wing size and curvature
		glVertex2f(x, y);
	}
	glEnd();

	// Draw the right wing (a curve using lines)
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++) {
		float x = i;
		float y = 10.0f * sinf(i * 0.1f); // Adjust the wing size and curvature
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}

void drawBird3() {
	glPushMatrix();
	glTranslated(850, 450, 0);
	glRotated(angleBird, 0, 0, 1);

	// Set the bird's body color
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	// Draw the bird's body (a single point)
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f); // Draw the bird at the origin
	glEnd();

	// Set the wing color
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	// Draw the left wing (a curve using lines)
	glBegin(GL_LINE_STRIP);
	for (int i = -30; i <= 0; i++) {
		float x = i;
		float y = 10.0f * sinf(i * 0.1f); // Adjust the wing size and curvature
		glVertex2f(x, y);
	}
	glEnd();

	// Draw the right wing (a curve using lines)
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++) {
		float x = i;
		float y = 10.0f * sinf(i * 0.1f); // Adjust the wing size and curvature
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
}


void GameInfo() {
	if (lives >= 4) {
		colorR = 0;
		colorG = 1;
		colorB = 0;
	}
	else if (lives >= 2) {
		colorR = 1;
		colorG = 0.6;
		colorB = 0;
	}
	else {
		colorR = 1;
		colorG = 0;
		colorB = 0;
	}
	if (lives == 5)
		xend = 170;
	else if (lives == 4)
		xend = 140;
	else if (lives == 3)
		xend = 110;
	else if (lives == 2)
		xend = 80;
	else if (lives == 1)
		xend = 50;
	else
		xend = 20;
	glColor3f(colorR, colorG, colorB);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(xbegin, ybegin, 0);
	glVertex3f(xend, ybegin, 0);
	glVertex3f(xend, yend, 0);
	glVertex3f(xbegin, yend, 0);
	glVertex3f(xbegin, ybegin, 0);
	glEnd();
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	char* scorearr[20];
	sprintf((char*)scorearr, "Score: %d", score);
	print(190, 560, (char*)scorearr);
	glPopMatrix();

	glPushMatrix();
	char* powerUp1Timearr[20];
	sprintf((char*)powerUp1Timearr, "Power1(Double Score): %d", powerUpTimer1);
	print(330, 560, (char*)powerUp1Timearr);
	glPopMatrix();

	glPushMatrix();
	char* powerUp2Timearr[20];
	sprintf((char*)powerUp2Timearr, "Power2(Hide Obstacles): %d", powerUpTimer2);
	print(595, 560, (char*)powerUp2Timearr);
	glPopMatrix();

	glPushMatrix();
	char* timearr[20];
	sprintf((char*)timearr, "Time: %d", timer);
	print(860, 560, (char*)timearr);
	glPopMatrix();
}


// Display function
void Display() {

	glClearColor(1, 1, 1, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	drawBoundaries();

	if (win == 1) {
		GameInfo();
		glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "You Won");
		print(430, 290, (char*)p0s);
	}
	else if (lives != 0 && timer != 0) {
		GameInfo();
		drawPlayer();
		drawObstacles();
		drawGoal();
		drawCollectables();
		drawPowerUps1();
		drawPowerUps2();
		drawBird1();
		drawBird2();
		drawBird3();
	}
	else {
		GameInfo();
		glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "You Lost");
		print(430, 290, (char*)p0s);
	}

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
