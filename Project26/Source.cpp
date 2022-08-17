#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "texture.h"
//#include <Sound.h>

#include <Camera.h>
#include<3DTexture.h>
#include<Model_3DS.h>
#include<fstream>
#include"heightMap.h"
#include"tgaLoader.h"
Camera MyCamera;
int mouseX = 0, mouseY = 0;
bool isClicked = 0, isRClicked = 0;
GLUquadricObj*obj=gluNewQuadric();
GLUquadricObj*obj1=gluNewQuadric();

GLfloat	z = -9.0f;
//Sound s1;

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Cntext
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default

// s1=Sound();
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 5000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


int box,slot,gray,power,mother,cylinder,powerbox,cubephoto,asus,gpu;
float a=0.0;
GLfloat LightPos[]={-500.0f,800.0f,-100.0f,0.0f};
GLfloat LightAmb[]={100.0f,100.0f,100.0f,1.0f};
GLfloat LightDiff[]={100.0f,100.0f,100.0f,1.0f};

Model_3DS* theAnt ;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{	
theAnt= new Model_3DS();
theAnt->Load ("Ant_3ds.3ds");

GLTexture AntColor;
AntColor.LoadBMP("Ant_color.bmp");
theAnt->Materials[1].tex=AntColor;
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1,GL_POSITION,LightPos);
	glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmb);
	
	glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiff);
	glEnable(GL_LIGHT1);


	MyCamera = Camera();
	MyCamera.Position.x =-990.0;
	MyCamera.Position.y = -980.0;
	MyCamera.Position.z = 300.0;
	MyCamera.RotateY(90.0);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Really Nice Perspective Calculations
	
	glEnable(GL_TEXTURE_2D);
	box = LoadTexture("box.bmp");
	slot = LoadTexture("slot.bmp");
	mother = LoadTexture("mother1.bmp");
	cylinder=LoadTexture("cylinder.bmp");
	gray=LoadTexture("gray1.bmp");
	power=LoadTexture("power.bmp");
	powerbox=LoadTexture("powerbox.bmp");
	asus=LoadTexture("asus.bmp");
	cubephoto=LoadTexture("cube.bmp");
	gpu=LoadTexture("gpu.bmp");
	
	gluQuadricTexture(obj,GL_TRUE);
	gluQuadricTexture(obj1,GL_TRUE);

	
	//s1.Sound("explosion.wav");

	return TRUE;										// Initialization Went OK
}
float NegPacx=-0.4;
float PosPacx=0.4;
float NegPacPacY=-0.4;
float PosPacPacY=0.4;


bool AreThereBlocks()
{
	
			bool BlockX = false;
	        bool BlockZ = false ;

			if(NegPacx<=2 && PosPacx>=2 )// if(
			BlockX= true;

			if (NegPacPacY<=0 && PosPacPacY>=0 )
			BlockZ=true;

		if(BlockX && BlockZ)
		{
			return true;
		}
		return false;
	}


void D_ANT(double x1,double y1,double z1){
	theAnt->pos.x =x1;
theAnt->pos.y= y1;
theAnt->pos.z= z1;
theAnt->Draw();
}




void mouse(int mouseX, int mouseY, bool isClicked, bool isRClicked)
{
	if (isClicked)
		MyCamera.RotateY(-0.2);
	if (isRClicked)
		MyCamera.RotateY(0.2);
}
float a1=0;
float a2=0;
float a3=0;
float a4=0;
float a5=0;
void keybord()
{
	
	if(keys['R'])
{
	a1-=1;
}
if(keys['F'])
{
	a2+=1;
	NegPacx+=0.1;
	PosPacx+=0.1;


}
if(keys['T'])
{
	a3-=1;
}
if(keys['G'])
{
	a4+=1;
	PosPacPacY+=0.1;
	NegPacPacY+=0.1;

}
if(keys['L'])
{
	a5-=1;
}
	if (keys['Q'])    		MyCamera.MoveUpward(1.0);
	if (keys['W'])			MyCamera.MoveUpward(-1.0);
	if (keys['A'])			MyCamera.RotateY(1);
	if (keys['S'])		    MyCamera.RotateY(-1);
	if (keys['Z'])		    MyCamera.RotateX(-0.1);
	if (keys['X'])		    MyCamera.RotateX(0.1);
	if (keys[VK_DOWN])        MyCamera.MoveForward(-1.0);
	if (keys[VK_UP])      MyCamera.MoveForward(1.0);
	if (keys[VK_LEFT])	    MyCamera.MoveRight(-1.0);
	if (keys[VK_RIGHT])		MyCamera.MoveRight(1.0);
}


void skybox()
{
//glColor3d(0.5,0.5,0.0);
	glBindTexture(GL_TEXTURE_2D, box);//back
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-1000, -1000, -1000);
	glTexCoord2d(1, 0);
	glVertex3d(1000, -1000, -1000);
	glTexCoord2d(1, 1);
	glVertex3d(1000, 1000, -1000);
	glTexCoord2d(0, 1);
	glVertex3d(-1000, 1000, -1000);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, box);//front
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-1000, -1000, 1000);
	glTexCoord2d(1, 0);
	glVertex3d(1000, -1000, 1000);
	glTexCoord2d(1, 1);
	glVertex3d(1000, 1000, 1000);
	glTexCoord2d(0, 1);
	glVertex3d(-1000, 1000, 1000 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, box);//left
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-1000, -1000, 1000 );
	glTexCoord2d(1, 0);
	glVertex3d(-1000, -1000, -1000 );
	glTexCoord2d(1, 1);
	glVertex3d(-1000, 1000, -1000 );
	glTexCoord2d(0, 1);
	glVertex3d(-1000, 1000, 1000 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, box);//right
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);
	glVertex3d(1000, -1000, 1000 );
	glTexCoord2d(0, 0);
	glVertex3d(1000, -1000, -1000);
	glTexCoord2d(0, 1);
	glVertex3d(1000, 1000, -1000);
	glTexCoord2d(1, 1);
	glVertex3d(1000, 1000, 1000);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, box);//top
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-1000, 1000, -1000);
	glTexCoord2d(1, 0);
	glVertex3d(1000, 1000, -1000);
	glTexCoord2d(1, 1);
	glVertex3d(1000, 1000, 1000);
	glTexCoord2d(0, 1);
	glVertex3d(-1000, 1000, 1000);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, box);//bottom
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1000.0f, -1000.0f, -1000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1000.0f, -1000.0f, -1000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glEnd();


}

void step2(){
	if(keys['H']){
		
		MyCamera = Camera();
		MyCamera.Position.x =2100.0;
	MyCamera.Position.y = -990.0;
	MyCamera.Position.z = -100.0;
	MyCamera.RotateY(90.0);
	}
	if(keys['P']){
		MyCamera = Camera();
		MyCamera.Position.x =0.0;
	MyCamera.Position.y = -980.0;
	MyCamera.Position.z = -2200.0;
	MyCamera.RotateY(90.0);
	
	}

}
float angle=0;
//void DrawCircle()
//{
//
//		glBegin(GL_TRIANGLES);
//	//Rotate and change rotate angle
//		glColor3d(0,0,0);
//
//	double x;
//	double y;
//	double xnext;
//	double ynext;
//	double step=0.1;
//	for(angle=0;angle<=(2*3.14);angle+=step)
//	{
//		x=cos(angle);
//		y=sin(angle);
//		glVertex3d(0,0,0);
//		glVertex3d(x,y,0);
//		xnext=cos(angle+step);
//		ynext=sin(angle+step);
//		glVertex3d(xnext,ynext,0);
//	}
//	 glEnd();
//}
	double x5;
	double y5;
	double xnext;
	double ynext;
	double step=0.1;
void pac_Man()
{
	glBegin(GL_TRIANGLES);
	glColor3ub(170,170,0);
		for(angle=0.4;angle<=(2*3.14-(step*4));angle+=step)
	{

		x5=cos(angle);
		y5=sin(angle);
		glVertex3d(0,0,0);
		glVertex3d(x5,y5,0);
		xnext=cos(angle+step);
		ynext=sin(angle+step);
		glVertex3d(xnext,ynext,0);

	}
	 glEnd();

	
	
}


void mother_board(){
glBindTexture(GL_TEXTURE_2D,mother);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-500.0f, -1000.2f, -1000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1000.0f, -1000.2f, -1000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, -1000.2f, 1000.0f);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-500.0f, -1000.2f, 1000.0f);

	glEnd();
	//cpu ant
	glPushMatrix();
	glTranslated(100,-990,-300);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(200,-990,-400);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(200,-990,-200);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();

	//mother ant
	glPushMatrix();
	if(AreThereBlocks()==false){
	glTranslated(200,-990,-700);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();
	}
	
	glPushMatrix();
	glTranslated(-70,-990,-750);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(-70,-990,750);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();
//gpu
	glPushMatrix();
	glTranslated(-970,30,-300);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-970,-190,350);
	glRotated(-90,0,0,1);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();
	
}

GLfloat pi=3.1415926535898;
void Draw_Circle (int r=0){
  GLfloat i=0, a ,c ;
	for(i = 0; i<=(2*pi) ; i+=0.01)
	{
		a=cos(i)*r;
		c=sin(i)*r;
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0,0,0);
		glVertex3f(0,0,4);
        glVertex3f(a,c,4);
        glEnd();
	 } 
  }

void Draw_Circle_filled (int r=0){
  GLfloat i=0, a ,c ;
	for(i = 0; i<=(2*pi) ; i+=0.01)
	{
		a=cos(i)*r;
		c=sin(i)*r;
	
		glBegin(GL_LINES);
		glColor3f(0,0,0);
         glVertex3f(0,0,4.1);
        glVertex3f(a,c,4.1);
        glEnd();
	 } 
  }

void Draw_Quads(GLfloat x,GLfloat y,GLfloat z,GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2){
	
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(x,y,z);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glEnd();

}

void Draw_fan (){
   // s1.Play();
	//s1.Stop();
	
	Draw_Circle(4);
	Draw_Circle_filled(1.9);
		
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	glVertex3f(-4,-4,4);
    glVertex3f(4,-4,4);
	glVertex3f(4,4,4);
	glVertex3f(-4,4,4);
	glVertex3f(-4,-4,4);
	glEnd();

	glRotated(a,0,0,1);
	Draw_Quads(0,0,4,3.7,-1,4,3.7,1,4);
	
	glPushMatrix();
	glRotated(60,0,0,1);
	Draw_Quads(0,0,4,3.7,-1,4,3.7,1,4);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(120,0,0,1);
	Draw_Quads(0,0,4,3.7,-1,4,3.7,1,4);
	glPopMatrix();
		
	glRotated(a,0,0,1);
	
	glPushMatrix();
	glRotated(-120,0,0,1);
	Draw_Quads(0,0,4,3.7,-1,4,3.7,1,4);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-60,0,0,1);
	Draw_Quads(0,0,4,3.7,-1,4,3.7,1,4);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(180,0,0,1);
	Draw_Quads(0,0,4,3.7,-1,4,3.7,1,4);
	glPopMatrix();
   
	a+=5;

}

void GPU(){
	
	//front
	glBindTexture(GL_TEXTURE_2D,gray);
	//glColor3f(1,1,0);
	glBegin(GL_QUADS);	
	glTexCoord2f(0,0);
	glVertex3f(-12.0f, -4.0f, 4.0f); 
	glTexCoord2f(1,0);
	glVertex3f(12.0f, -4.0f, 4.0f);
	glTexCoord2f(1,1);
	glVertex3f(12.0f, 4.0f, 4.0f);
	glTexCoord2f(0,1);
	glVertex3f(-12.0f, 4.0f, 4.0f);
	glEnd();
	
	glPushMatrix();
	Draw_fan();
	glPopMatrix();

	glPushMatrix();
	glTranslated(8,0,0);
	Draw_fan();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-8,0,0);
	Draw_fan();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,gpu);
	glBegin(GL_QUADS);	
	glTexCoord2f(0,0);
	glVertex3f(-12.0f, -4.0f, 1.5f); 
	glTexCoord2f(1,0);
	glVertex3f(12.0f, -4.0f, 1.5f);
	glTexCoord2f(1,1);
	glVertex3f(12.0f, 4.0f, 1.5f);
	glTexCoord2f(0,1);
	glVertex3f(-12.0f, 4.0f, 1.5f);
	glEnd();
	glPopMatrix();

	//back
	glPushMatrix();
	glTranslated(0,0,-3);
	glBindTexture(GL_TEXTURE_2D,gray);
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_QUADS);	
	glTexCoord2f(0,0);
	glVertex3f(-12.0f, -4.0f, 4.0f); 
	glTexCoord2f(1,0);
	glVertex3f(12.0f, -4.0f, 4.0f);
	glTexCoord2f(1,1);
	glVertex3f(12.0f, 4.0f, 4.0f);
	glTexCoord2f(0,1);
	glVertex3f(-12.0f, 4.0f, 4.0f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0,0,-3.1);
	Draw_fan();
	glPopMatrix();

	glPushMatrix();
	glTranslated(8,0,-3.1);
	Draw_fan();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-8,0,-3.1);
	Draw_fan();
	glPopMatrix();

	//right
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS); 
	glTexCoord2f(1,1);
	glVertex3f(12.0f, 4.0f, 4.0f);
	glTexCoord2f(0,1);
	glVertex3f(12.0f, 4.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(12.0f, -4.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(12.0f, -4.0f, 4.0f);
	glEnd();

	glPopMatrix();

	//left
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS);	
	glTexCoord2f(0,1);
	glVertex3f(-12.0f, 4.0f, 1.0f); 
	glTexCoord2f(1,1);
	glVertex3f(-12.0f, 4.0f, 4.0f);
	glTexCoord2f(1,0);
	glVertex3f(-12.0f, -4.0f, 4.0f);
	glTexCoord2f(0,0);
	glVertex3f(-12.0f, -4.0f, 1.0f);
	glPopMatrix();
	glEnd();

	//top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS); 
	glTexCoord2f(1,1);
	glVertex3f(12.0f, 4.0f, 1.0f); 
	glTexCoord2f(0,1);
	glVertex3f(-12.0f, 4.0f, 1.0f);
	glTexCoord2f(0,0);	
	glVertex3f(-12.0f, 4.0f, 4.0f);
    glTexCoord2f(1,0);	
	glVertex3f(12.0f, 4.0f, 4.0f);
	glEnd();
	glPopMatrix();

	//Bottom
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex3f(12.0f, -4.0f, 4.0f); 
	glTexCoord2f(0,0);
	glVertex3f(-12.0f, -4.0f, 4.0f);
	glTexCoord2f(0,1);
	glVertex3f(-12.0f, -4.0f, 1.0f);
	glTexCoord2f(1,1);
	glVertex3f(12.0f, -4.0f, 1.0f);
	glEnd();
	glPopMatrix();

}

void Draw_transistor(){

	glBindTexture(GL_TEXTURE_2D,cylinder);
	glRotated(90,1,0,0);
	//glColor3f(0.8,0.8,0.8);
	Draw_Circle_filled(20);
	gluCylinder(obj,20,20,50,30,30);
   

}
void Ram()
{
	glScalef(1, 2, 2);
	//glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D,slot);
	glBegin(GL_QUADS); // Draw The Cube Using quads

	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f); //   (Top)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f); // (front)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, -1.0f); // (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f); //  (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f); // (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
}

void cube (){
    glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS); // Draw The Cube Using quads

	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f); //   (Top)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(1,1);
	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, 1.0f); // (front)
	glTexCoord2f(0,0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1,1);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, -1.0f); // (Back)
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(1,1);
	glVertex3f(-1.0f, 1.0f, 1.0f); //  (Left)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(-1.0f, -1.0f, 1.0f);


	glTexCoord2f(0,1);
	glVertex3f(1.0f, 1.0f, -1.0f); // (Right)
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();

}
void powercube (){
    glBindTexture(GL_TEXTURE_2D,asus);
	glBegin(GL_QUADS); // Draw The Cube Using quads

	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f); //   (Top)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(1,1);
	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, 1.0f); // (front)
	glTexCoord2f(0,0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1,1);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, -1.0f); // (Back)
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(1,1);
	glVertex3f(-1.0f, 1.0f, 1.0f); //  (Left)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(-1.0f, -1.0f, 1.0f);


	glTexCoord2f(0,1);
	glVertex3f(1.0f, 1.0f, -1.0f); // (Right)
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();

}

void north_bridge (){
    glBindTexture(GL_TEXTURE_2D,asus);
	glBegin(GL_QUADS); // Draw The Cube Using quads

	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f); //   (Top)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f); // (front)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, -1.0f); // (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f); //  (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f); // (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();

}


void cubeViaSquads()
{
	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS); //(Top)
	glTexCoord2f(1,1);
	glVertex3f(4.0f, 4.0f, -4.0f); 
	glTexCoord2f(0,1);
	glVertex3f(-4.0f, 4.0f, -4.0f);
	glTexCoord2f(0,0);	
	glVertex3f(-4.0f, 4.0f, 4.0f);
	glTexCoord2f(1,0);	
	glVertex3f(4.0f, 4.0f, 4.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS);// (Bottom)
	glTexCoord2f(1,0);
	glVertex3f(4.0f, -4.0f, 4.0f); 
	glTexCoord2f(0,0);
	glVertex3f(-4.0f, -4.0f, 4.0f);
	glTexCoord2f(0,1);
	glVertex3f(-4.0f, -4.0f, -4.0f);
	glTexCoord2f(1,1);
	glVertex3f(4.0f, -4.0f, -4.0f);
	glEnd();

	glPushMatrix();// (front)
	glColor3f(1,1,1);
	Draw_fan();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS); //  (Left)
	glTexCoord2f(1,1);
	glVertex3f(-4.0f, 4.0f, 4.0f);
	glTexCoord2f(0,1);
	glVertex3f(-4.0f, 4.0f, -4.0f);
	glTexCoord2f(0,0);
	glVertex3f(-4.0f, -4.0f, -4.0f);
	glTexCoord2f(1,0);
	glVertex3f(-4.0f, -4.0f, 4.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,gray);
	glBegin(GL_QUADS);	// (Right)
	glTexCoord2f(0,1);
	glVertex3f(4.0f, 4.0f, -4.0f); 
	glTexCoord2f(1,1);
	glVertex3f(4.0f, 4.0f, 4.0f);
	glTexCoord2f(1,0);
	glVertex3f(4.0f, -4.0f, 4.0f);
	glTexCoord2f(0,0);
	glVertex3f(4.0f, -4.0f, -4.0f);

	glEnd();
}

int y; 
void Circle(float r)
{
	double i,z,x,y;
	glBegin(GL_LINE_STRIP);
	for(i=0;i<=2*(3.14)*r;i+=0.1)
		{
			glColor3f(0.5,0.5,0.5);
			x=r*sin(i);
		    y=r*cos(i);	
		  glVertex3d(x,y,0);
			  
		}
		   glEnd();
}
void Circle2(float r)
{
	double i,z,x;
	glBegin(GL_LINES);
		for(i=0;i<=2*(3.14)*r;i+=0.1)
		{
			glColor3f(0.5,0.5,0.5);
			x=r*sin(i);
		    y=r*cos(i);
			 glVertex3d(0,0,0);
		     glVertex3d(x,y,0);
			  

		}
		   glEnd();
}

void miniskybox()
{
    // glColor3ub(250,15,0);
	glBindTexture(GL_TEXTURE_2D, powerbox);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-500, -500, -500);
	glTexCoord2d(1, 0);
	glVertex3d(0, -500,- 500);
	glTexCoord2d(1, 1);
	glVertex3d(0, 0, -500);
	glTexCoord2d(0, 1);
	glVertex3d(-500, 0, -500);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, powerbox);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-500, -500, 0);
	glTexCoord2d(1, 0);
	glVertex3d(0, -500, 0);
	glTexCoord2d(1, 1);
	glVertex3d(0, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3d(-500, 0, 0 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, powerbox);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-500, -500, 0);
	glTexCoord2d(1, 0);
	glVertex3d(-500,-500, -500 );
	glTexCoord2d(1, 1);
	glVertex3d(-500, 0,-500 );
	glTexCoord2d(0, 1);
	glVertex3d(-500, 0, 0 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, powerbox);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0);
	glVertex3d(0, -500, 0 );
	glTexCoord2d(0, 0);
	glVertex3d(0, -500, -500);
	glTexCoord2d(0, 1);
	glVertex3d(0, 0, -500);
	glTexCoord2d(1, 1);
	glVertex3d(0, 0, 0);
	glEnd();

	glPushMatrix();// (top)
	glTranslated(-250,240,-250);
	glScalef(60,60,60);
    glRotated(90,1,0,0);
	Draw_fan();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-250,0,-250);
    glScalef(80,80,80);
    glRotated(90,1,0,0);
	glLineWidth(1);
    Circle(2);
    Circle2(3.5);
    Circle(1.5);
    Circle(2.5);
    Circle(1);

	glPopMatrix();

	/*glBindTexture(GL_TEXTURE_2D, powerbox);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-500, 0,- 500);
	glTexCoord2d(1, 0);
	glVertex3d(0, 0, -500);
	glTexCoord2d(1, 1);
	glVertex3d(0, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3d(-500, 0, 0);
	glEnd();*/
	
	glBindTexture(GL_TEXTURE_2D, power);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-500.0f, -500.0f,-500.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, -500.0f, -500.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, -500.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(-500.0f,-500.0f, 0.0f);
	glEnd();
}


 
// åÏÇ ÇáßíæÈ ÇáãÓÊØíá
void Rectangle(){
	glBindTexture(GL_TEXTURE_2D,cubephoto);
	glBegin(GL_QUADS); // Draw The Cube Using quads
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f); //   (Top)
	glTexCoord2f(0,1);
	glVertex3f(-3.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);	
	glVertex3f(-3.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glTexCoord2f(0,0);
    glVertex3f(-3.0f, -1.0f, 1.0f);
	glTexCoord2f(0,1);
    glVertex3f(-3.0f, -1.0f, -1.0f);
	glTexCoord2f(1,1);
    glVertex3f(1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(0,1);
	glVertex3f(-3.0f, 1.0f, 1.0f); // (front)
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-3.0f, -1.0f, 1.0f);

	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, -1.0f); // (Back)
	glTexCoord2f(0,0);
	glVertex3f(-3.0f, -1.0f, -1.0f);
    glTexCoord2f(0,1);
	glVertex3f(-3.0f, 1.0f, -1.0f);
	glTexCoord2f(1,1);
	glVertex3f(1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(1,1);
	glVertex3f(-3.0f, 1.0f, 1.0f); //  (Left)
	glTexCoord2f(0,1);
	glVertex3f(-3.0f, 1.0f, -1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-3.0f, -1.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(-3.0f, -1.0f, 1.0f);

	glTexCoord2f(0,1);
	glVertex3f(1.0f, 1.0f, -1.0f); // (Right)
	glTexCoord2f(0,0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1,1);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
}

//åÏÇ Çááí ÈíÄÓã ÇáÓßß Çááí ãÊá ÇáãÓÊØíáÇÊ
void cc()
{
	
  glScalef(30, 50, 10);
  Rectangle();

  glTranslated(0.9,1.3,0);
  glScalef(0.1, 0.3, 0.1);
  Rectangle();
 
  glTranslated(-6,0,0);
  Rectangle();
  
  glTranslated(-7,0,-0.3);
  Rectangle();

  glTranslated(-8,0,-0.3);
  Rectangle();

  glTranslated(-8.8,0,-0.3);
  Rectangle();
 
  glTranslated(-6,0,-0.3);
  Rectangle();

}

//åÏæá ÊÈÚÇÊ ÇáÔÈßå

void Draw_columes(GLint x,GLint y,GLint z,GLint x1,GLint y1, GLint z1){
	glLineWidth(5);
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3f(x,y,z);
	glVertex3f(x1,y1,z1);
	glEnd();

}
int x=0;
void cpu(){
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D,asus);
	glBegin(GL_QUADS);
    glTexCoord2f(1,1);
	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glTexCoord2f(0,1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0,0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1,0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.5,0.5,0);
glLineWidth(3);
for(float i=-1 ;i<=1;i+=0.1)
{   
for(float j=0 ;j<=2.1;j+=0.1)
{	

	glPushMatrix();
	glTranslated(0,0,j);
	glBegin(GL_LINES);
    glPushMatrix();
    glVertex3d(i,-1,-1);
    glVertex3d(i,-0.9,-1);	 
    glPopMatrix();	 
    glEnd();
	glPopMatrix();
}
}

}
void supply(){
    miniskybox();
	
	glPushMatrix();
	glTranslated(-300,-450,-100);
	cc();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-300,-450,-300);
	cc();
	glPopMatrix();
	
	//cylinder
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,cylinder);
	glTranslated(-300,-440,-400);
    glScalef(5, 40, 10);
    glRotated(90,1,0,0);
    gluCylinder(obj,3,3,1.5,30,30);
    glPopMatrix();

   glPushMatrix();
   glTranslated(-200,-440,-400);
   glScalef(5, 40, 10);
   glRotated(90,1,0,0);
   gluCylinder(obj,2,2,1.5,30,30);
   glPopMatrix();

   glPushMatrix();
   glTranslated(-150,-440,-400);
   glScalef(5, 40, 10);
   glRotated(90,1,0,0);
   gluCylinder(obj,2,2,1.5,30,30);
   glPopMatrix();

  glPushMatrix();//done
  glTranslated(-170,-470,-350);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,2,2,1.5,30,30);
  glPopMatrix();

  glPushMatrix();//done
  glTranslated(-140,-470,-350);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,2,2,1.5,30,30);
  glPopMatrix();

  glPushMatrix();//done
  glTranslated(-100,-470,-350);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,2,2,1.5,30,30);
  glPopMatrix();
  //ßÇÈáÇÊ
  glPushMatrix();
  glTranslated(-300,-400,-40);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,1.5,1.5,5,30,30);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-340,-440,-250);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,1.5,1.5,3,30,30);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-340,-440,-160);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,1.5,1.5,3,30,30);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-450,-440,-160);
  glScalef(5, 20, 10);
  glRotated(90,1,0,0);
  gluCylinder(obj,1.5,1.5,3,30,30);
  glPopMatrix();


  //powercube
  glPushMatrix();
  glTranslated(-200,-490,-200);
  glScalef(25, 15, 20);
  powercube();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-150,-490,-80);
  glScalef(20, 10, 20);
  powercube();
  glPopMatrix();

  
  glPushMatrix();
  glTranslated(-460,-490,-460);
  glScalef(20, 10, 20);
  powercube();
  glPopMatrix();

  //power supply ant
	glPushMatrix();
	glTranslated(-460,-470,-460);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-150,-470,-80);
	glScaled(0.02,0.02,0.02);
	D_ANT(1,0,5);
	glPopMatrix();


}
bool CheckCollisom()
{
	if(a2==-700 && a4==-990)
	{
		return true;
	}
	return false;
}
int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
		

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glPushMatrix();
	glTranslated(2,0,-5);
	glScaled(0.0002,0.0002,0.0002);
	//glColor3d(1,1,1);

	//glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,-1);
	glColor3f(1,1,1);
	glPopMatrix();
	glTranslated(0, 0, -3);
	MyCamera.Render();
	keybord();
	mouse(mouseX, mouseY, isClicked, isRClicked);
	skybox();
	mother_board();



	//CPU_FAN
	glPushMatrix();
	glTranslated(200,-990,-300);
    glRotated(-90,1,0,0);
	glScaled(40,60,4);
	cubeViaSquads();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(200,-920,-300);
	glScaled(80,70,80);
	cpu();
    glPopMatrix();	

	glPopMatrix(); //don't remove this ever ever


	
	//GPU
	glPushMatrix();
	glTranslated(-990,-190,-300);
    glRotated(-90,0,1,0);
    glRotated(180,0,1,0);
    glScaled(50,50,8);
	GPU();
	glPopMatrix();

	glPopMatrix(); //dont remove this ever ever
	
	//ram 
	glPushMatrix();
	glTranslated(830,-990,-380);
    glRotated(-90,0,1,0);
	glScaled(580,5,15);
	Ram();
	glPopMatrix();


    glPushMatrix();
	glTranslated(750,-990,-380);
    glRotated(-90,0,1,0);
	glScaled(580,5,15);
	Ram();
	glPopMatrix();

	glPushMatrix();
	glTranslated(670,-990,-380);
    glRotated(-90,0,1,0);
	glScaled(580,5,15);
	Ram();
	glPopMatrix();

	glPushMatrix();
	glTranslated(590,-990,-380);
    glRotated(-90,0,1,0);
	glScaled(580,5,15);
	Ram();
	glPopMatrix();


	glPushMatrix();
	glTranslated(200,-990,350);
	glScaled(400,5,15);
	Ram();
	glPopMatrix();

    glPushMatrix();
	glTranslated(-100,-990,520);
	glScaled(80,5,20);
	Ram();
	glPopMatrix();

    glPushMatrix();
	glTranslated(-100,-990,670);
	glScaled(80,5,20);
	Ram();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-100,-990,820);
	glScaled(80,5,20);
	Ram();
	glPopMatrix();


	//transistor

	glPushMatrix();
	glTranslated(890,-950,-800);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(890,-950,-400);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(890,-950,-450);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(150,-950,180);
	glRotated(90,1,0,0);
	glColor3f(0.8,0.8,0.8);
	Draw_Circle_filled(90);
	gluCylinder(obj,90,90,50,30,30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-200,-950,80);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-200,-950,10);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-170,-950,410);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-280,-950,-680);
	Draw_transistor();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-280,-950,-340);
	Draw_transistor();
	glPopMatrix();


	//north bridge
	glPushMatrix();
	glTranslated(500,-990,650);
	glScaled(150,20,150);
	north_bridge();
	glPopMatrix();

	//cube
	glPushMatrix();
	glTranslated(-130,-990,-170);
	glScaled(30,10,40);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-130,-990,-330);
	glScaled(30,10,40);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-130,-990,-490);
	glScaled(30,10,40);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-130,-990,-770);
	glScaled(30,10,40);
	cube();
	glPopMatrix();
	
	//power supply
	glPushMatrix();	
    glTranslated(-500,-500,+1000);
    supply();
	glPopMatrix();

	glPushMatrix();
	  	glTranslated(a1,0,0);
	glTranslated(a2,0,0);
    glTranslated(0,a3,0);
	glTranslated(0,a4,0);
	 glTranslated(-500,-970,-500);
	 glScaled(20,20,20);
	 pac_Man();
	
	 glPopMatrix();
	
	return TRUE;
	
	
	

	
}
LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	case WM_MOUSEMOVE:
	{
						 mouseX = (int)LOWORD(lParam);
						 mouseY = (int)HIWORD(lParam);
						 isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
						 isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
						 break;
	}
	case WM_LBUTTONUP:
		isClicked = false; 	 break;
	case WM_RBUTTONUP:
		isRClicked = false;   break;
	case WM_LBUTTONDOWN:
		isClicked = true; 	break;
	case WM_RBUTTONDOWN:
		isRClicked = true;	break;

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
