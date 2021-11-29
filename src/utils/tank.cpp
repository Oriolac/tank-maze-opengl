//
// Created by quimpm on 17/10/21.
//

#include <vector>
#include "tank.h"
#include "textures.h"
//
// Created by quimpm on 17/10/21.
//

void Tank::drawTank(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos, float current_degreee){
    setMaterial(color);
    glPushMatrix();
    glTranslatef(x_pos, y_pos, 20);
    glTranslatef(size_x / 2, size_y / 2, 0);
    glRotatef(current_degreee,0, 0, 1);
    glTranslatef(-size_x / 2, -size_y / 2, 0);
    glPushMatrix();
    drawWheels(size_x, size_y, size_z);
    drawBase(size_x, size_y, size_z, color);
    drawCavin(size_x, size_y, size_z, color);
    drawCannon(size_x, size_y, size_z, color);
    glPopMatrix();
    glPopMatrix();

}

void Tank::drawWheels(int size_x, int size_y, int size_z){
    int radius = size_x/6;
    GLUquadricObj *quadratic;
    glPushMatrix();
    glTranslatef(size_x/4, size_y / 6, radius);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3*size_x/4, size_y / 6, radius);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(size_x/4, 5 * size_y / 6, radius);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3*size_x/4,5 * size_y / 6, radius);
    quadratic = gluNewQuadric();
    gluSphere(quadratic,radius,32,32);
    glEnd();
    glPopMatrix();
}

void Tank::drawBase(int size_x, int size_y, int size_z, float color[3]){

    /*Part de Baix*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0, size_y / 6, size_y / 6);
    glVertex3f(size_x,  size_y / 6, size_y / 6);
    glVertex3f(size_x,  5 * size_y / 6, size_y / 6);
    glVertex3f(0, 5 * size_y / 6, size_y / 6);
    glEnd();

    /*Part de Dalt*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0, size_y / 6, 2 * size_z / 3);
    glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x, 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x, size_y / 6, 2 * size_z / 3 );
    glEnd();

    /*Part Esquerra*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0,  size_y / 6, size_y / 6);
    glVertex3f(0,  size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x,  size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x,  size_y / 6, size_y / 6);
    glEnd();

    /*Part Dreta*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0, 5 * size_y / 6, size_y / 6);
    glVertex3f(size_x, 5 * size_y / 6, size_y / 6);
    glVertex3f(size_x, 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
    glEnd();

    /*Part Frontal*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(size_x, size_y / 6, size_y / 6);
    glVertex3f(size_x, size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x, 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x, 5 * size_y / 6, size_y / 6);
    glEnd();

    /*Part Darrere*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0, size_y / 6, size_y / 6);
    glVertex3f(0, 5 * size_y / 6, size_y / 6);
    glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(0, size_y / 6, 2 * size_z / 3);
    glEnd();

}

void Tank::drawCavin(int size_x, int size_y, int size_z, float color[3]){

    /*Part de Dalt*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0, size_y / 6, size_z);
    glVertex3f(0, 5 * size_y / 6, size_z);
    glVertex3f(size_x/2, 5 * size_y / 6, size_z);
    glVertex3f(size_x/2, size_y / 6, size_z);
    glEnd();

    /*Part Esquerra*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0, size_y / 6, 2 * size_z / 3);
    glVertex3f(0, size_y / 6, size_z);
    glVertex3f(size_x/2, size_y / 6, size_z);
    glVertex3f(size_x/2, size_y / 6, 2 * size_y / 3);
    glEnd();

    /*Part Dreta*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0,  5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x/2, 5 * size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x/2, 5 * size_y / 6, size_z);
    glVertex3f(0, 5 * size_y / 6, size_z);
    glEnd();

    /*Part Frontal*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(size_x/2, size_y / 6, 2 * size_z / 3);
    glVertex3f(size_x/2, size_y / 6, size_z);
    glVertex3f(size_x/2, 5 * size_y / 6, size_z);
    glVertex3f(size_x/2, 5 * size_y / 6, 2 * size_y / 3);
    glEnd();

    /*Part Darrere*/
    setMaterial(color);
    glBegin(GL_QUADS);
    glVertex3f(0,  size_y / 6, 2 * size_y / 3);
    glVertex3f(0,  5 * size_y / 6, 2 * size_y / 3);
    glVertex3f(0,  5 * size_y / 6, size_z);
    glVertex3f(0,  size_y / 6, size_z);
    glEnd();

}

void Tank::drawCannon(int size_x, int size_y, int size_z, float color[]) {
    float radius = (size_z / 12);
    GLUquadricObj *quadratic;
    glPushMatrix();
    glTranslatef(size_x/2, size_y / 2, 3 * size_z / 4 + (size_z / 4) / 2);
    glRotatef(90, 0, 1, 0);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, radius, radius, size_x/2, 32, 32);
    glEnd();
    glPopMatrix();

}

