//
// Created by quimpm on 17/10/21.
//

#include "tank.h"
//
// Created by quimpm on 17/10/21.
//

void Tank::drawTank(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos){
    drawWheels(size_x, size_y, size_z, x_pos, y_pos);
    drawBase(size_x, size_y, size_z, color, x_pos, y_pos);
    drawCavin(size_x, size_y, size_z, color, x_pos, y_pos);
    drawCannon(size_x, size_y, size_z, x_pos, y_pos);
}

void Tank::drawWheels(int size_x, int size_y, int size_z, float x_pos, float y_pos){
    int radius = size_x/6;
    GLUquadricObj *quadratic;

    glPushMatrix();
    glTranslatef(x_pos+size_x/4, y_pos + size_y / 6, radius);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x_pos+3*size_x/4, y_pos + size_y / 6, radius);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x_pos+size_x/4, y_pos + 5 * size_y / 6, radius);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x_pos+3*size_x/4, y_pos + 5 * size_y / 6, radius);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();
}

void Tank::drawBase(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos){

    /*Part de Baix*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, size_y / 6);
    glVertex3f(x_pos+size_x, y_pos + size_y / 6, size_y / 6);
    glVertex3f(x_pos+size_x, y_pos + 5 * size_y / 6, size_y / 6);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, size_y / 6);
    glEnd();

    /*Part de Dalt*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos,y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x, y_pos + size_y / 6, 2 * size_z / 3 );
    glEnd();

    /*Part Esquerra*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, size_y / 6);
    glVertex3f(x_pos, y_pos + size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x, y_pos + size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x, y_pos + size_y / 6, size_y / 6);
    glEnd();

    /*Part Dreta*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, size_y / 6);
    glVertex3f(x_pos+size_x, y_pos + 5 * size_y / 6, size_y / 6);
    glVertex3f(x_pos+size_x, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glEnd();

    /*Part Frontal*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos+size_x, y_pos + size_y / 6, size_y / 6);
    glVertex3f(x_pos+size_x, y_pos + size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x, y_pos + 5 * size_y / 6, size_y / 6);
    glEnd();

    /*Part Darrere*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, size_y / 6);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, size_y / 6);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos, y_pos + size_y / 6, 2 * size_z / 3);
    glEnd();

}

void Tank::drawCavin(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos){

    /*Part de Dalt*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, size_z);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, size_z);
    glVertex3f(x_pos+size_x/2, y_pos + 5 * size_y / 6, size_z);
    glVertex3f(x_pos+size_x/2, y_pos + size_y / 6, size_z);
    glEnd();

    /*Part Esquerra*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos, y_pos + size_y / 6, size_z);
    glVertex3f(x_pos+size_x/2, y_pos + size_y / 6, size_z);
    glVertex3f(x_pos+size_x/2, y_pos + size_y / 6, 2 * size_y / 3);
    glEnd();

    /*Part Dreta*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x/2, y_pos + 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x/2, y_pos + 5 * size_y / 6, size_z);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, size_z);
    glEnd();

    /*Part Frontal*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos+size_x/2, y_pos + size_y / 6, 2 * size_z / 3);
    glVertex3f(x_pos+size_x/2, y_pos + size_y / 6, size_z);
    glVertex3f(x_pos+size_x/2, y_pos + 5 * size_y / 6, size_z);
    glVertex3f(x_pos+size_x/2, y_pos + 5 * size_y / 6, 2 * size_y / 3);
    glEnd();

    /*Part Darrere*/
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_QUADS);
    glVertex3f(x_pos, y_pos + size_y / 6, 2 * size_y / 3);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, 2 * size_y / 3);
    glVertex3f(x_pos, y_pos + 5 * size_y / 6, size_z);
    glVertex3f(x_pos, y_pos + size_y / 6, size_z);
    glEnd();

}

void Tank::drawCannon(int size_x, int size_y, int size_z, float x_pos, float y_pos){
    float radius = (size_z / 12);
    GLUquadricObj *quadratic;
    glPushMatrix();
    glTranslatef(x_pos+size_x/2, y_pos + size_y / 2, 3 * size_z / 4 + (size_z / 4) / 2);
    glRotatef(90, 0, 1, 0);
    glColor3f(0,0,0);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, radius, radius, size_x/2, 32, 32);
    glEnd();
    glPopMatrix();

}

