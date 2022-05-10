/* 
Carlos Bueno Project
Used Code from example files to get overall skeleton
Used Code from hw 6 as well
https://stackoverflow.com/questions/28547173/creating-a-3d-room-in-opengl-c for wall idea
https://stackoverflow.com/questions/32883572/how-to-draw-cylinder-in-modern-opengl to learn how to make a cylinder correctly
*/
#include "CSCIx229.h"
int mode = 1;
int move = 1;       //  Move light
int th = 57.0;      //  Azimuth of view angle
int ph = 10.0;      //  Elevation of view angle
int fov = 55;      //  Field of view (for perspective)
double asp = 1;    //  Aspect ratio
double dim = 800.0; //  Size of world
// Light values
int light = 1;      //  Lighting
int one = 1;		// Unit value
int distance = 820;	// Light distance
int inc = 15;		// Ball increment
int smooth = 1;		// Smooth/Flat shading
int local = 0;		// Local Viewer Model
int emission = 0;	// Emission intensity (%)
int ambient = 40;	// Ambient intensity (%)
int diffuse = 70;  // Diffuse intensity (%)
int specular = 0;	// Specular intensity (%)
int shininess = 0;  // Shininess (power of two)
float shiny = 1;	// Shininess (value)
int zh =80;		// Light azimuth
float ylight = 0;	// Elevation of light
int rotation = 0.0;
int wall_toggle = 1;			// Turn the walls on

// Texture values
unsigned int texture[10]; // Texture names

//Draw Walls
static void walls() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_QUADS);
	//bottom
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(-555, -10, -555);
	glTexCoord2f(3, 0); glVertex3f(555, -10, -555);
	glTexCoord2f(3, 3); glVertex3f(555, -10, 555);
	glTexCoord2f(0, 3); glVertex3f(-555, -10, 555);
	//right
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0, 0); glVertex3f(-555, -10, 555);
	glTexCoord2f(3, 0); glVertex3f(555, -10, 555);
	glTexCoord2f(3, 3); glVertex3f(555, 555, 555);
	glTexCoord2f(0, 3); glVertex3f(-555, 555, 555);
	//left
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(-555, -10, -555);
	glTexCoord2f(3, 0); glVertex3f(555, -10, -555);
	glTexCoord2f(3, 3); glVertex3f(555, 555, -555);
	glTexCoord2f(0, 3); glVertex3f(-555, 555, -555);
	//back
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(555, 555, 555);
	glTexCoord2f(3, 0); glVertex3f(555, -10, 555);
	glTexCoord2f(3, 3); glVertex3f(555, -10, -555);
	glTexCoord2f(0, 3); glVertex3f(555, 555, -555);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Draw floor
static void base_floor() {
	// Textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[5]);
	glBegin(GL_QUADS);
	//Floor
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(-530, 0, -530);
	glTexCoord2f(2, 0); glVertex3f(530, 0, -530);
	glTexCoord2f(2, 2); glVertex3f(530, 0, 530);
	glTexCoord2f(0, 2); glVertex3f(-530, 0, 530);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
//drawcan (from hw6)
void drawCan(double x,double y,double z,double dx,double dy,double dz,double th) { //(figured out how to make using https://stackoverflow.com/questions/32883572/how-to-draw-cylinder-in-modern-opengl)
	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	glPushMatrix();
	//Tranformation
	glTranslated(x,y,z);
	glRotated(th,0,0,1);
	glScaled(dx,dy,dz);
	// Textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[7]);
	//Cylinder tube for Can 
	double rad = 0.3; 
	double height = 0.2;
	glBegin(GL_QUAD_STRIP);
	for (double i = 0; i <= 360; i+=0.125) {
		const float u = (i / (float) 360);
		double x = rad * Cos(i);
		double y = height;
		double z = rad * Sin(i);
		glNormal3d(Cos(i), 0, Sin(i));
		glTexCoord2f(-u, 0.0); glVertex3d(x, -y, z);
		glTexCoord2f(-u, 1.0); glVertex3d(x, y, z);
	}
	glEnd();
   glBindTexture(GL_TEXTURE_2D,texture[8]);
    //Top of Can
   glNormal3d(0,1,0);
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, height, 0.0);
      for(double i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(rad * Cos(i), height, rad * Sin(i));
      }
   glEnd();
   glBindTexture(GL_TEXTURE_2D,texture[9]);
   //Bottom of Can
   glNormal3d(0,-1,0);
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, -height, 0.0);
      for(double i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(rad * Cos(i), -height, rad * Sin(i));
      }
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D); 
}

//Function to save space when making faces of an rectuanglar object along with adding textures
static void helper(double x, double y, double z) {
	glPushMatrix();
	glBegin(GL_QUADS);

	glNormal3d(0, 0, 1);
	glTexCoord2d(0, 0); glVertex3d(-x, y, z);
	glTexCoord2d(0, 1); glVertex3d(-x, -y, z);
	glTexCoord2d(1, 1); glVertex3d(x, -y, z); 
	glTexCoord2d(1, 0); glVertex3d(x, y, z);

	glNormal3d(1, 0, 0);
	glTexCoord2d(0, 0); glVertex3d(x, y, z);
	glTexCoord2d(0, 1); glVertex3d(x, -y, z);
	glTexCoord2d(1, 1); glVertex3d(x, -y, -z);
	glTexCoord2d(1, 0); glVertex3d(x, y, -z);
	glNormal3d(0, 0, -1);

	glTexCoord2d(1, 0); glVertex3d(x, y, -z);
	glTexCoord2d(1, 1); glVertex3d(x, -y, -z);
	glTexCoord2d(0, 1); glVertex3d(-x, -y, -z);
	glTexCoord2d(0, 0); glVertex3d(-x, y, -z);

	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 1); glVertex3d(-x, y, -z);
	glTexCoord2d(0, 0); glVertex3d(-x, -y, -z);
	glTexCoord2d(1, 0); glVertex3d(-x, -y, z);
	glTexCoord2d(1, 1); glVertex3d(-x, y, z);

	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0); glVertex3d(-x, y, z);
	glTexCoord2d(1, 0); glVertex3d(x, y, z);
	glTexCoord2d(1, 1); glVertex3d(x, y, -z);
	glTexCoord2d(0, 1);glVertex3d(-x, y, -z); 

	glNormal3d(0, -1, 0);
	glTexCoord2d(0, 1); glVertex3d(-x, -y, -z);
	glTexCoord2d(1, 1); glVertex3d(x, -y, -z);
	glTexCoord2d(1, 0); glVertex3d(x, -y, z);
	glTexCoord2d(0, 0); glVertex3d(-x, -y, z);

	glEnd();
	glPopMatrix();
}

// Draws the TV Hutch (used glucylinder for legs to save space rather than using cylinder code from can)
static void tv_hutch(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);
	glColor3d(0.6, 0.6, 0.6);

	glPushMatrix();
	glTranslated(0, 2.8, 0);
	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glNormal3d(0, 0, 1);
	glVertex3f(-35, 0, -49);
	glVertex3f(-35, 0, 49);
	glVertex3f(35, 0, 49);
	glVertex3f(35, 0, -49);
	glEnd();
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -2.8, 0);
	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glNormal3d(0, 0, 1);
	glVertex3f(-35, 0, -49);
	glVertex3f(-35, 0, 49);
	glVertex3f(35, 0, 49);
	glVertex3f(35, 0, -49);
	glEnd();
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix();

	glPushMatrix();
	glTranslated(28, 0, 42);
	glRotated(90,1, 0, 0);
	gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-28, 0,42);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(28, 0, -42);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-28, 0, -42);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 3.5, 2.1, 56, 20, 20);
	glPopMatrix();

}
// Draw couch
static void couch(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glTranslated(-44, 0, 0);
	helper(7.7, 36, 36);

	glTranslated(92, 0, 0);
	helper(7.7, 36, 36);

	glTranslated(-44, 0, 0);
	glRotated(6, -1, 0, 0);
	glTranslated(0, -1, 0);
	helper(42, 2, 23);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, 6, 3);
	helper(41, 6, 26);
	glTranslated(0, 23, -21);
	glRotated(90, -1, 0, 0);
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	helper(42, 2, 23);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTranslated(0, -6, 3);
	helper(41, 6, 36);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//Draw Chair
static void chair(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslated(-46, 0, 0);
	helper(7, 39.8, 39.8);

	glTranslated(96, 0, 0);
	helper(7, 39.8, 39.8);

	glTranslated(-46, 0, 0);
	glRotated(6, -1, 0, 0);
	glTranslated(0, -1, -20);
	helper(44, 2, 29.8);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, 6.33, 3);
	helper(43, 6.33, 25.8);

	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslated(0, 29.8, -27.8);
	glRotated(90, -1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	helper(44, 2, 29.8);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, -6.33, 3);
	helper(43, 6.33, 25.8);

	glBindTexture(GL_TEXTURE_2D, 0);

}

// Draw  tv
static void tv(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0, 0); glVertex3f(-46, 9, -55);
	glTexCoord2f(1, 0); glVertex3f(46, 9, -55);
	glTexCoord2f(1, 1); glVertex3f(46, 100, -55);
	glTexCoord2f(0, 1); glVertex3f(-46, 100, -55);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(-46, 9, -46);
	glTexCoord2f(1, 0); glVertex3f(46, 9, -46);
	glTexCoord2f(1, 1); glVertex3f(46, 100, -46);
	glTexCoord2f(0, 1); glVertex3f(-46, 100, -46);

	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(-46, 9, -55);
	glTexCoord2f(1, 0); glVertex3f(-46, 100, -55);
	glTexCoord2f(1, 1); glVertex3f(-46, 100, -46);
	glTexCoord2f(0, 1); glVertex3f(-46, 9, -46);

	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(46, 9, -55);
	glTexCoord2f(1, 0); glVertex3f(46, 100, -55);
	glTexCoord2f(1, 1); glVertex3f(46, 100, -46);
	glTexCoord2f(0, 1); glVertex3f(46, 9, -46);

	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(-46, 100, -55);
	glTexCoord2f(1, 0); glVertex3f(-46, 100, -46);
	glTexCoord2f(1, 1); glVertex3f(46, 100, -46);
	glTexCoord2f(0, 1); glVertex3f(46, 100, -55);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Draw dining table
static void dining_table(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);
	//legs
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glTranslated(-40, 0, -90);
	GLUquadric *holder = gluNewQuadric();
	gluQuadricTexture(holder, GL_TRUE);
	glTranslated(0, -45, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder, 6.7, 8, 90, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 45, 0);
	gluDeleteQuadric(holder);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, -90);
	GLUquadric *holder2 = gluNewQuadric();
	gluQuadricTexture(holder2, GL_TRUE);
	glTranslated(0, -45, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder2, 6.7, 8, 90, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 45, 0);
	gluDeleteQuadric(holder2);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-40, 0, 90);
	GLUquadric *holder3 = gluNewQuadric();
	gluQuadricTexture(holder3, GL_TRUE);
	glTranslated(0, -45, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder3, 6.7, 8, 90, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 45, 0);
	gluDeleteQuadric(holder3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, 90);
	GLUquadric *holder4 = gluNewQuadric();
	gluQuadricTexture(holder4, GL_TRUE);
	glTranslated(0, -45, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder4, 6.7, 8, 90, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 45, 0);
	gluDeleteQuadric(holder4);
	glPopMatrix();
	//table top
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslated(0, 45, 0);
	helper(50, 4.5, 100);
	glDisable(GL_TEXTURE_2D);
	
}

//Console Table
static void console_table(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	
	glPushMatrix();
	glTranslated(-40, 0, -90);
	GLUquadric *holder = gluNewQuadric();
	gluQuadricTexture(holder, GL_TRUE);
	glTranslated(0, -30, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder, 6.7, 8, 60, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 30, 0);
	gluDeleteQuadric(holder);
	glPopMatrix();

	glPushMatrix();
	glTranslated(40, 0, -90);
	GLUquadric *holder2 = gluNewQuadric();
	gluQuadricTexture(holder2, GL_TRUE);
	glTranslated(0, -30, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder2, 6.7, 8, 60, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 30, 0);
	gluDeleteQuadric(holder2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-40, 0, 90);
	GLUquadric *holder3 = gluNewQuadric();
	gluQuadricTexture(holder3, GL_TRUE);
	glTranslated(0, -30, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder3, 6.7, 8, 60, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 30, 0);
	gluDeleteQuadric(holder3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(40, 0, 90);
	GLUquadric *holder4 = gluNewQuadric();
	gluQuadricTexture(holder4, GL_TRUE);
	glTranslated(0, -30, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(holder4, 6.7, 8, 60, 10, 10);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, 30, 0);
	gluDeleteQuadric(holder4);
	glPopMatrix();
	
	glTranslated(0, 30, 0);
	helper(50, 3, 100);
	glDisable(GL_TEXTURE_2D);
}

static void box_tv(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white (Code reuse from Ex 13)
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,0,+1,0);
	glScaled(dx,dy,dz);
	// Enable Textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//  box_tv Body
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	glBegin(GL_QUADS);
	//  Front of box_tv
	glNormal3f(0, 0, +1);
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,-1, 1);
	glTexCoord2f(1.0, 0.0);glVertex3f(+1,-1, 1);
	glTexCoord2f(1.0, 1.0);glVertex3f(+1,+1, 1);
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,+1, 1);

	//  Right of box_tv
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,+1);
	glTexCoord2f(1.0, 0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(1.0, 1.0); glVertex3f(+1,+1,-1);
	glTexCoord2f(0.0, 1.0); glVertex3f(+1,+1,+1);
	//  Left of box_tv
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1,-1,+1);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1,+1,+1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1,+1,-1);
	//  Top of box_tv
	glNormal3f(0, +1, 0);
	glVertex3f(-1,+1,+1);
	glVertex3f(+1,+1,+1);
	glVertex3f(+1,+1,-1);
	glVertex3f(-1,+1,-1);
	//  Bottom box_tv
	glNormal3f(0, -1, 0);
	glVertex3f(-1,-1,-1);
	glVertex3f(+1,-1,-1);
	glVertex3f(+1,-1,+1);
	glVertex3f(-1,-1,+1);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_TEXTURE_2D); 
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//  Back of box_tv
	glBegin(GL_QUADS);
	glNormal3f(0, 0,-1);
	glNormal3f( 0, 0,-1);
	glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1,+1,-1);
	glTexCoord2f(0.0, 1.0); glVertex3f(+1,+1,-1);
	//  End
	glEnd();
	//  Undo transformations
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix();
}

static void fridge(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white (Code reuse from Ex 13)
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,0,+1,0);
	glScaled(dx,dy,dz);
	// Enable Textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//  fridge Body
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	glBegin(GL_QUADS);
	//  Front of fridge
	glNormal3f(0, 0, +1);
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,-1, 1);
	glTexCoord2f(1, 0.0);glVertex3f(+1,-1, 1);
	glTexCoord2f(1, 1.0);glVertex3f(+1,+1, 1);
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,+1, 1);

	//  Right of fridge
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,+1);
	glTexCoord2f(1.0, 0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(1.0, 1.0); glVertex3f(+1,+1,-1);
	glTexCoord2f(0.0, 1.0); glVertex3f(+1,+1,+1);
	// bottom of fridge
	glNormal3f(0, 0,-1);
	glNormal3f( 0, 0,-1);
	glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1,+1,-1);
	glTexCoord2f(0.0, 1.0); glVertex3f(+1,+1,-1);


	//  Top of fridge
	glNormal3f(0, +1, 0);
	glVertex3f(-1,+1,+1);
	glVertex3f(+1,+1,+1);
	glVertex3f(+1,+1,-1);
	glVertex3f(-1,+1,-1);
	//  Bottom fridge
	glNormal3f(0, -1, 0);
	glVertex3f(-1,-1,-1);
	glVertex3f(+1,-1,-1);
	glVertex3f(+1,-1,+1);
	glVertex3f(-1,-1,+1);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_TEXTURE_2D); 
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	//  left of fridge
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1,-1,+1);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1,+1,+1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1,+1,-1);
	//  End
	glEnd();
	//  Undo transformations
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix();
}


/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th, double ph)
{
	double x = Sin(th)*Cos(ph);
	double y = Cos(th)*Cos(ph);
	double z = Sin(ph);
	//  For a sphere at the origin, the position
	//  and normal vectors are the same
	glNormal3d(x, y, z);
	glVertex3d(x, y, z);
}


/*
 *  Draw vertex in polar coordinates with normal (Code reuse from Ex 13)
 */

static void ball(double x, double y, double z, double r) //(Code reuse from Ex 13)
{

	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glScaled(r, r, r);
	int th, ph;
	float yellow[] = { 1.0,1.0,0.0,1.0 };
	float Emission[] = { 0.0,0.0,0.01*emission,1.0 };
	//  White ball
	glColor3f(1, 1, 1);
	glMaterialf(GL_FRONT, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
	glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
	//  Bands of latitude
	for (ph = -90; ph < 90; ph += inc)
	{
		glBegin(GL_QUAD_STRIP);
		for (th = 0; th <= 360; th += 2 * inc)
		{
			Vertex(th, ph);
			Vertex(th, ph + inc);
		}
		glEnd();
	}
	//  Undo transofrmations
	glPopMatrix();
}
void display() //(some code reuse from Ex 13 mostly for light switch)
{
	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective - set eye position
	if (mode)
	{
		double Ex = -2 * dim*Sin(th)*Cos(ph);
		double Ey = +2 * dim *Sin(ph);
		double Ez = +2 * dim*Cos(th)*Cos(ph);
		gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
	}
	//  Orthogonal - set world orientation
	else
	{
		glRotatef(ph, 1, 0, 0);
		glRotatef(th, 0, 1, 0);
	}
	//  Flat or smooth shading
	glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);
	  //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 10);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
	base_floor();
	if (wall_toggle)
		walls(); 
	couch(-100, 28, 0, 3, 1, 1.5, 0, 0, 0, 0);
	chair(130, -20, -27, 0.5, 1, 1, 95, 1, 0, 0);
	tv_hutch(-260, -280, -35, 2, 1, 0.75, 95, 1, 0, 0);
	drawCan(10, 50, -600, 30, 80, 80 , 0);
	drawCan(35, 50, -630, 30, 80, 80 , 0);
	tv(0, -3.5, 45, 0.75 , 1, 0.75, 0, 0, 0, 0);
	dining_table(0, -9, -900, 1.5, 1, 1, 0, 0, 0, 0);
	console_table(-5, -65, 600, 1, 0.7, 0.3, 0, 1, 0, 0);
	box_tv(120,0,400,20,100,100,0.0);
	fridge(170,240,-2000,20,300,300,0.0);
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Render the scene
   glFlush();
   glutSwapBuffers();
}
 
/*
 *  GLUT calls this routine when the window is resized (Code reuse from Ex 13)
 */
void idle()
{
	//  Elapsed time in seconds
	double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	zh = fmod(90 * t, 360.0);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed (reused from past hw)
 */
void special(int key, int x, int y) 
{
		//  Right arrow key - increase angle by 5 degrees
		if (key == GLUT_KEY_RIGHT)
			th += 10;
		//  Left arrow key - decrease angle by 5 degrees
		else if (key == GLUT_KEY_LEFT)
			th -= 10;
		//  Up arrow key - increase elevation by 5 degrees
		else if (key == GLUT_KEY_UP)
			ph += 10;
		//  Down arrow key - decrease elevation by 5 degrees
		else if (key == GLUT_KEY_DOWN)
			ph -= 10;
		//  PageUp key - increase dim
		else if (key == GLUT_KEY_PAGE_DOWN)
			dim += 10;
		//  PageDown key - decrease dim
		else if (key == GLUT_KEY_PAGE_UP && dim > 1)
			dim -= 10;
		//  Keep angles to +/-360 degrees
		th %= 360;
		ph %= 360;
	//  Update projection 
	Project(mode ? fov : 0, asp, dim);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

void key(unsigned char ch, int x, int y) //(Code reuse from Ex 13 since key binding's were already positioned well)
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);
	//  Toggle lighting
	else if (ch == 'l')
		light = 1 - light;
	//  Toggle the walls
	else if (ch == 'y')
		wall_toggle = 1 - wall_toggle;
	//  Toggle light movement
	else if (ch == 'm')
		move = 1 - move;
	//  Light elevation
	else if (ch == '[')
		ylight -= 10;
	else if (ch == ']')
		ylight += 10;
	//  Reset view angle
	if (ch == '0'){
		th=57;
		ph=10;
	}
	//Switch display mode 
	else if (ch == 'p')
		mode = 1 - mode;
	//  Translate shininess power to value (-1 => 0)
	shiny = shininess < 0 ? 0 : pow(2.0, shininess);
	//  Reproject
	Project(mode ? fov : 0, asp, dim);
	//  Animate if requested
	glutIdleFunc(move ? idle : NULL);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

void reshape(int width, int height) //(reuse from past hw)
{
	//  Ratio of the width to the height of the window
	asp = (height > 0) ? (double)width / height : 1;
	//  Set the viewport to the entire window
	glViewport(0, 0, width, height);
	//  Set projection
	Project(mode ? fov : 0, asp, dim);
}
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(800,800);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Carlos Bueno Project");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK);
#endif
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user 
   glutIdleFunc(idle);
    //Load Textures 
	texture[0] = LoadTexBMP("leather.bmp");
	texture[1] = LoadTexBMP("chairwood.bmp");
	texture[2] = LoadTexBMP("fridge.bmp");
	texture[3] = LoadTexBMP("tv_back.bmp");
	texture[4] = LoadTexBMP("tv_glitch.bmp");
	texture[5] = LoadTexBMP("carpet.bmp");
	texture[6] = LoadTexBMP("wall.bmp");
	texture[7] = LoadTexBMP("pepsi.bmp");
	texture[8] = LoadTexBMP("topOfCan.bmp");
	texture[9] = LoadTexBMP("bottomOfCan.bmp");
   ErrCheck("init");
   glutMainLoop();
   return 0;
}