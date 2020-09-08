//  ========================================================================
//  COSC363: Computer Graphics (2020); CSSE  University of Canterbury.
//
//  FILE NAME: Yard.cpp
//  See Lab03.pdf for details.
//  ========================================================================

#include <iostream>
#include <cmath>
//~ #include <OpenGL/gl.h>
//~ #include <OpenGL/glu.h>
//~ #include <GLUT/glut.h>
#include <GL/freeglut.h>
#include "loadTGA.h"
#include "loadBMP.h"

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F

GLuint txId[10];   //Texture ids
float angle=0, look_x, look_z=-1, cam_hgt=30, eye_x, eye_z=700;  //Camera parameters

float museumHeight=150, museumOuter=200, museumInner=195, doorWidth=30, doorHeight=75;
int roofHeight=300;
float theta = 0;
GLUquadric *q;    //Required for creating cylindrical objects
float ballX = -18;
float ballY = 13;
double shaftRotation = -20;
int catapultFiring=0;
int reverseRotation = 0;

//Pivot vertices
float vx[11] = {-8, -6, -4, -2, 0, 2, 4, 6, 8, 10}; float wx[11] = {-8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
float vy[11] = {0, 2, 4, 6, 8, 6, 4, 2, 0, -2}; float wy[11] = {0, 2, 4, 6, 8, 6, 4, 2, 0, -2};
float vz[11] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; float wz[11] = {-3, -3, -3, -3, -3, -3, -3, -3, -3, -3};

float px[11] = {-8, -6, -4, -2, 0, 2, 4, 6, 8, 10}; float qx[11] = {-8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
float py[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; float qy[11] = {0, 2, 4, 6, 8, 6, 4, 2, 0, -2};
float pz[11] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; float qz[11] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

float sx[11] = {-8, -6, -4, -2, 0, 2, 4, 6, 8, 10}; float tx[11] = {-8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
float sy[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; float ty[11] = {0, 2, 4, 6, 8, 6, 4, 2, 0, -2};
float sz[11] = {-3, -3, -3, -3, -3, -3, -3, -3, -3, -3}; float tz[11] = {-3, -3, -3, -3, -3, -3, -3, -3, -3, -3};

double seesawRotation=15.466, b1X=27, b1Y, b2X=-27, b2Y=4;
int b1=1, b2=0, b1OnWayDown=1, b2OnWayDown=0;

float lgt_pos1[] = {0., 100,  0., 0.0f};

using namespace std;

//--------------------------------------------------------------------------------
void loadTexture()
{
    glGenTextures(10, txId);     // Create 10 texture ids

    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("textures/left.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("textures/back.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("textures/right.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
    loadTGA("textures/front.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture
    loadTGA("textures/up.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
    loadTGA("textures/down.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[6]);  //Use this texture
    loadTGA("textures/roof.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, txId[7]);  //Use this texture
    loadTGA("textures/museumOuter.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, txId[8]);  //Use this texture
    loadTGA("textures/door.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, txId[9]);      //Use this texture
    loadBMP("textures/fern.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

//-------------------------------------------------------------------------------

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
              float x3, float y3, float z3 )
{
      float nx, ny, nz;
      nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
      ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
      nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

      glNormal3f(nx, ny, nz);
}

//--------------------------------------------------------------------------------

bool isInside(int x1, int z1, int x2, int z2, int x, int z)
{
    if (x > x1 and x < x2 and z > z1 and z < z2) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------

void special(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
    else if(key == GLUT_KEY_RIGHT) angle += 0.1;
    else if(key == GLUT_KEY_DOWN)
    {  //Move backward
        int temp_x = eye_x - 5*sin(angle);
        int temp_z = eye_z + 5*sin(angle);

        if (!(isInside(-120, 70, -75, 180, temp_x, temp_z))) {
            eye_x -= 5*sin(angle);
            eye_z += 5*cos(angle);
        }
    }
    else if(key == GLUT_KEY_UP)
    {   //Move forward

        int temp_x = eye_x + 5*sin(angle);
        int temp_z = eye_z - 5*cos(angle);

        if (!(isInside(-120, 70, -75, 180, temp_x, temp_z))) {
            eye_x += 5*sin(angle);
            eye_z -= 5*cos(angle);
        }
    }

    look_x = eye_x + 100*sin(angle);
    look_z = eye_z - 100*cos(angle);

    glutPostRedisplay();

}

//--------------------------------------------------------------------------------

void initialise()
{
    //loadTexture();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glClearColor(0., 1., 1., 1.);    //Background colour
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float red[4] = {1.0, 0.0, 0.0, 1.0};

    q = gluNewQuadric();

    glEnable(GL_LIGHTING);                  //Enable OpenGL states

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    glDisable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, red);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.01);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    glDisable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------------------------

void skybox()
{
    glEnable(GL_TEXTURE_2D);

    ////////////////////// BACK WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(-1000, 500, -1000);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-1000, -500, -1000);
        glTexCoord2f(1.0, 0.0);  glVertex3f(1000, -500, -1000);
        glTexCoord2f(1.0, 1.0);  glVertex3f(1000, 500, -1000);
    glEnd();

    ////////////////////// FRONT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(1000, 500, 1000);
        glTexCoord2f(0.0, 0.0);   glVertex3f(1000, -500, 1000);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-1000, -500, 1000);
        glTexCoord2f(1.0, 1.0);   glVertex3f(-1000, 500, 1000);
    glEnd();

    ////////////////////// LEFT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(-1000, 500, 1000);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-1000, -500, 1000);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-1000, -500, -1000);
        glTexCoord2f(1.0, 1.0);   glVertex3f(-1000, 500, -1000);
    glEnd();

    ////////////////////// RIGHT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(1000, 500, -1000);
        glTexCoord2f(0.0, 0.0);   glVertex3f(1000, -500, -1000);
        glTexCoord2f(1.0, 0.0);   glVertex3f(1000, -500, 1000);
        glTexCoord2f(1.0, 1.0);   glVertex3f(1000, 500, 1000);
    glEnd();

    ////////////////////// TOP WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);   glVertex3f(1000, 500, -1000);
        glTexCoord2f(0.0, 1.0);   glVertex3f(-1000, 500, -1000);
        glTexCoord2f(1.0, 1.0);  glVertex3f(-1000, 500, 1000);
        glTexCoord2f(1.0, 0.0);  glVertex3f(1000, 500, 1000);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------------------------

void floor()
{
    float white[4] = {1., 1., 1., 1.};
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[5]);
    glBegin(GL_QUADS);
         glTexCoord2f(0.0, 1.0);   glVertex3f(-1000, -0.01, -1000);
         glTexCoord2f(0.0, 0.0);   glVertex3f(-1000, -0.01, 1000);
         glTexCoord2f(1.0, 0.0);   glVertex3f(1000, -0.01, 1000);
         glTexCoord2f(1.0, 1.0);   glVertex3f(1000, -0.01, -1000);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor4f(0.99, 0.99, 0.99, 1.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glBegin(GL_QUADS);
    for(int i = -200; i < 200; i++)
    {
        for(int j = -200;  j < 200; j++)
        {
            glVertex3f(i, 0.01, j);
            glVertex3f(i, 0.01, j+1);
            glVertex3f(i+1, 0.01, j+1);
            glVertex3f(i+1, 0.01, j);
        }
    }
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glEnd();

}

//--------------------------------------------------------------------------------

void museumWalls() //TODO textures
{
    glBegin(GL_QUADS);
        //BACK OUTER
        glTexCoord2f(0.0, 2.0);   glVertex3f(-museumOuter, museumHeight, -museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter, 0, -museumOuter);
        glTexCoord2f(20.0, 0.0);  glVertex3f(museumOuter, 0, -museumOuter);
        glTexCoord2f(20.0, 2.0);  glVertex3f(museumOuter, museumHeight, -museumOuter);

        //BACK INNER
        glTexCoord2f(0.0, 2.0);   glVertex3f(-museumInner, museumHeight, -museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumInner, 0, -museumInner);
        glTexCoord2f(20.0, 0.0);  glVertex3f(museumInner, 0, -museumInner);
        glTexCoord2f(20.0, 2.0);  glVertex3f(museumInner, museumHeight, -museumInner);

        //LEFT OUTER
        glTexCoord2f(0.0, 2.0);   glVertex3f(-museumOuter, museumHeight, museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter, 0, museumOuter);
        glTexCoord2f(20.0, 0.0);   glVertex3f(-museumOuter, 0, -museumOuter);
        glTexCoord2f(20.0, 2.0);   glVertex3f(-museumOuter, museumHeight, -museumOuter);

        //LEFT INNER
        glTexCoord2f(0.0, 2.0);   glVertex3f(-museumInner, museumHeight, museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumInner, 0, museumInner);
        glTexCoord2f(20.0, 0.0);   glVertex3f(-museumInner, 0, -museumInner);
        glTexCoord2f(20.0, 2.0);   glVertex3f(-museumInner, museumHeight, -museumInner);

        //RIGHT OUTER
        glTexCoord2f(0.0, 2.0);   glVertex3f(museumOuter, museumHeight, -museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(museumOuter, 0, -museumOuter);
        glTexCoord2f(20.0, 0.0);   glVertex3f(museumOuter, 0, museumOuter);
        glTexCoord2f(20.0, 2.0);   glVertex3f(museumOuter, museumHeight, museumOuter);

        //RIGHT INNER
        glTexCoord2f(0.0, 2.0);   glVertex3f(museumInner, museumHeight, -museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(museumInner, 0, -museumInner);
        glTexCoord2f(20.0, 0.0);   glVertex3f(museumInner, 0, museumInner);
        glTexCoord2f(20.0, 2.0);   glVertex3f(museumInner, museumHeight, museumInner);

        //FRONT OUTER TOP
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumOuter, museumHeight, museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter, doorHeight, museumOuter);
        glTexCoord2f(20.0, 0.0);   glVertex3f(museumOuter, doorHeight, museumOuter);
        glTexCoord2f(20.0, 1.0);   glVertex3f(museumOuter, museumHeight, museumOuter);

        //FRONT INNER TOP
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumInner, museumHeight, museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumInner, doorHeight, museumInner);
        glTexCoord2f(20.0, 0.0);   glVertex3f(museumInner, doorHeight, museumInner);
        glTexCoord2f(20.0, 1.0);   glVertex3f(museumInner, museumHeight, museumInner);

        //FRONT OUTER BOTTOMLEFT
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumOuter, doorHeight, museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter, 0, museumOuter);
        glTexCoord2f(17.0, 0.0);   glVertex3f(-doorWidth, 0, museumOuter);
        glTexCoord2f(17.0, 1.0);   glVertex3f(-doorWidth, doorHeight, museumOuter);

        //FRONT INNER BOTTOMLEFT
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumInner, doorHeight, museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumInner, 0, museumInner);
        glTexCoord2f(17.0, 0.0);   glVertex3f(-doorWidth, 0, museumInner);
        glTexCoord2f(17.0, 1.0);   glVertex3f(-doorWidth, doorHeight, museumInner);

        //FRONT OUTER BOTTOMRIGHT
        glTexCoord2f(0.0, 1.0);   glVertex3f(doorWidth, doorHeight, museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(doorWidth, 0, museumOuter);
        glTexCoord2f(17.0, 0.0);   glVertex3f(museumOuter, 0, museumOuter);
        glTexCoord2f(17.0, 1.0);   glVertex3f(museumOuter, doorHeight, museumOuter);

        //FRONT INNER BOTTOMRIGHT
        glTexCoord2f(0.0, 1.0);   glVertex3f(doorWidth, doorHeight, museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(doorWidth, 0, museumInner);
        glTexCoord2f(17.0, 0.0);   glVertex3f(museumInner, 0, museumInner);
        glTexCoord2f(17.0, 1.0);   glVertex3f(museumInner, doorHeight, museumInner);

        //DOOR INNER LEFT
        glTexCoord2f(0.0, 1.0);   glVertex3f(-doorWidth, doorHeight, museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-doorWidth, 0, museumOuter);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-doorWidth, 0, museumInner);
        glTexCoord2f(1.0, 1.0);   glVertex3f(-doorWidth, doorHeight, museumInner);

        //DOOR INNER RIGHT
        glTexCoord2f(0.0, 1.0);   glVertex3f(doorWidth, doorHeight, museumInner);
        glTexCoord2f(0.0, 0.0);   glVertex3f(doorWidth, 0, museumInner);
        glTexCoord2f(1.0, 0.0);   glVertex3f(doorWidth, 0, museumOuter);
        glTexCoord2f(1.0, 1.0);   glVertex3f(doorWidth, doorHeight, museumOuter);

        //DOOR INNER TOP
        glTexCoord2f(0.0, 1.0);   glVertex3f(doorWidth, doorHeight, museumOuter);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-doorWidth, doorHeight, museumOuter);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-doorWidth, doorHeight, museumInner);
        glTexCoord2f(1.0, 1.0);   glVertex3f(doorWidth, doorHeight, museumInner);

    glEnd();
}

//--------------------------------------------------------------------------------

void museumRoof() //TODO textures
{
    glBegin(GL_TRIANGLES);
        //FRONT BOTTOM
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-6, museumOuter+10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-6, museumOuter+10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight, 0);

        //BACK BOTTOM
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight, 0);

        //RIGHT BOTTOM
        glTexCoord2f(0.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-6, museumOuter+10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight, 0);

        //LEFT BOTTOM
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-6, museumOuter+10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight, 0);

        //FRONT TOP
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-3, museumOuter+10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-3, museumOuter+10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight+3, 0);

        //BACK TOP
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-3, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-3, -museumOuter-10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight+3, 0);

        //RIGHT TOP
        glTexCoord2f(0.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-3, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-3, museumOuter+10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight+3, 0);

        //LEFT TOP
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-3, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-3, museumOuter+10);
        glTexCoord2f(0.5, 1.0);   glVertex3f(0, roofHeight+3, 0);

    glEnd();
    glDisable(GL_TEXTURE_2D);

}

//--------------------------------------------------------------------------------
void roofStrips()
{
    //Now draw quads to join two roof layers
    glBegin(GL_QUADS);
        //BACK
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumOuter-10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-3, -museumOuter-10);
        glTexCoord2f(10.0, 0.0);  glVertex3f(museumOuter+10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(1.0, 1.0);  glVertex3f(museumOuter+10, museumHeight-3, -museumOuter-10);

        //LEFT
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumOuter-10, museumHeight-6, museumOuter+10);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-3, museumOuter+10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(1.0, 1.0);   glVertex3f(-museumOuter-10, museumHeight-3, -museumOuter-10);

        //RIGHT
        glTexCoord2f(0.0, 1.0);   glVertex3f(museumOuter+10, museumHeight-6, -museumOuter-10);
        glTexCoord2f(0.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-3, -museumOuter-10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-6, museumOuter+10);
        glTexCoord2f(1.0, 1.0);   glVertex3f(museumOuter+10, museumHeight-3, museumOuter+10);

        //FRONT
        glTexCoord2f(0.0, 1.0);   glVertex3f(-museumOuter-10, museumHeight-3, museumOuter+10);
        glTexCoord2f(0.0, 0.0);   glVertex3f(-museumOuter-10, museumHeight-6, museumOuter+10);
        glTexCoord2f(1.0, 0.0);   glVertex3f(museumOuter+10, museumHeight-6, museumOuter+10);
        glTexCoord2f(1.0, 1.0);   glVertex3f(museumOuter+10, museumHeight-3, museumOuter+10);
    glEnd();
}

//--------------------------------------------------------------------------------

void revolvingDoor() //Draws one door (rotate 90 degrees on y axs to draw other three)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[8]);
    glPushMatrix();
    glRotatef(theta, 0, 1, 0);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(2.5, doorHeight, 2.5);
        glTexCoord2f(0.0, 0.0);   glVertex3f(2.5, 0, 2.5);
        glTexCoord2f(1.0, 0.0);   glVertex3f(doorWidth-0.01, 0, 2.5);
        glTexCoord2f(1.0, 1.0);   glVertex3f(doorWidth-0.01, doorHeight, 2.5);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glColor3d(1, 1, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(doorWidth-0.01, doorHeight, 2.5);
        glTexCoord2f(0.0, 0.0);   glVertex3f(doorWidth-0.01, 0, 2.5);
        glTexCoord2f(1.0, 0.0);   glVertex3f(doorWidth-0.01, 0, -2.5);
        glTexCoord2f(1.0, 1.0);   glVertex3f(doorWidth-0.01, doorHeight, -2.5);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);   glVertex3f(2.5, doorHeight, -2.5);
        glTexCoord2f(0.0, 0.0);   glVertex3f(2.5, 0, -2.5);
        glTexCoord2f(1.0, 0.0);   glVertex3f(doorWidth-0.01, 0, -2.5);
        glTexCoord2f(1.0, 1.0);   glVertex3f(doorWidth-0.01, doorHeight, -2.5);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------------------------

void catapultBase()
{
    //Base
    glColor4f(0.76, 0.60, 0.42, 1.0);
    glPushMatrix();
      glTranslatef(0.0, 4.0, 0.0);
      glScalef(20.0, 2.0, 10.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Wheels
    glColor4f(0., 0., 0., 0.);
    glPushMatrix();
      glTranslatef(-8.0, 2.0, 5.1);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(8.0, 2.0, 5.1);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-8.0, 2.0, -5.1);
      glRotatef(180.0, 0., 1., 0.);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(8.0, 2.0, -5.1);
      glRotatef(180.0, 0., 1., 0.);
      gluDisk(q, 0.0, 2.0, 20, 2);
    glPopMatrix();

    //Sides
    //Front
    glColor4f(0.76, 0.60, 0.42, 1.0);
    glPushMatrix();
      glTranslatef(0.0, 11.5, 4.49);
      glScalef(2.0, 13.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(4.0, 8.0, 4.49);
      glRotatef(45., 0., 0., 1.0);
      glScalef(1.0, 12.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-4.0, 8.0, 4.49);
      glRotatef(-45., 0., 0., 1.0);
      glScalef(1.0, 12.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Back
    glPushMatrix();
      glTranslatef(0.0, 11.5, -4.49);
      glScalef(2.0, 13.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(4.0, 8.0, -4.49);
      glRotatef(45., 0., 0., 1.0);
      glScalef(1.0, 12.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-4.0, 8.0, -4.49);
      glRotatef(-45., 0., 0., 1.0);
      glScalef(1.0, 12.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Crossbar
    glPushMatrix();
      glTranslatef(0.0, 17.5, 0.0);
      glScalef(2.0, 1.0, 8.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Bottombar
    glPushMatrix();
      glTranslatef(-6, 6., 0.0);
      glRotatef(45., 0., 0., 1.);
      glScalef(1.0, 1.0, 8.0);
      glutSolidCube(1.0);
    glPopMatrix();
}

//--------------------------------------------------------------------------------

void catapult()
{
    glPushMatrix();
      glTranslatef(0., 5.3, 0.0);
      glRotatef(shaftRotation, 0., 0., 1.0);
      glTranslatef(-10., 0.0, 0.);
      glScalef(20.0, 1.0, 2.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glColor4f(202/256, 204/256, 206/256, 1.0);
    glPushMatrix();
        glTranslatef(ballX, ballY, 0);
        if (catapultFiring) {
            float spot_pos[] = {5,-5, 0};
            float spot_dir[] = {1, -ballY, 0};
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
        } else {
            glDisable(GL_LIGHT0);
        }
        glutSolidSphere(1, 10, 10);
    glPopMatrix();
}


//--------------------------------------------------------------------------------

void catapultAnimation(int time)
{
    glutPostRedisplay();
    catapultFiring = 1;

    ballX = (cos(50*(M_PI/180)) * 30 * time*0.05) + -18;
    ballY = ((sin(50*(M_PI/180)) * 30 * time*0.05) + (-9.81 * 0.5 * pow(time*0.05,2))) + 13;
    time += 1;

    if (shaftRotation > -83 && reverseRotation == 0) {
        shaftRotation -= 4;
    } else {
        reverseRotation = 1;
        shaftRotation += 2;
        if (shaftRotation > -20) {
            shaftRotation = -20;
        }
    }

    if (ballY > 2) {
        glutTimerFunc(1,catapultAnimation,time);
    } else {
        catapultFiring = 0;
        reverseRotation = 0;
    }
}


//-----------------Bottom panel of the boat------------------------------
void boatBase()
{
    const int n = 40;   //Size of the array

    float vx[] = { -20, -18, -16, -15, -14, -13, -11, -9, -6, -3, 0, 3, 6, 9, 11, 12, 14, 15, 16, 18, 20,
                         18,  16,  15,  14,  13,  11,  9,  6,  3,  0,  -3,  -6,  -9, -11, -12, -14, -15, -16, -18};
    float vy[n] = { 0 };
    float vz[] = { 0, 2, 3, 3.5, 4, 4.2, 4.8, 5, 5, 5, 5, 5, 5, 5, 4.8, 4.2, 4, 3.5, 3, 2, 0,
                  -2, -3, -3.5, -4, -4.2, -4.8, -5, -5, -5, -5, -5, -5, -5, -4.8, -4.2, -4, -3.5, -3, -2 };

    //Draw the above polygon here
    glBegin(GL_POLYGON);
        for (int i = 0; i < n; i++)
            glVertex3f(vx[i], vy[i], vz[i]);
    glEnd();

}

//-----------Side+Hull of the boat---------------------------------------
void boatSide()
{
    const int n = 21;   //Size of the array

    float vx[] = { -20, -18, -16, -15, -14, -13, -11, -9, -6, -3, 0, 3, 6, 9, 11, 12, 14, 15, 16, 18, 20};
    float vy[21] = { 0 };
    float vz[] = { 0, 2, 3, 3.5, 4, 4.2, 4.8, 5, 5, 5, 5, 5, 5, 5, 4.8, 4.2, 4, 3.5, 3, 2, 0 };

    float wx[] = { -25, -22, -19, -17, -15, -13,  -11, -9, -6, -3, 0,  3,  6,  9,   11,  13, 15, 17, 19, 22, 25 };
    float wy[] = { 10,  10,  9,  8,  7,  6, 5.5, 5, 5, 5, 5, 5, 5, 5, 5.5, 6, 7, 8, 9, 10, 10 };
    //float wz[] = { 0, 3, 5, 6, 6.5, 6.8, 7.2, 7.5, 7.8, 8, 8, 8, 7.8, 7.5, 7.2, 6.8, 6.5, 6, 5, 3, 0 };
    float wz[] = { 0, 3, 5, 6, 7, 7.6, 8, 8.5, 8.8, 9, 9, 9, 8.8, 8.5, 8, 7.6, 6, 6, 5, 3, 0 };

    //Draw a quad strip using the above two polygonal lines
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[9]);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < n; i++) {
        glTexCoord2f( (float)i/(float)(n-1), 0);
        glVertex3f(vx[i], vy[i], vz[i]);
        if (i > 0) normal(wx[i-1], wy[i-1], wz[i-1],
                          vx[i], vy[i], vz[i],
                          wx[i], wy[i], wz[i]);
        glTexCoord2f( (float)i/(float)(n-1), 1);
        glVertex3f(wx[i], wy[i], wz[i]);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------
void boatSeats()
{
    glColor4f(0.76, 0.60, 0.42, 1.0);
    glPushMatrix();
        glTranslatef(-7, 4, 0);
        glScalef(4, 1, 14.7);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7, 4, 0);
        glScalef(4, 1, 14.7);
        glutSolidCube(1.0);
    glPopMatrix();
}

//---------------------------------------------------------------------------
void boatOar()
{
    gluCylinder(q, 0.5, 0.5, 20, 100, 100);

    glPushMatrix();
        glTranslatef(0, 0, 20);
        glScalef(3, 0.5, 5);
        glutSolidCube(1.0);
    glPopMatrix();
}

//--Draws a character model constructed using GLUT objects ------------------
void statueArmsLegs()
{
    glColor4f(0.76, 0.58, 0.51, 1.0);  //Lower leg
    glPushMatrix();
        glTranslatef(3, 3.8, 2);
        glScalef(2, 6, 2);
        glutSolidCube(1.0);
    glPopMatrix();

    glColor4f(0.6, 0.6, 0.6, 1.0);     //Upper leg
    glPushMatrix();
        glTranslatef(5.1, 5.8, 2);
        glRotatef(90, 1, 0, 0);
        glScalef(2.3, 2, 2);
        glutSolidCube(1.0);
    glPopMatrix();

    glColor4f(0.8, 0.58, 0.51, 1.0);   //Arm
    glPushMatrix();
        glTranslatef(6, 9, 3.5);
        glRotatef(-30, 0, 0, 1);
        glScalef(1, 6, 1);
        glutSolidCube(1.0);
    glPopMatrix();
}


//-------------------------------------------------------------------------------
void statueHeadTorso()
{
    glColor4f(0.8, 0.58, 0.51, 1.0);       //Head
    glPushMatrix();
        glTranslatef(7.2, 13, 0);
        glScalef(2, 2.5, 2.5);
        glutSolidCube(1.0);
    glPopMatrix();

    glColor4f(0., 0., 0.502, 1.0);          //Torso
    glPushMatrix();
        glTranslatef(7.2, 8.3, 0);
        glScalef(2, 7, 6);
        glutSolidCube(1.0);
    glPopMatrix();
}

//--------------------------------------------------------------------------------

void seesaw()
{
    glColor4f(0.76, 0.60, 0.42, 1.0);
    glPushMatrix();
        glTranslatef(0, 8.5, 0);
        glRotatef(seesawRotation, 0., 0., 1.);
        glScalef(60, 1, 6);
        glutSolidCube(1.0);
    glPopMatrix();

    //b1 and b2
    glColor4f(0, 0.5, 0, 1.0);
    glPushMatrix();
        glTranslatef(b1X, b1Y, 0);
        glutSolidSphere(2, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(b2X, b2Y, 0);
        glutSolidSphere(2, 20, 20);
    glPopMatrix();
}

void ballTwoAnimation(int time);

//--------------------------------------------------------------------------------

void ballOneAnimation(int time)
{
    glutPostRedisplay();
    b1Y = (0.04429 * time) + (0.5 * -0.00098 * pow(time, 2));
    b1Y *= 60; //To make height in terms of pixels not metres
    b1Y += 4; //Initial height in pixels
    time += 1;

    if (b1Y < 20) {

        if (b1OnWayDown) {
            //start ballOneAnimation if not already started
            if (!b2) {
                b2 = 1;
                glutTimerFunc(1, ballTwoAnimation, 0);
            }

            if (b1Y < 4.1) { //Finish ballOneAnimation
                seesawRotation = -15.466;
                b1Y = 4;
                b1=0;
                b1OnWayDown = 0;
            } else {
                seesawRotation -= 3;
                glutTimerFunc(1, ballOneAnimation, time);
            }

        } else { //b1 is on its way up
            seesawRotation += 3;
            glutTimerFunc(1, ballOneAnimation, time);
        }
    } else { //b1Y is above 16 so set b1Up
        b1OnWayDown = 1;
        seesawRotation = 15.466;
        glutTimerFunc(1, ballOneAnimation, time);
    }
}

//--------------------------------------------------------------------------------

void ballTwoAnimation(int time)
{
    glutPostRedisplay();
    b2Y = (0.04429 * time) + (0.5 * -0.00098 * pow(time, 2));
    b2Y *= 60; //To make height in terms of pixels not metres
    b2Y += 4; //Initial height in pixels
    time += 1;

    if (b2Y < 20) { //Could be on way up or way down

        if (b2OnWayDown) { //b2 is on its way down
            //start ballOneAnimation if not already started
            if (!b1) {
                b1 = 1;
                glutTimerFunc(1, ballOneAnimation, 0);
            }

            if (b2Y < 4.1) { //Finish ballTwoAnimation
                b2Y = 4;
                b2=0;
                b2OnWayDown = 0;
            } else {
                glutTimerFunc(1, ballTwoAnimation, time);
            }

        } else { //b2 is on its way up
            glutTimerFunc(1, ballTwoAnimation, time);
        }
    } else { //b2Y is above 16 so set b2OnWayDown
        b2OnWayDown = 1;
        glutTimerFunc(1, ballTwoAnimation, time);
    }
}

//--------------------------------------------------------------------------------

void ballOneDown(int time)
{
    glutPostRedisplay();
    b1Y = 1 + (0.5 * -0.00098 * pow(time, 2));
    b1Y *= 60; //To make height in terms of pixels not metres
    time += 1;

    if (b1Y < 16) { //The ball is at seesaw level

        //Start b2 animation if not started already
        if (!b2) {
            b2= 1;
            glutTimerFunc(1, ballTwoAnimation, 0);
        }

        if (b1Y < 4) { //Finish ballOneDown
            b1Y = 4;
            b1=0;
            b1OnWayDown = 0;
            seesawRotation = -15.466;
        } else {
            seesawRotation -= 4;
            glutTimerFunc(1, ballOneDown, time);
        }
    } else { //b1Y above 16 so call function as usual
        glutTimerFunc(1, ballOneDown, time);
    }
}

//--------------------------------------------------------------------------------

void seesawPivot()
{
    glColor4f(0.4, 0.4, 0.4, 1.0);
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < 11; i++) {
            glVertex3f(vx[i], vy[i], vz[i]);
            if (i > 0) normal(wx[i-1], wy[i-1], wz[i-1],
                              vx[i], vy[i], vz[i],
                              wx[i], wy[i], wz[i]);
            glVertex3f(wx[i], wy[i], wz[i]);
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < 11; i++) {
            glVertex3f(px[i], py[i], pz[i]);
            if (i > 0) normal(qx[i-1], qy[i-1], qz[i-1],
                              px[i], py[i], pz[i],
                              qx[i], qy[i], qz[i]);
            glVertex3f(qx[i], qy[i], qz[i]);
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < 11; i++) {
            glVertex3f(sx[i], sy[i], sz[i]);
            if (i > 0) normal(tx[i-1], ty[i-1], tz[i-1],
                              sx[i], sy[i], sz[i],
                              tx[i], ty[i], tz[i]);
            glVertex3f(tx[i], ty[i], tz[i]);
        }
    glEnd();
}

//--------------------------------------------------------------------------------

void keyboard (unsigned char key, int x, int y)
{
    if (key == 'c' && catapultFiring == 0)
    {
        ballX = -18;
        ballY  = 13;
        shaftRotation = -20;
        glutTimerFunc(0,catapultAnimation,1);
    }
}

//--------------------------------------------------------------------------------
void display()
{
    glEnable(GL_LIGHTING);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45., 1., 1., 3000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);
    gluLookAt(eye_x, cam_hgt, eye_z,  look_x, cam_hgt, look_z,   0, 1, 0);
    skybox();
    floor();

    float shadowMat[16] = {1000.0f, 0, 0, 0, 1000, 0, 500, -1, 0, 0, 1000, 0, 0, 0, 0, 1000};
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glColor4f(0.2, 0.2, 0.2, 1.0);
        museumWalls();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, txId[7]);
        museumWalls();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glColor4f(0.2, 0.2, 0.2, 1.0);
        museumRoof();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, txId[6]);
        museumRoof();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glColor4f(0.2, 0.2, 0.2, 1.0);
        roofStrips();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glPushMatrix();
        glColor3d(0.7, 0.54, 0.40); //Roughly the same colour as roof texture
        roofStrips();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, museumOuter-2.5);
        //Draw the 4 doors that make up a revolving door
        for (int i = 0; i < 4; i++) {
            glRotatef(90 * i, 0, 1, 0);
            revolvingDoor();
        }
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-museumInner+70, 0, -museumInner+70); //Position catapult on back wall of museum
        glScalef(3., 3., 3.);
        catapult();
        catapultBase();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-museumInner+100, 0, museumInner-70);
        glScalef(1.7, 1.7, 1.7);
        glRotatef(90, 0, 1, 0);
        seesaw();
        seesawPivot();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(museumInner-80, 0, 50);
        glRotatef(90, 0, 1, 0);
        glScalef(2., 2., 2.);
        boatBase();           //Bottom panel of the boat
        boatSide();           //Front side of the boat

        glPushMatrix();
            glScalef(1, 1, -1);
            boatSide();
        glPopMatrix();

        //Oar
        glPushMatrix();
            glTranslatef(0, 7, 4);
            glRotatef(15, 1, 0, 0);
            boatOar();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 7, -4);
            glRotatef(-15, 1, 0, 0);
            glRotatef(180, 0, 1, 0);
            boatOar();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        boatSeats();
        statueArmsLegs();
        statueHeadTorso();

        glPushMatrix();
            glScalef(1, 1, -1);
            statueArmsLegs();
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

//-------------------------------------------------------------------------
void myTimer(int value)
{
    glutPostRedisplay();
    theta += 1;
    glutTimerFunc(10, myTimer, value);
}

//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (1200, 900);
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("acl118 COSC363 Assignment 1");
   initialise();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(10, myTimer, 0);
   glutTimerFunc(0, ballOneDown, 0);;
   glutMainLoop();
   return 0;
}
