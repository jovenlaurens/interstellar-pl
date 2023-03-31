#include <cmath>

#ifdef __APPLE__

#include <GLUT/glut.h>

#else
#include <GL/freeglut.h>
#endif

#include "figure.h"

#define pi 3.1415926535897932384626434f

line::line(pair pt1, pair pt2, float r, float g, float b) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    this->r = r;
    this->g = g;
    this->b = b;
}

void line::draw() {
    glColor3f(r, g, b);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(pt1.first, pt1.second);
    glVertex2f(pt2.first, pt2.second);
    glEnd();
}

triangle::triangle(pair pt1, pair pt2, pair pt3, float r, float g, float b) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    this->pt3 = pt3;
    this->r = r;
    this->g = g;
    this->b = b;
}

void triangle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(pt1.first, pt1.second);
    glVertex2f(pt2.first, pt2.second);
    glVertex2f(pt3.first, pt3.second);
    glEnd();
}

quadrangle::quadrangle() = default;

quadrangle::quadrangle(pair pt1, pair pt2, pair pt3, pair pt4, float r, float g, float b) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    this->pt3 = pt3;
    this->pt4 = pt4;
    this->r = r;
    this->g = g;
    this->b = b;
}

void quadrangle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(pt1.first, pt1.second);
    glVertex2f(pt2.first, pt2.second);
    glVertex2f(pt3.first, pt3.second);
    glVertex2f(pt4.first, pt4.second);
    glEnd();
}

rectangle::rectangle(pair pt1, pair pt2, float r, float g, float b) {
    this->pt1 = pt1;
    this->pt2 = {pt1.first, pt2.second};
    this->pt3 = pt2;
    this->pt4 = {pt2.first, pt1.second};
    this->r = r;
    this->g = g;
    this->b = b;
}

circle::circle(pair center, float radius, float r, float g, float b) {
    this->center = center;
    this->radius = radius;
    this->r = r;
    this->g = g;
    this->b = b;
}

void circle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++) {
        glVertex2f(radius * cosf(pi / 10 * static_cast<float>(i)) + center.first,
                   radius * sinf(pi / 10 * static_cast<float>(i)) + center.second);
    }
    glEnd();
}

semicircle::semicircle(pair center, float angle, float radius, float r, float g, float b) {
    this->center = center;
    this->radius = radius;
    this->r = r;
    this->g = g;
    this->b = b;
    this->angle = angle;
}

void semicircle::draw() {
    float theta;
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    float rotate = angle * pi / 180;
    for (int i = 0; i <= 10; i++) {
        theta = static_cast<float>(i) * pi / 10;
        glVertex2f(center.first + radius * (float)cos(theta + rotate), center.second + radius * (float)sin(theta + rotate));
    }
    glEnd();
}
