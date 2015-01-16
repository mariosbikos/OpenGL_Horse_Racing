#include <stdio.h>     // - Just for some ASCII messages
#include <time.h>
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include <math.h>

void axes()
{
  glColor3f(0.9, 0.1, 0.1);
  glPushMatrix();
  glLineWidth(2);
  //glTranslatef(0, 0, -40.0);
  glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(40.0,0.0,0.0);
		glColor3f(0.1, 0.9, 0.1);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,40.0,0.0);
		glColor3f(0.1, 0.1, 0.9);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,-500.0);
		
  glEnd();
  glPopMatrix(); 
}