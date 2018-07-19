/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


GLint a=0;
static int slices = 16;
static int stacks = 16;
GLint ancho=1200;
GLint alto=500;
struct puntos{
    float x;
    float y;
};
struct puntos3{
    float x;
    float y;
    float z;
};
puntos puntos2D;
puntos3 puntos3D;
/* GLUT callback Handlers */
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    ancho = width;
    alto = height;
}
void rotarCurva(std::vector< puntos3> vect3){
    glPushMatrix();
    for(int i=0;i<360;i++){
        for(int j=0;j<vect3.size()-1;j++){
            glBegin(GL_TRIANGLES);
            glVertex3f(vect3[j].x,vect3[j].y,vect3[j].z);
            glVertex3f(vect3[j+1].x,vect3[j+1].y,vect3[j].z+1.0);
            glVertex3f(vect3[j+1].x,vect3[j+1].y,vect3[j].z-1.0);
            glEnd();
        }
        glRotatef(i,0,1,0);
        for(int j=0;j<vect3.size()-1;j++){
            glBegin(GL_TRIANGLES);
            glVertex3f(vect3[j+1].x,vect3[j+1].y,vect3[j].z);
            glVertex3f(vect3[j].x,vect3[j].y,vect3[j].z+1.0);
            glVertex3f(vect3[j].x,vect3[j].y,vect3[j].z-1.0);
            glEnd();
        }
    }
    glPopMatrix();
}
void linea(std::vector< puntos> vect1){
    glBegin(GL_LINES);
    for(int i=0;i<vect1.size()-1;i++){
        glVertex3f(vect1[i].x,vect1[i].y,-1.0);
        glVertex3f(vect1[i+1].x,vect1[i+1].y,-1.0);
    }

    glEnd();
}
void display(void)
{

    std::vector< puntos> vect1;
    std::vector<puntos3> vect3;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   std::ifstream my_file;
    my_file.open("C:\\Users\\Emmanuel\\Documents\\Universidad\\Ingenieria de Sistemas\\Noveno Semestre\\Intro Compu Grafica\\Taller4\\curvaAbierta.in");
    std::string s;
    if (my_file.is_open())
  {
    while ( getline (my_file,s) && s!="f" )
    {
      std::stringstream data(s);
      data>>puntos3D.x;
      data>>puntos3D.y;
      puntos3D.z=0.0;
      //vect1.push_back(puntos2D);
      vect3.push_back(puntos3D);
      data.clear();
    }
    my_file.close();
  }

  else std::cout << "Unable to open file";
  rotarCurva(vect3);
    /*std::ifstream my_file;
    my_file.open("curvaAbierta.in");
    std::string s;
    if (my_file.is_open())
  {
    while ( getline (my_file,s,' ') && s!="f" )
    {
      std::cout << s << '\n';

    }
    my_file.close();
  }

  else std::cout << "Unable to open file";*/
    /*glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();
*/
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        glRotatef(10.0,1.0,0.0,0.0);
        glutPostRedisplay();
        break;
    case 'X':
        glRotatef(-10.0,1.0,0.0,0.0);
        glutPostRedisplay();
        break;
    case 'y':
        glRotatef(15.0,0.0,1.0,0.0);
        glutPostRedisplay();
        break;
    case 'Y':
        glRotatef(-15.0,0.0,1.0,0.0);
        glutPostRedisplay();
        break;
    case 'z':
        glRotatef(3.0,0.0,0.0,1.0);
        glutPostRedisplay();
        break;
    case 'Z':
        glRotatef(-3.0,0.0,0.0,1.0);
        glutPostRedisplay();
        break;
    case 'd': case 'D':
        glLoadIdentity();
        gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glutPostRedisplay();
        break;
    }
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}



void init()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    ancho = 1200;
    alto = 500;
}

/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Solidos de Revolucion");
    init();
    glutKeyboardFunc (keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
