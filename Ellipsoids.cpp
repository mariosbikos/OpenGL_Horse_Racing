#include <stdio.h>     // - Just for some ASCII messages
#include <time.h>
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include <math.h>



void DrawCircle(float cx, float cy, float r, int num_segments) 
{ 
	float theta = 2 * 3.1415926 / float(num_segments); 
	float c = cos(theta);//precalculate the sine and cosine
	float s = sin(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_TRIANGLE_FAN); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}


void DrawCircleBorder(float cx, float cy, float r, int num_segments) 
{ 
	float theta = 2 * 3.1415926 / float(num_segments); 
	float c = cos(theta);//precalculate the sine and cosine
	float s = sin(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_STRIP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}


void DrawSemiCircleBorder(float cx, float cy, float r, int num_segments)
{
	float theta = 1 * 3.1415926 / float(num_segments); 
	float c = cos(theta);//precalculate the sine and cosine
	float s = sin(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_STRIP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}

void DrawSemiCircleFilled(float cx, float cy, float r, int num_segments)
{
	float theta = 1 * 3.1415926 / float(num_segments); 
	float c = cos(theta);//precalculate the sine and cosine
	float s = sin(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_TRIANGLE_FAN); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}

void DrawFilledEllipsoid(float width,float height)
{
	glPushMatrix();
		glPushMatrix();
		  glTranslatef(- ((width/2.0)-(height/2.0)) ,0.0,0.0);
		  //glRotatef(90.0,0.0,0.0,1.0);
		  DrawCircle(0.0, 0.0, height/2.0, 10000);
	  glPopMatrix();
	  glPushMatrix();
		  glTranslatef((width/2.0)-(height/2.0),0.0,0.0);
		  //glRotatef(-90.0,0.0,0.0,1.0);
		  DrawCircle(0.0, 0.0, height/2.0, 10000);
	  glPopMatrix();
  
	  glBegin(GL_TRIANGLE_FAN);
					glVertex2f(- ((width/2.0)-(height/2.0)),height/2.0);
					glVertex2f((width/2.0)-(height/2.0),height/2.0);
					glVertex2f((width/2.0)-(height/2.0),-height/2.0);
					glVertex2f(-(width/2.0)+(height/2.0),-height/2.0);
	  glEnd();
  glPopMatrix();
}


void DrawEllipsoidBorder(float width,float height)
{
	glPushMatrix();
	glPushMatrix();
	  glTranslatef(-(width/2.0)+(height/2.0) ,0.0,0.0);
	  glRotatef(90.0,0.0,0.0,1.0);
	  DrawSemiCircleBorder(0.0, 0.0, height/2.0, 10000);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef((width/2.0)-(height/2.0),0.0,0.0);
	  glRotatef(-90.0,0.0,0.0,1.0);
	  DrawSemiCircleBorder(0.0, 0.0, height/2.0, 10000);
  glPopMatrix();
  
  glBegin(GL_LINES);
				glVertex2f(-(width/2.0)+(height/2.0),height/2.0);
				glVertex2f((width/2.0)-(height/2.0),height/2.0);
				glVertex2f((width/2.0)-(height/2.0),-height/2.0);
				glVertex2f(-(width/2.0)+(height/2.0),-height/2.0);
  glEnd();

   glPopMatrix();
}



void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments) 
{ 
	float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	
	float x = r * cosf(start_angle);//we now start at the start angle
	float y = r * sinf(start_angle); 
    
	glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
	for(int ii = 0; ii < num_segments; ii++)
	{ 
		glVertex2f(x + cx, y + cy);

		float tx = -y; 
		float ty = x; 

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor; 
		y *= radial_factor; 
	} 
	glEnd(); 
}