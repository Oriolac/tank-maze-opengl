#include <GL/glut.h>
#include <math.h>

#define PI 3.1416

#define WIDTH 600
#define HEIGHT 400


/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 0;
int anglebeta = 0;

//-----------------------------------------------
//-----------------------------------------------

void PositionObserver(float alpha,float beta,int radi);

void display();
void keyboard(unsigned char c,int x,int y);


//-----------------------------------------------
//-----------------------------------------------

int main(int argc,char *argv[])
{
  anglealpha=90;
  anglebeta=30;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("3D Hello World");
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}

//-----------------------------------------------
//-----------------------------------------------

void position_observer(float alpha,float beta,int radi)
{
  float x,y,z;
  float upx,upy,upz;
  float modul;

  x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
  y = (float)radi*sin(beta*2*PI/360.0);
  z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

  if (beta>0)
    {
      upx=-x;
      upz=-z;
      upy=(x*x+z*z)/y;
    }
  else if(beta==0)
    {
      upx=0;
      upy=1;
      upz=0;
    }
  else
    {
      upx=x;
      upz=z;
      upy=-(x*x+z*z)/y;
    }


  modul=sqrt(upx*upx+upy*upy+upz*upz);

  upx=upx/modul;
  upy=upy/modul;
  upz=upz/modul;

  gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}


void drawWheels(int size_x, int size_z, int size_y){
    int radius = size_x/6;
    GLUquadricObj *quadratic;

    glPushMatrix();
    glTranslatef(size_x/4, radius, size_z/6);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3*size_x/4, radius, size_z/6);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(size_x/4, radius, 5*size_z/6);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3*size_x/4, radius, 5*size_z/6);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();


}

void drawBase(int size_x, int size_z, int size_y, float color[3]){

    /*Part de Baix*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, size_z/6,  size_z/6);
    glVertex3f(size_x, size_z/6, size_z/6);
    glVertex3f(size_x, size_z/6, 5*size_z/6);
    glVertex3f(0.0, size_z/6, 5*size_z/6);
    glEnd();

    /*Part de Dalt*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 2*size_y/3,  size_z/6);
    glVertex3f(0.0, 2*size_y/3, 5*size_z/6);
    glVertex3f(size_x, 2*size_y/3, 5*size_z/6);
    glVertex3f(size_x, 2*size_y/3, size_z/6);
    glEnd();

    /*Part Esquerra*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, size_z/6,  size_z/6);
    glVertex3f(0.0, 2*size_y/3, size_z/6);
    glVertex3f(size_x, 2*size_y/3, size_z/6);
    glVertex3f(size_x, size_z/6, size_z/6);
    glEnd();

    /*Part Dreta*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, size_z/6,  5*size_z/6);
    glVertex3f(size_x, size_z/6, 5*size_z/6);
    glVertex3f(size_x, 2*size_y/3, 5*size_z/6);
    glVertex3f(0.0, 2*size_y/3, 5*size_z/6);
    glEnd();

    /*Part Frontal*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(size_x, size_z/6,  size_z/6);
    glVertex3f(size_x, 2*size_y/3, size_z/6);
    glVertex3f(size_x, 2*size_y/3, 5*size_z/6);
    glVertex3f(size_x, size_z/6, 5*size_z/6);
    glEnd();

    /*Part Darrere*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0, size_z/6,  size_z/6);
    glVertex3f(0, size_z/6, 5*size_z/6);
    glVertex3f(0, 2*size_y/3, 5*size_z/6);
    glVertex3f(0, 2*size_y/3, size_z/6);
    glEnd();

}

void drawCavin(int size_x, int size_z, int size_y, float color[3]){

    /*Part de Dalt*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, size_y,  size_z/6);
    glVertex3f(0.0, size_y, 5*size_z/6);
    glVertex3f(size_x/2, size_y, 5*size_z/6);
    glVertex3f(size_x/2, size_y, size_z/6);
    glEnd();

    /*Part Esquerra*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 2*size_y/3,  size_z/6);
    glVertex3f(0.0, size_y, size_z/6);
    glVertex3f(size_x/2, size_y, size_z/6);
    glVertex3f(size_x/2, 2*size_z/3, size_z/6);
    glEnd();

    /*Part Dreta*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 2*size_y/3,  5*size_z/6);
    glVertex3f(size_x/2, 2*size_y/3, 5*size_z/6);
    glVertex3f(size_x/2, size_y, 5*size_z/6);
    glVertex3f(0.0, size_y, 5*size_z/6);
    glEnd();

    /*Part Frontal*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(size_x/2, 2*size_y/3,  size_z/6);
    glVertex3f(size_x/2, size_y, size_z/6);
    glVertex3f(size_x/2, size_y, 5*size_z/6);
    glVertex3f(size_x/2, 2*size_z/3, 5*size_z/6);
    glEnd();

    /*Part Darrere*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(0, 2*size_z/3,  size_z/6);
    glVertex3f(0, 2*size_z/3, 5*size_z/6);
    glVertex3f(0, size_y, 5*size_z/6);
    glVertex3f(0, size_y, size_z/6);
    glEnd();

}

void drawCannon(int size_x, int size_z, int size_y){
    float radius = (size_y/12);
    GLUquadricObj *quadratic;
    glPushMatrix();
    glTranslatef(size_x/2, 3*size_y/4+(size_y/4)/2, size_z/2);
    glRotatef(90, 0, 1, 0);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, radius, radius, size_x/2, 32, 32);
    glEnd();
    glPopMatrix();

}

void drawTank(int size_x, int size_z, int size_y, float color[3]){
    drawWheels(size_x, size_z, size_y);
    drawBase(size_x, size_z, size_y, color);
    drawCavin(size_x, size_z, size_y, color);
    drawCannon(size_x, size_z, size_y);
}

//-----------------------------------------------
//-----------------------------------------------
void display()
{
    int size_x = 100;
    int size_y = 100;
    int size_z = 100;
  glClearColor(1.0,1.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  position_observer(anglealpha,anglebeta,450);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH*0.6,WIDTH*0.6,-HEIGHT*0.6,HEIGHT*0.6,10,2000);

  glMatrixMode(GL_MODELVIEW);

  glPolygonMode(GL_FRONT,GL_FILL);
  glPolygonMode(GL_BACK,GL_LINE);

  glColor3f(0.2,0.2, 0.2);
  glBegin(GL_QUADS);
  glVertex3f(0.0, 0.0,  0.0);
  glVertex3f(0.0, 0.0, size_z);
  glVertex3f(size_x, 0.0, size_z);
  glVertex3f(size_x, 0.0, 0.0);
  glEnd();


  float color[3] = {0.439216,0.858824,0.576471};

  drawTank(size_x, size_z, size_y, color);

  glutSwapBuffers();
}

//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  int i,j;

  if (c=='i' && anglebeta<=(90-4))
    anglebeta=(anglebeta+3);
  else if (c=='k' && anglebeta>=(-90+4))
    anglebeta=anglebeta-3;
  else if (c=='j')
    anglealpha=(anglealpha+3)%360;
  else if (c=='l')
    anglealpha=(anglealpha-3+360)%360;

  glutPostRedisplay();
}

