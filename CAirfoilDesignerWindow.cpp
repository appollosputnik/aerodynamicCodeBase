#include "CAirfoilDesignerWindow.h"
#include <fstream>
#include <QVector2D>
#include <QVector3D>
#include "math.h"

float pi = 4*atan(1.0);

using namespace  std;

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

#include <QMouseEvent>

#include <math.h>

//INTERNATIONAL STANDARD WEATHER PREDICTOR
//AERODYNAMIC DESIGNER & FLOW PREDICTOR
//AERODYNAMIC POST PROCESSING ANALYZER
//LUNAR MISSION DESIGNER

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
//Lunar Mission:
1.  Design Lunar Vehicle (Voyger)
2.  Design Path (Trajectory)
3.  Landing on Moon
4.  Rover for driving on Moon
5.  Finding water (probe) and row Trees
6.  Electronics Associated.
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*

Aerofoil Geoometry
   a. Draw a symmetric aerofoil with le(0.0) and te(100.0)
   b. maximum thickness position (30.0, 0.0)
   c. Bezier control points (0.0,0.0), (30.0, 15.0), (100.0, 0.0), (30.0, -15.0), (0.0, 0.0)
   d. x, y. B(t) = SIGMA(i=0, i=n). nCi. (1-t)^(n-i). t^i. Pi
   e. get aerofoilKnotList.
   f. get dy/dx aerofoilKnotList
   g. get d^2y/dx^2 aerofoilKnotList
   h. camber=> maximum camber(30.0, 0.0) = 0.05C
   i. Leading edge radius/curvature <= d^2y/dx^2    write option to modify
   j. Trailing edge cusp (Kutaa condition) => dy/dx write option to modify

   //Algoritm...
   float xLE = 0.0; yLE = 0.0; xTE = 100.0; yTE = 0.0;
   float maxThicknessPosX = 30.0, maxThicknessPosY = 0.0;
   int nBzrCtrlPts = 5;
   float nezierCtrlPosX[5] = {0.0, 30.0, 100.0, 30.0, 0.0};
   float nezierCtrlPosY[5] = {0.0, 15.0, 0.0, -15.0, 0.0};
   int nKnots = 100;
   float ctrlPts_DyDx[4]; ctrlPts_D2yDx2[3];
   float camber = 5.0;
   float maxThickness = 30.0;
   float DyDxTECuspBezrDyDx[m]; //smoothen between first and last points at the Trailing Edge...

   */

static bool ifDraw = false;
static bool ifDrawKnots = false;
CAirfoilDesigner::CAirfoilDesigner(QWidget *parent) :
    QGLWidget(parent),
    xMin(0.0),
    xMax(0.0),
    yMin(0.0),
    yMax(0.0)
{
    trans[0] = 0.0;
    trans[1] = 0.0;
    trans[2] = 0.0;
    m_rot[0] = 0.0;
    m_rot[1] = 0.0;
    m_rot[2] = 0.0;
    zoomFactor = 1.0;
}

CAirfoilDesigner::~CAirfoilDesigner()
{
}

void CAirfoilDesigner::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    old_pos = e->localPos();
}

void CAirfoilDesigner::mouseReleaseEvent(QMouseEvent *e)
{
}

void CAirfoilDesigner::mouseMoveEvent(QMouseEvent *e)
{
    new_pos = e->localPos();

    dx = new_pos.x() - old_pos.x();
    dy = old_pos.y() - new_pos.y();

    if(e->button()==Qt::LeftButton)
    {
        trans[0] += dx;
        trans[1] -= dy;
        updateGL();
    }
    else if(e->button()==Qt::RightButton)
    {
        m_rot[0] += dx/500.0f;
        m_rot[1] -= dy/500.0f;
        #define clamp(x) x = x > 360.0f ? x-360.0f : x < -360.0f ? x+=360.0f : x
        clamp(m_rot[0]);
        clamp(m_rot[1]);
        updateGL();
    }

    else if(e->button()==Qt::MiddleButton)
    {

    }

    else
        QString str = "No operation at this point of time...";

    old_pos = new_pos;
}
void CAirfoilDesigner::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
    {
        zoomFactor *= 0.75;
    }
    else if(e->delta() <= 0)
    {
        zoomFactor /= 0.75;
    }

    updateGL();
}

void CAirfoilDesigner::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); 
}

void CAirfoilDesigner::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    xMin *= aspect; xMax *= aspect;
    //xMin *= aspect; xMax *= aspect;
    glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(xMin - 10.0f, xMax + 10.0f, yMax + 10.0f, yMin - 10.0f, -5.0, 5.0);
}

void CAirfoilDesigner::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(trans[0], trans[1], 0.0f);
    glRotatef(m_rot[0], 1.0, 0.0, 0.0);
    glRotatef(m_rot[1], 0.0, 1.0, 0.0);
    glScalef(zoomFactor, zoomFactor, zoomFactor);

    glBegin(GL_QUADS);
    glPointSize(4.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(xMin-3, yMin-3);
    glVertex2f(xMax+3, yMin-3);
    glVertex2f(xMax+3, yMax+3);
    glVertex2f(xMin-3, yMax+3);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(ifDraw) {
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    for(int i=0; i<nAnchors; i++)
    {
    if(i<nAnchors/2) {
        _anchorXu[i] = _anchorXu[i];
        glVertex2f(_anchorXu[i], _anchorYu[i]);
    }
    else if(i>nAnchors/2) {
        _anchorXu[i] = _anchorXu[i];
        glVertex2f(_anchorXu[i], _anchorYu[i]);
    }
    else {
        _anchorXu[i] = _anchorXu[i];
        glVertex2f(_anchorXu[i], _anchorYu[i]);
    }
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    for(int i=0; i<nAnchors; i++)
    {
    if(i<nAnchors/2) {
        _anchorXl[i] = _anchorXl[i];
        glVertex2f(_anchorXl[i], _anchorYl[i]);
    }
    else if(i>nAnchors/2) {
        _anchorXl[i] = _anchorXl[i];
        glVertex2f(_anchorXl[i], _anchorYl[i]);
    }
    else
        glVertex2f(_anchorXl[i], _anchorYl[i]);
    }
    glEnd();

    }

    if(ifDrawKnots) {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    for(int i=0; i<nKnots; i++) {
        glVertex2f(_knotsXu[i], _knotsYu[i]);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    for(int i=0; i<nKnots; i++) {
    if(i<nKnots/2) {
        _knotsXl[i] = _knotsXl[i];
        glVertex2f(_knotsXl[i], _knotsYl[i]);
    }
    else if(i>nKnots/2) {
        _knotsXl[i] = _knotsXl[i];
        glVertex2f(_knotsXl[i], _knotsYl[i]);
    }
    else
        glVertex2f(_knotsXl[i], _knotsYl[i]);
    }
    glEnd();
    }
    glFlush();
}

void CAirfoilDesigner::set_domain(float xmin, float xmax, float ymin, float ymax)
{
    xMin = xmin;
    xMax = xmax;
    yMin = ymin;
    yMax = ymax;
    updateGL();
}

void CAirfoilDesigner::set_anchors(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
     nAnchors = n;
    _anchorXu = x1; _anchorYu = y1; _anchorZu = z1;
    _anchorXl = x2; _anchorYl = y2; _anchorZl = z2;
    if(!ifDraw)
    ifDraw = !ifDraw;
    updateGL();
}
void CAirfoilDesigner::set_bezier_knots(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
     nKnots = n;
    _knotsXu = x1; _knotsYu = y1; _knotsZu = z1;
    _knotsXl = x2; _knotsYl = y2; _knotsZl = z2;
    if(!ifDrawKnots)
    ifDrawKnots = !ifDrawKnots;
    updateGL();
}
