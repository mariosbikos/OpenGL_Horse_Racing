#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include <math.h>
#include <time.h>       /* time */
#define PI (3.141592653589793)
#define GREEN_TRACK_WIDTH 15
#define GREEN_TRACK_HEIGHT 5
#define TRACK_WIDTH 25
#define TRACK_HEIGHT 12
#define SIMULATION_SPEED 0.01
#define DIFFERENT_HORSE_PERFORMANCES false

int randomNumber,randomHorse,randomSpeed;
float vsX[] = { 40,40,40,40 };
float TranslatesX[] = { 0,0,0,0 };
float angleSpeedPerHorse[]={700,650,600,550};
float radius=5;
float halfLength=10;
float horseLegsAngle;
float inc=20.0;
float horseBodyAngles[] = { 0,0,0,0 };
float totalDistances[] = { 0,0,0,0 };
float totalHorseBodyAngles[] = { 0,0,0,0 };
//float horseBodyRadius=3;
bool enableDifferentHorsePerformances=false;
//tut1
// angle of rotation for the camera direction
float angle=0.0;

//------------------------------------//
int cameraX=0,cameraZ=18;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
bool startFlag=false;

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
	else if(key==32)
		startFlag=true;

}

void processSpecialKeys(int key, int xx, int yy) {

	

	switch (key) {
		case GLUT_KEY_LEFT :
			cameraX-=2;
			break;
		case GLUT_KEY_RIGHT :
			cameraX+=2;
			break;
		case GLUT_KEY_UP :
			if (cameraZ-2>0)
			cameraZ-=1;
			break;
		case GLUT_KEY_DOWN :
			if (cameraZ+2>0)
			cameraZ+=1;
			break;
		case GLUT_KEY_F1:
			enableDifferentHorsePerformances=true;
	}
}


void DrawHorse(float radiusFromTrackCenter,int horseNo)
{
	glPushMatrix();
		glTranslatef((GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0),0,0); // metakino 2,5 aristera oste na pao sto kentro tou kuklou tou grasidiou pou orizo os aksona peristrofis

		//-Animation translations and rotations-//
		if (horseNo==1)
		{
			glTranslatef(- TranslatesX[0],0,0);
			glRotatef(horseBodyAngles[0],0,1,0);
		}
		else if (horseNo==2)
		{
			glTranslatef(- TranslatesX[1],0,0);
			glRotatef(horseBodyAngles[1],0,1,0);
		}
		else if (horseNo==3)
		{
			glTranslatef(- TranslatesX[2],0,0);
			glRotatef(horseBodyAngles[2],0,1,0);
		}
		else if (horseNo==4)
		{
			glTranslatef(- TranslatesX[3],0,0);
			glRotatef(horseBodyAngles[3],0,1,0);
		}
		//--//

		glPushMatrix();
			//move horse above Cube(ground) and radius away from center of track
			glTranslatef(0,1,-radiusFromTrackCenter);

			glPushMatrix();

				//scale down horse to fit track
				glScalef(0.2,0.2,0.2);
	
				//Horse Neck & Head
				glPushMatrix();
					glTranslatef(-3,1,0);
					glRotatef(-45.0,0.0,0.0,1.0);
					glPushMatrix();
						glScalef(1,0.5,0.5);
						glutSolidSphere(1,100,100);
					glPopMatrix();
					glTranslatef(-1,-1,0);
					glRotatef(90,0,0,1);
					glScalef(1.5,0.7,0.5);
					glutSolidSphere(1,100,100);
				glPopMatrix();
	
				//draw leg front left-brown
				glPushMatrix();
					glTranslatef(-0.5*3,-0.5*1,0);
					glRotatef(-horseLegsAngle,0,0,1);
					glScalef(1,3,0.5);
					glPushMatrix();
						glTranslatef(0,-0.5,1);
						glutSolidCube(1);
					glPopMatrix();
				glPopMatrix();
				//draw leg front right-red
	
				glPushMatrix();
					glTranslatef(-3*0.5,-0.5*1,0);
					glRotatef(-horseLegsAngle,0,0,1);
					glScalef(1,3,0.5);
					glPushMatrix();
						glTranslatef(0,-0.5,-1);
						glutSolidCube(1);
					glPopMatrix();
		
				glPopMatrix();

				//draw leg back left-blue
	
				glPushMatrix();
					glTranslatef(3*0.5,-0.5,0);
					glRotatef(horseLegsAngle,0,0,1);
					glScalef(1,3,0.5);
					glPushMatrix();
						glTranslatef(0,-0.5,1);
						glutSolidCube(1);
					glPopMatrix();
		
				glPopMatrix();

				//draw leg back right-green
	
				glPushMatrix();
					glTranslatef(3*0.5,-0.5,0);
					glRotatef(horseLegsAngle,0,0,1);
					glScalef(1,3,0.5);
					glPushMatrix();
						glTranslatef(0,-0.5,-1);
						glutSolidCube(1);
					glPopMatrix();
		
				glPopMatrix();

				//main body
				glPushMatrix();
					glScalef(3,1,1);
					glutSolidSphere(1,100,100);
				glPopMatrix();
			glPopMatrix();


	glPopMatrix();

	glPopMatrix();
	

}


void DrawMainCube(float width,float height)
{
	glPushMatrix();
		glColor3ub(2,166,17);
		glTranslatef(0.0,0.0,-2.7);
		glScalef(width,height,5.0);
		glutSolidCube(1.0);
	glPopMatrix();
}


void DrawTrack()
{
	glPushMatrix();
	
		//Draw main cube of track-green
		DrawMainCube(30,30);
		glPushMatrix();
			glTranslatef((GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0),GREEN_TRACK_HEIGHT/2,0);
			glColor3f(0.8,0.3,0.3);
			glScalef(0.1,1,1);
			glutSolidCube(1);
		glPopMatrix();
		//Draw Road
		glColor3ub(142,96,47);
		DrawFilledEllipsoid(25.0,12.0);

		//Draw Grass in the middle of the track
		glColor3ub(2,166,17);
		DrawFilledEllipsoid(15.0,5.0);

		//Draw inside border(white)
		glColor3f(1,1,1);
		glLineWidth(4.0);
		DrawEllipsoidBorder(15.0,5.0);

		//Draw outside border(white)
		glColor3f(1,1,1);
		glLineWidth(5.0);
		DrawEllipsoidBorder(25.0,12.0);
   glPopMatrix();
	//----------------------------------//
}

void drawSeats(int number)
{
	
	glPushMatrix();
		glTranslatef(0,0,-10);
		glScalef(18,5,2);
		glColor3ub(35,152,232);
		float j = 1;
		for ( int i = 0; i < number; i++ )
		{
			glPushMatrix();
				glTranslatef(0,0.25*i,-i);
				glScalef(1,j,1);
				glutSolidCube(1.0);
			glPopMatrix();
			j += 0.5;
		}
	glPopMatrix();

}

void Render()
{    
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	


   // Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	cameraX, 18.0f, cameraZ,
			0, 1.0f,  0,
			0.0f, 1.0f,  0.0f);

	axes();


//----DRAW SEATS OF STADIUM-------//
	glPushMatrix();
	    drawSeats(5);  //5 levels of seats
    glPopMatrix();
//-------------------------------//
   

//-----PISTA-------//
   glPushMatrix();
	   glRotatef(-90,1,0,0); //rotate 90 degrees to get correctly track
	   DrawTrack();
   glPopMatrix();


   //--Call DrawHorse function giving distance from center of track--//
   //4 horses
   if(startFlag==true)
   {
	   glColor3ub(85,56,26);	//brown horse color 
	   DrawHorse(3,1);
	   glColor3ub(133,68,2);	//brown horse color 
	   DrawHorse(3.8,2);
	   glColor3ub(130,64,40);	//brown horse color 
	   DrawHorse(4.6,3);
	   glColor3ub(199,198,193);
	   DrawHorse(5.4,4);
   }
//---------------------------------------------//
	

	glutSwapBuffers();
}

//-----------------------------------------------------------


void Idle()
{
	float dt = SIMULATION_SPEED;
	if (startFlag==true){
		//--Enable or Disable different horse performance-----------------------//
		if(enableDifferentHorsePerformances==true)
		{
			randomNumber = rand() % 10 + 1;
			randomHorse = rand() % 4 + 1;
			randomSpeed= rand() % 20 + 1;
			if (randomNumber==6)
			{
				vsX[randomHorse]+=randomSpeed;
			}
			else if (randomNumber==7)
			{
				if (vsX[randomHorse]>0 && vsX[randomHorse]-randomSpeed>10)
					vsX[randomHorse]-=randomSpeed;
			}
		}
		//-------------------------------------------------------------------//

		for(int i=0;i<4;i++)
		{
			//---Horse movement Animation---/
			if (totalDistances[i]<2*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) ))       //An vrisketai stin eutheia,tote mono metatopise kata x
			{
				TranslatesX[i]=TranslatesX[i]+vsX[i]*dt;
				totalDistances[i] = TranslatesX[i];
			}
			if (totalDistances[i]>=(2*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) )) && horseBodyAngles[i]<180 && totalDistances[i]<(4*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) )) ) //An exoun perasei 5 metra sunolika ksekina kukliki troxia
			{
				horseBodyAngles[i] = horseBodyAngles[i] + angleSpeedPerHorse[i]*dt;
				totalHorseBodyAngles[i]=horseBodyAngles[i];
			}
			if (totalDistances[i]>=(2*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) )) && horseBodyAngles[i]>=180 && totalDistances[i]<2*((2*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) ))))
			{
				TranslatesX[i]=TranslatesX[i]-vsX[i]*dt;
				if (TranslatesX[i]<=0)
				{
					totalDistances[i]=2*((2*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) )));
				}
			}
			if (totalDistances[i]>=(4*( (GREEN_TRACK_WIDTH/2.0)-(GREEN_TRACK_HEIGHT/2.0) )) && horseBodyAngles[i]>=180)
			{	
				horseBodyAngles[i] = horseBodyAngles[i] + angleSpeedPerHorse[i]*dt;
				if ( horseBodyAngles[i]>=360)
				{
					totalDistances[i]=0;
					totalHorseBodyAngles[i]=0;
					horseBodyAngles[i]=0;
				}
			}
		}
		//-----------------------------------------------------------------------------------//


		//--Horse Legs Animation--From -20 to 20 degrees--//
		if (horseLegsAngle>=20) 
			{
				horseLegsAngle = 20;
				inc = -inc;
			}
		if (horseLegsAngle<=-20) 
			{
				horseLegsAngle = -20;
				inc = -inc;
			}
		horseLegsAngle += inc;
		//----------------------------------------------//
	}
    glutPostRedisplay(); 
	
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ 
	// define the visible area of the window ( in pixels )
	if (h==0) h=1;
	glViewport(0,0,w,h); 

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	 
////(02b)
	          // L     R       B      T      N      F
	//glOrtho (-50.0f, 50.0f, -50.0f, 50.0f,-500.0f,500.0f);
	
	float aspect = (float)w/(float)h;             /// aspect ratio
	gluPerspective(80.0, aspect, 1.0, 500.0);
}


//-----------------------------------------------------------

void Setup()  
{ 
	srand (time(NULL));
   //glEnable( GL_CULL_FACE );

   glShadeModel( GL_FLAT );

   glEnable(GL_DEPTH_TEST);
   glDepthFunc( GL_LEQUAL );      
   glClearDepth(1.0); 		      


   //Set up light source
   GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat diffuseLight[] = { 0.6, 0.6, 0.6, 1.0 };
   GLfloat lightPos[] = { -20.0, 20.0, 150.0, 1.0 };

   glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
   glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
   glLightfv( GL_LIGHT0, GL_POSITION,lightPos );

 
	// polygon rendering mode and material properties
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
   
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	printf("PRESS F1 TO ENABLE DIFFERENT HORSE PERFORMANCES\n");
	printf("CHANGE CAMERA VIEW USING KEYBOARD ARROWS\n");
	printf("PRESS SPACEBAR TO START HORSE RACE \n");
}




                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              