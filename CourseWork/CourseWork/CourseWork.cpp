// CourseWork.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "freeglut.h"
#include <Windows.h>
#include <iostream>

using namespace std;

//grid status
#define ON 1
#define OFF 2
BOOLEAN gridOn = true;

//mouse click coordinates
float mousex ;
float mousey ;

//arrays to store colors
double horElement1[3] = { 0.0,0.8,0.5 };
double horElement2[3] = { 0.0,0.8,0.5 };
double horElement3[3] = { 0.0,0.8,0.5 };
double verElement1 [3] = { 0.0,0.8,0.5 };
double verElement2[3] = { 0.0,0.8,0.5 };
double verElement3[3] = { 0.0,0.8,0.5 };
double verElement4[3] = { 0.0,0.8,0.5 };

//arrays to store drawn objects
float points[1000][2];
float lines[1000][4];
float rectangles[1000][2];
float triangles[1000][2];
float polyTriangles[1000][2];
float polyRectangles[1000][2];
float polyCircle[1000][2];

//variables as counters
int polyTri=0;
int polyRect = 0;
int polyCir = 0;
int tri=0;
int rect=0;
int li = 0;
int click = 0;
int changeDot = 0;

//variables to store coordinates for line
float x1, x2, cy1, y2;
float xi, yi, xf, yf;


//vairables to determine selection
int SelectedL = 0;
int SelectedD = 0;
int SelectedR = 0;
int SelectedT = 0;
int SelectedPT = 0;
int SelectedPR = 0;
int SelectedCR = 0;

//variables used for transforming
float pX, pY, pZ;
float lX, lY, lZ;
float rX, rY, rZ;
float tX, tY, tZ;
float ptX, ptY, ptZ;
float prX, prY, prZ;
float pcX, pcY, pcZ;



//code to draw the grid
void drawGrid() {
	
	//used to turn the grid on and off
	if (gridOn == true) {
		glBegin(GL_LINES);
		glColor3f(0.1, 0.1, 0.1);

		for (float x = 80.0; x < 800; x = x + 40) {
			glLineWidth(1);
			glLineStipple(3, 0xAAAA); //create the dashed polylines
			glEnable(GL_LINE_STIPPLE); //enable stipple to dispaly
			glBegin(GL_LINES);
			glVertex2f(x, 60);
			glVertex2f(x, 600);
			glEnd();
			glDisable(GL_LINE_STIPPLE);
		}

		for (float y = 60; y < 600; y = y + 30) {
			glLineWidth(1);
			glLineStipple(3, 0xAAAA);  //create the dashed polylines
			glEnable(GL_LINE_STIPPLE); //enable stipple to dispaly
			glBegin(GL_LINES);
			glVertex2f(80, y);
			glVertex2f(800, y);
			glEnd();
			glDisable(GL_LINE_STIPPLE);
		}
		glLineWidth(2);
	
	}
}

//code to say what to do on selected PopUp menu item
void menuEvents(int option) {

	//checking which option is selected from the popup menu
	switch (option) {
	case ON:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gridOn = true; //assinging boolean value to true, making grid visible
		glutPostRedisplay();
		break;


	case OFF:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gridOn = false; //assigning boolean value to false, making grid not visible
		glutPostRedisplay();
		break;
	}
}

//code to create the pop up menu.
void createGLUTMenus() {

	//creating the menu and assigning "menuEvents" as the processor. 
	int menu = glutCreateMenu(menuEvents);

	//adding the menu entries
	glutAddMenuEntry("Grid On", ON);
	glutAddMenuEntry("Grid Off", OFF);

	//attaching the menu to the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	// set the current clear color to white and the current 
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0, w, h, 0, -1, 1);
	
	glutSwapBuffers();
}

//code to create the menu bars and the menu elements.
void drawMenuBars() {
	
	//colors for the menu bars
	glColor3f(0.0, 0.5, 0.5);
	
	//horizontal bar
	glBegin(GL_QUADS);
	glVertex2f(0.0,60);
	glVertex2f(80, 60);
	glVertex2f(80.00, 600.0);
	glVertex2f(0.0, 600);
	glEnd();
	
	//verticle bar
	glBegin(GL_QUADS);
	glVertex2f(80, 0.0);
	glVertex2f(800, 0.0);
	glVertex2f(800, 60.0);
	glVertex2f(80, 60.0);
	glEnd();

		
	//1st element on horizontal
	glColor3f(horElement1[0], horElement1[1], horElement1[2]);
	glBegin(GL_QUADS);
	glVertex2f(80, 0);
	glVertex2f(160, 0.0);
	glVertex2f(160.0, 60.0);
	glVertex2f(80.0, 60.0);
	glEnd();
	
	//2nd element on horizontal
	glColor3f(horElement2[0], horElement2[1], horElement2[2]);
	glBegin(GL_QUADS);
	glVertex2f(160, 0);
	glVertex2f(240, 0.0);
	glVertex2f(240.0, 60.0);
	glVertex2f(160.0, 60.0);
	glEnd();
	
	//3rd element on horizontal
	glColor3f(horElement3[0], horElement3[1], horElement3[2]);
	glBegin(GL_QUADS);
	glVertex2f(240, 0);
	glVertex2f(320, 0.0);
	glVertex2f(320.0, 60.0);
	glVertex2f(240.0, 60.0);
	glEnd();

	//1st element on verticle
	glColor3d(verElement1[0], verElement1[1], verElement1[2]);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 60.0);
	glVertex2f(80.0, 60.0);
	glVertex2f(80.0, 120.0);
	glVertex2f(0.0, 120.0);
	glEnd();
	
	//2nd element on verticle
	glColor3d(verElement2[0], verElement2[1], verElement2[2]);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 120.0);
	glVertex2f(80.0, 120.0);
	glVertex2f(80.0, 180.0);
	glVertex2f(0.0, 180.0);
	glEnd();

	//3rd element on 
	glColor3d(verElement3[0], verElement3[1], verElement3[2]);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 180.0);
	glVertex2f(80.0, 180.0);
	glVertex2f(80.0, 240.0);
	glVertex2f(0.0, 240.0);
	glEnd();

	//4th element on verticle
	glColor3d(verElement4[0], verElement4[1], verElement4[2]);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 240.0);
	glVertex2f(80.0, 240.0);
	glVertex2f(80.0, 300.0);
	glVertex2f(0.0, 300.0);
	glEnd();


	//lines that separate the menus elements
	//assinging the colors for the lines
	glColor3f(0.0, 0.0, 0.0);

	//1st line on horizontal
	glBegin(GL_LINES);
	glVertex2f(160, 0.0);
	glVertex2f(160, 60.0);
	glEnd();

	//2nd line on horizontal
	glBegin(GL_LINES);
	glVertex2f(240, 0.0);
	glVertex2f(240, 60.0);
	glEnd();
	
	//3rd line onn horizontal
	glBegin(GL_LINES);
	glVertex2f(320, 0.0);
	glVertex2f(320, 60.0);
	glEnd();
	
	//1st line on verticle
	glBegin(GL_LINES);
	glVertex2f(0.0, 120.0);
	glVertex2f(80.0, 120.0);
	glEnd();

	//2nd line on verticle
	glBegin(GL_LINES);
	glVertex2f(0.0, 180.0);
	glVertex2f(80.0, 180.0);
	glEnd();
	
	//3rd line on verticle
	glBegin(GL_LINES);
	glVertex2f(0.0, 240.0);
	glVertex2f(80.0, 240.0);
	glEnd();
	
	//4th line on verticle
	glBegin(GL_LINES);
	glVertex2f(0.0, 300.0);
	glVertex2f(80.0, 300.0);
	glEnd();
	
	//lines that seperate the menu bars from the canvas
	//horizontal menu line
	glBegin(GL_LINES);
	glVertex2f(80.0, 0.00);
	glVertex2f(80.0, 600.0);
	glEnd();
	
	//verticle menu line
	glBegin(GL_LINES);
	glVertex2f(0.0, 60.0);
	glVertex2f(800.0, 60.0);
	glEnd();
	
	//iincreasing the width of lines
	glLineWidth(2);

	//menu elements
	//1st element (point) on the verticle menu bar
	glPointSize(5);	//increasing the point size.
	glBegin(GL_POINTS);
	glVertex2f( 40 , 90 );
	glEnd();
	
	//2nd element(line) on the verticle menu bar
	glBegin(GL_LINES);
	glVertex2f(70, 130);
	glVertex2f(10, 170);
	glEnd();
	
	//3rd element(square) on the verticle menu bar
	glBegin(GL_LINE_LOOP);
	glVertex2f(10, 190);
	glVertex2f(70, 190);
	glVertex2f(70, 230);
	glVertex2f(10, 230);
	glEnd();
	
	//4h element(triangle) on the verticle menu bar
	glBegin(GL_LINE_LOOP);
	glVertex2f(70, 250);
	glVertex2f(70, 290);
	glVertex2f(10, 290);
	glEnd();
	
	//1st element (tiangle)on the horizontal menu bar
	glBegin(GL_TRIANGLES);
	glVertex2f(150, 10);
	glVertex2f(150, 50);
	glVertex2f(90, 50);
	glEnd();
	
	//2nd element(square) on the horizontal mnu bar
	glBegin(GL_QUADS);
	glVertex2f(170, 10);
	glVertex2f(230, 10);
	glVertex2f(230, 50);
	glVertex2f(170, 50);
	glEnd();
	
	//3rd element (circle) on the horizontal menu bar
	int triangleAmount = 32; //# of triangles used to draw circle
	GLfloat twoPi = 2.0f * 3.141592f;

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			280 + (25 * cos(i *  twoPi / triangleAmount)),
			30 + (25 * sin(i * twoPi / triangleAmount))
		);
	}
	glEnd();
}

// drawing on a point on mouse click coordinates.
void drawPoint(float x, float y) {
	//storing the x1,y1 coordinates in array to allow multiple points to be drawn.
	if (!(changeDot == 1000)) {
		points[changeDot][0] = { mousex };
		points[changeDot][1] = { mousey };
		changeDot++;
	}
	else {
		changeDot = 0;
	}

	glPushMatrix(); //storing current coordinates in stack.
	glTranslatef(pX, pY, pZ); //translating the point
	//drawing the point.
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 1000; i++) {
		if (points[i][0] != 0 && points[i][1] != 0) {
			glBegin(GL_POINTS);
			glVertex2f(points[i][0], points[i][1]);
			glEnd();
		}
		
	}
	glPopMatrix(); //calling the orginal coordinates from stack.
}

//drawing line on two mouse click points.
void drawLine(float x1, float cy1, float x2, float y2) {

	//stornig the x1,y1,x2,y2 coordinates in array to allow multiple lines to be drawn.
	if (!(li == 1000)) {
		lines[li][0] = { x1 };
		lines[li][1] = { cy1 };
		lines[li][2] = { x2 };
		lines[li][3] = { y2 };

		li++;
	}
	else {
		li = 0;
	}

	glPushMatrix();//storing the current coordniates in stack
	glTranslatef(lX, lY, lZ); //translating the line

	//drawing the line
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 1000; i++) {
		
		if ((lines[i][0] != 0 && lines[i][1] != 0)&& (lines[i][2] != 0 && lines[i][3] != 0)) {
			glBegin(GL_LINES);
			glVertex2f(lines[i][0], lines[i][1]);
			glVertex2f(lines[i][2], lines[i][3]);
			glEnd();
		}
		
	}
	glPopMatrix(); //calling th orignial coordinates from stack
}

//drawing rectangle on mouse click as center.
void drawRectangle(float x,float y) {

	//stroing the center point in array to allow multiple rectangles to be drawn.
	if (!(rect == 1000)) {
		rectangles[rect][0] = {x};
		rectangles[rect][1] = {y};
		rect++;
	}
	else {
		rect = 0;
	}
	glPushMatrix();//storing the current coordinates in stack.
	glTranslatef(rX, rY, rZ); // translating the rectangle.

	//drawing the rectangle.
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 1000; i++) {
		if (rectangles[i][0] != 0 && rectangles[i][1] != 0) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(rectangles[i][0] + 80, rectangles[i][1] + 45);
			glVertex2f(rectangles[i][0] - 80, rectangles[i][1] + 45);
			glVertex2f(rectangles[i][0] - 80, rectangles[i][1] - 45);
			glVertex2f(rectangles[i][0] + 80, rectangles[i][1] - 45);
			glEnd();
		}
	}
	glPopMatrix();// calling the original coordinates from stack.

}

//drawing triangle on mouse click as center.
void drawTriangle(float x, float y) {

	//storing the center point of the triangle in an array to allow multiple triangles to be drawn.
	if (!(tri == 1000)) {
		triangles[tri][0] = { x };
		triangles[tri][1] = { y };
		tri++;
	}
	else {
		tri = 0;
	}

	glPushMatrix(); //storing the current coordinates in stack
	glTranslatef(tX, tY, tZ); //translating the triangle.

	//drawing the triangle.
	glColor3f(1.0, 0.0, 0.0);

	for (int i = 0; i < 1000; i++) {
		if (triangles[i][0] != 0 && triangles[i][1] != 0)  {
			glBegin(GL_LINE_LOOP);
			glVertex2f(triangles[i][0] + 80, triangles[i][1] + 45);
			glVertex2f(triangles[i][0] - 80, triangles[i][1] + 45);
			glVertex2f(triangles[i][0] - 80, triangles[i][1] - 45);
			glEnd();
		}
	}
	glPopMatrix();//calling the orignial coordinates from stack.
}

//drawing polygon trianlge on mouse click as center
void drawPolyTriangle(float x, float y) {
	 //storing the x,y coordinates in array to allow multiple poly trinalges to be drawn
	if (!(polyTri == 1000)) {
		polyTriangles[polyTri][0] = { x };
		polyTriangles[polyTri][1] = { y };
		polyTri++;
	}
	else {
		polyTri = 0;
	}

	glPushMatrix(); //storing the current coordinates in stack
	glTranslatef(ptX, ptY, ptZ);// translating the polygon triangle.

	//drawing the poly triangle
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 1000; i++) {
		if (polyTriangles[i][0] != 0 && polyTriangles[i][1] != 0) {
			glBegin(GL_TRIANGLES);
			glVertex2f(polyTriangles[i][0] + 80, polyTriangles[i][1] + 45);
			glVertex2f(polyTriangles[i][0] - 80, polyTriangles[i][1] + 45);
			glVertex2f(polyTriangles[i][0] - 80, polyTriangles[i][1] - 45);
			glEnd();
		}
	}
	glPopMatrix();//calling the original coordinates from the stack
}

//drawing polygon rectangle on mouse click as center
void drawPolyRectangle(float x, float y) {

	//storing the center point in array to allow multiple Poly Rectangles to be drawn.
	if (!(polyRect == 1000)) {
		polyRectangles[polyRect][0] = { x };
		polyRectangles[polyRect][1] = { y };
		polyRect++;
	}
	else {
		polyRect = 0;
	}

	glPushMatrix();//storing the current coordinates in the stack.
	glTranslatef(prX, prY, prZ);//translating the polygon rectangle

	//drawing the Poly Rectangle.
	glColor3f(1.0, 0.0, 0.0);
	
	for (int i = 0; i < 1000; i++) {
		if (polyRectangles[i][0] != 0 && polyRectangles[i][1] != 0) {
			glBegin(GL_QUADS);
			glVertex2f(polyRectangles[i][0] + 80, polyRectangles[i][1] + 45);
			glVertex2f(polyRectangles[i][0] - 80, polyRectangles[i][1] + 45);
			glVertex2f(polyRectangles[i][0] - 80, polyRectangles[i][1] - 45);
			glVertex2f(polyRectangles[i][0] + 80, polyRectangles[i][1] - 45);
			glEnd();
		}
	}
	glPopMatrix();//calling the original coordinates from the stack.


}

//drawing polygon circle on mouse click as center
void drawPolyCircle(float x, float y) {
	if (!(polyCir == 1000)) {
		polyCircle[polyCir][0] = { x };
		polyCircle[polyCir][1] = { y };
		polyCir++;
	}
	else {
		polyCir = 0;
	}



	int triangleAmount = 32; //# of triangles used to draw circle
	GLfloat twoPi = 2.0f * 3.141592f;
	glPushMatrix(); //storing the current coordinates in stack.
	glTranslatef(pcX, pcY, pcZ);//translating the polygon circle.

	glColor3f(1.0,0.0,0.0);
	for (int i = 0; i < 1000; i++) {
		if (polyCircle[i][0] != 0 && polyCircle[i][1] != 0) {
			glBegin(GL_TRIANGLE_FAN);
			for (int j = 0; j <= triangleAmount; j++) {
				glVertex2f(
					polyCircle[i][0] + (50 * cos(j *  twoPi / triangleAmount)),
					polyCircle[i][1] + (50 * sin(j * twoPi / triangleAmount))
				);
			}
			glEnd();
		}
	}
	glPopMatrix();//calling the original coordinates from stack.

}

//used to clear the drawn object according to keypress
void clearObjects(int i) {

	//clear circles
	if (i == 5) {
		for (int i = 0; i < 1000; i++) {
			polyCircle[i][0] = NULL;
			polyCircle[i][1] = NULL;
		}
	}

	//clear triangles
	if (i == 4) {
		for (int i = 0; i < 1000; i++) {
			triangles[i][0] =NULL;
			triangles[i][1] = NULL;
			polyTriangles[i][0] = NULL;
			polyTriangles[i][1] = NULL;
		}
	}

	//clear rectangles
	if (i == 3) {
		for (int i = 0; i < 1000; i++) {
			rectangles[i][0] = NULL;
			rectangles[i][1] = NULL;
			polyRectangles[i][0] = NULL;
			polyRectangles[i][1] = NULL;
		}
	}
	//clear lines
	if (i == 2) {
		for (int i = 0; i < 1000; i++) {
			lines[i][0] = NULL;
			lines[i][1] = NULL;
			lines[i][2] = NULL;
			lines[i][3] = NULL;
		}
	}

	//clear Points
	if (i == 1) {
		for (int i = 0; i < 1000; i++) {
			points[i][0] = NULL;
			points[i][1] = NULL;
		}
	}
	
}

//used to detect which primitive is selected and to highlight it
void selectPrimitive() {
	//drawing dot if selected
	if (SelectedD == 1) {
		//highlighting when selected
		verElement1[0] = { 1.0 };
		verElement1[1] = { 0.0 };
		verElement1[2] = { 0.0 };

		drawPoint(mousex, mousey);
	}
	else {
		//de-hilighting when not selected
		verElement1[0] = { 0.0 };
		verElement1[1] = { 0.8 };
		verElement1[2] = { 0.5 };
	}

	//drawing line if selected
	if (SelectedL == 1) {
		//highlighting when selected
		verElement2[0] = { 1.0 };
		verElement2[1] = { 0.0 };
		verElement2[2] = { 0.0 };

		drawLine(xi, yi, xf, yf);
	}
	else {
		//de-hilighting when not selected
		verElement2[0] = { 0.0 };
		verElement2[1] = { 0.8 };
		verElement2[2] = { 0.5 };
	}

	//drawing rectangle if selected
	if (SelectedR == 1) {
		//highlighting when selected
		verElement3[0] = { 1.0 };
		verElement3[1] = { 0.0 };
		verElement3[2] = { 0.0 };

		drawRectangle(mousex, mousey);
	}
	else {
		//de-hilighting when not selected
		verElement3[0] = { 0.0 };
		verElement3[1] = { 0.8 };
		verElement3[2] = { 0.5 };
	}


	//drawing triangle if selected
	if (SelectedT == 1) {
		//highlighting when selected
		verElement4[0] = { 1.0 };
		verElement4[1] = { 0.0 };
		verElement4[2] = { 0.0 };

		drawTriangle(mousex, mousey);
	}
	else {
		//de-hilighting when not selected
		verElement4[0] = { 0.0 };
		verElement4[1] = { 0.8 };
		verElement4[2] = { 0.5 };
	}

	//drawing polygon triangle if selected
	if (SelectedPT == 1) {
		//highlighting when selected
		horElement1[0] = { 1.0 };
		horElement1[1] = { 0.0 };
		horElement1[2] = { 0.0 };

		drawPolyTriangle(mousex, mousey);
	}
	else {
		//de-hilighting when not selected
		horElement1[0] = { 0.0 };
		horElement1[1] = { 0.8 };
		horElement1[2] = { 0.5 };
	}

	//drawing polygon rectangle if selected
	if (SelectedPR == 1) {
		//highlighting when selected
		horElement2[0] = { 1.0 };
		horElement2[1] = { 0.0 };
		horElement2[2] = { 0.0 };

		drawPolyRectangle(mousex, mousey);
	}
	else {
		//de-hilighting when not selected
		horElement2[0] = { 0.0 };
		horElement2[1] = { 0.8 };
		horElement2[2] = { 0.5 };
	}


	//drawing polygon circle if selected
	if (SelectedCR == 1) {
		//highlighting when selected
		horElement3[0] = { 1.0 };
		horElement3[1] = { 0.0 };
		horElement3[2] = { 0.0 };

		drawPolyCircle(mousex, mousey);
	}
	else {
		//de-hilighting when not selected
		horElement3[0] = { 0.0 };
		horElement3[1] = { 0.8 };
		horElement3[2] = { 0.5 };
	}

}

//used to display everything
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawGrid();		//drawing the grid if it's set to be 'on'
	drawMenuBars(); //drawing the menu bars
	selectPrimitive(); //selecting the clicked primitive from the menu bar
	glutSwapBuffers();
}

//code to capture keyboard input
void keyInput(unsigned char key, int x, int y)
{
	switch (key){
		//checking if escape key is pressed.
	case 27:
		exit(0);
		break;
	case 32: //checking if spcaebar is pressed
		clearObjects(1);
		clearObjects(2);
		clearObjects(3);
		clearObjects(4);
		clearObjects(5);
		break;
	case 'p':
		clearObjects(1);
		break;
	case 'l':
		clearObjects(2);
		break;
	case 'r':
		clearObjects(3);
		break;
	case 't':
		clearObjects(4);
		break;
	case 'c':
		clearObjects(5);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

//code to capture special key inputs
void specialKeys(int key, int x, int y) {
	switch (key) {

		//checking which key is pressed and performaing translation accordinly.
	case GLUT_KEY_RIGHT:
		//translating only the object that is selected from the menu.
		if (SelectedD == 1) {
			pX = pX + 1;
			pY = pY;
			pZ = pZ;
		}

		if (SelectedL == 1) {
			lX = lX + 1;
			lY = lY;
			lZ = lZ;
		}
	

		if (SelectedR == 1) {
			rX = rX + 1;
			rY = rY;
			rZ = rZ;
		}
	
		if (SelectedT == 1) {
			tX = tX + 1;
			tY = tY;
			tZ = tZ;
		}
	
		if (SelectedPT == 1) {
			ptX = ptX + 1;
			ptY = ptY;
			ptZ = ptZ;
		}
	
		if (SelectedPR == 1) {
			prX = prX + 1;
			prY = prY;
			prZ = prZ;
		}

		if (SelectedCR == 1) {
			pcX = pcX + 1;
			pcY = pcY;
			pcZ = pcZ;
		}
		
		break;
	case GLUT_KEY_LEFT:
		if (SelectedD == 1) {
			pX = pX - 1;
			pY = pY;
			pZ = pZ;
		}

		if (SelectedL == 1) {
			lX = lX - 1;
			lY = lY;
			lZ = lZ;
		}


		if (SelectedR == 1) {
			rX = rX - 1;
			rY = rY;
			rZ = rZ;
		}

		if (SelectedT == 1) {
			tX = tX - 1;
			tY = tY;
			tZ = tZ;
		}

		if (SelectedPT == 1) {
			ptX = ptX - 1;
			ptY = ptY;
			ptZ = ptZ;
		}

		if (SelectedPR == 1) {
			prX = prX - 1;
			prY = prY;
			prZ = prZ;
		}

		if (SelectedCR == 1) {
			pcX = pcX - 1;
			pcY = pcY;
			pcZ = pcZ;
		}

		break;
	case GLUT_KEY_DOWN:
		if (SelectedD == 1) {
			pX = pX ;
			pY = pY + 1;
			pZ = pZ;
		}

		if (SelectedL == 1) {
			lX = lX ;
			lY = lY + 1;
			lZ = lZ;
		}


		if (SelectedR == 1) {
			rX = rX ;
			rY = rY + 1;
			rZ = rZ;
		}

		if (SelectedT == 1) {
			tX = tX ;
			tY = tY + 1;
			tZ = tZ;
		}

		if (SelectedPT == 1) {
			ptX = ptX ;
			ptY = ptY + 1;
			ptZ = ptZ;
		}

		if (SelectedPR == 1) {
			prX = prX ;
			prY = prY + 1;
			prZ = prZ;
		}

		if (SelectedCR == 1) {
			pcX = pcX;
			pcY = pcY + 1;
			pcZ = pcZ;
		}


		break;
	case GLUT_KEY_UP:
		if (SelectedD == 1) {
			pX = pX;
			pY = pY - 1;
			pZ = pZ;
		}

		if (SelectedL == 1) {
			lX = lX;
			lY = lY - 1;
			lZ = lZ;
		}


		if (SelectedR == 1) {
			rX = rX;
			rY = rY - 1;
			rZ = rZ;
		}

		if (SelectedT == 1) {
			tX = tX;
			tY = tY - 1;
			tZ = tZ;
		}

		if (SelectedPT == 1) {
			ptX = ptX;
			ptY = ptY - 1;
			ptZ = ptZ;
		}

		if (SelectedPR == 1) {
			prX = prX;
			prY = prY - 1;
			prZ = prZ;
		}

		if (SelectedCR == 1) {
			pcX = pcX;
			pcY = pcY - 1;
			pcZ = pcZ;
		}


		break;
		
	}
	glutPostRedisplay();
}

//code to caputre mouse input
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		xi = 0;
		yi = 0;
		xf = 0;		//assigning 0 as coordinates to break line continuation
		yf = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

		//checking if clicked inside the canvas
		if (x > 80 && y > 60) {

			//assigning mouse x and y coordinates to varibles
			mousex = (x);
			mousey = (y);

			//check if Line is selected to draw.
			if (SelectedL == 1) {
				//getting coordinates to draw line.
				switch (click)
				{
				case 0:
					xi = x;
					yi = y;
					click = 2;
					break;
				case 2:
					xf = x;
					yf = y;
					click = 0;
					break;
				}
			}
		}


		//checking if clicked inside the verticle  menu bar.
		if (x < 80 && y < 300) {

			//selecting the point to draw.
			if (y > 60 && y < 120) {
				if (SelectedD == 1) {
					SelectedD = 0;					
				}
				else {
					SelectedD = 1;
				}
			}

			//selecting the line to draw.
			if (y > 120 && y < 180) {
				if (SelectedL == 1) {
					SelectedL = 0;
				}
				else {
					SelectedL = 1;
				}
			}

			//selecting the square to draw.
			if (y > 180 && y < 240) {
				if (SelectedR == 1) {
					SelectedR = 0;
				}
				else {
					SelectedR = 1;
				}
			}

			//selecting the triangle to draw.
			if (y > 240 && y < 300) {
				if (SelectedT == 1) {
					SelectedT = 0;
				}
				else {
					SelectedT = 1;
				}
			}
		}

		//checking if clicked inside the horizontal menu bar.
		if (x > 80 && y < 60) {
			//selecting the PolyTriangle to draw.
			if (x > 80 && x < 160) {
				if (SelectedPT == 1) {
					SelectedPT = 0;
				}
				else {
					SelectedPT = 1;
				}
			}

			//selecting the PolyRectangle to draw.
			if (x > 160 && x < 240) {
				if (SelectedPR == 1) {
					SelectedPR = 0;
				}
				else {
					SelectedPR = 1;
				}
			}

			//selecting the PolyCircle to draw.
			if (x > 240 && x < 320) {
				if (SelectedCR == 1) {
					SelectedCR = 0;
				}
				else {
					SelectedCR = 1;
				}
			}
		}
	}
	glutPostRedisplay();
}

//display the instructions in the console window
void instructions() {
	cout << "CONTROLS AND INSTRUCTIONS" << endl;
	cout << "---------------------------" << endl;
	cout << "- right click to get pop up menu to turn on/off grid " << endl;
	cout << "- Left click on primitive or polygon to select it." << endl;
	cout << "- left click on canvas to darw. " << endl;
	cout << "- click on two points to draw a line. " << endl;
	cout << "- click Middle mouse button to discontinue line " << endl;
	cout << "- use to folling to clear: " << endl;
	cout << "           -p = clear points." << endl;
	cout << "           -l = clear lines." << endl;
	cout << "           -r = clear rectangles." << endl;
	cout << "           -t = clear triangles." << endl;
	cout << "           -c = clear circles." << endl;
	cout << "           -SpaceBar = clear Canvas fully." << endl;
}

int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for the display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "2D Drawing Canvas"
	glutCreateWindow("2D Drawing Canvas");
	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(reshape);
	instructions(); //displaying the instructions in the console window
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeys);
	createGLUTMenus();
	glutMouseFunc(myMouse);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
