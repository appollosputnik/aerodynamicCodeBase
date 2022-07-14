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
    xMin(-5.0),
    xMax(5.0),
    yMin(-5.0),
    yMax(5.0)
{
    _cx = 0.0;
    _cy = 0.0;
    _cz = 0.0;
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
    old_pos = e->pos();
}

void CAirfoilDesigner::mouseReleaseEvent(QMouseEvent *e)
{
}

void CAirfoilDesigner::mouseMoveEvent(QMouseEvent *e)
{
    new_pos = e->pos();

    dx = old_pos.x() - new_pos.x();
    dy = new_pos.y() - old_pos.y();

    if(e->button()==Qt::LeftButton)
    {
        trans[0] -= dx;
        trans[1] -= dy;
    }
    else if(e->button()==Qt::RightButton)
    {
        m_rot[0] += dx;
        m_rot[1] -= dy;
        #define clamp(x) x = x > 360.0f ? x-360.0f : x < -360.0f ? x+=360.0f : x
        clamp(m_rot[0]);
        clamp(m_rot[1]);
    }

    else if(e->button()==Qt::MiddleButton)
    {

    }

    else
        QString str = "No operation at this point of time...";

    old_pos = new_pos;

    updateGL();
}
void CAirfoilDesigner::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
    {
        zoomFactor /= 0.75;
    }
    else if(e->delta() <= 0)
    {
        zoomFactor *= 0.75;
    }

    updateGL();
}

void CAirfoilDesigner::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); 
}

void CAirfoilDesigner::resizeGL(int w, int h)
{
    glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(xMin-100, xMax+100, yMax+100, yMin-100, -5.0, 5.0);
}

void CAirfoilDesigner::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);


    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glOrtho(xMin-100, xMax+100, yMax+100, yMin-100, -5.0, 5.0);

    glTranslatef(trans[0], trans[1], 0.0f);
    glTranslatef(_cx, _cy, _cz);
    glScalef(zoomFactor, zoomFactor, zoomFactor);
    glTranslatef(-_cx, -_cy, -_cz);

/*  glBegin(GL_QUADS);
    glPointSize(4.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(xMin-3, yMin-3);
    glVertex2f(xMax+3, yMin-3);
    glVertex2f(xMax+3, yMax+3);
    glVertex2f(xMin-3, yMax+3);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    if(ifDraw) {
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    for(int i=0; i<nAnchors; i++)
    {
        glVertex2f(_anchorXu[i], _anchorYu[i]);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    for(int i=0; i<nAnchors; i++)
    {
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
        glVertex2f(_knotsXl[i], _knotsYl[i]);
    }
    glEnd();
    }

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glFlush();
}

void CAirfoilDesigner::set_anchors(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
     nAnchors = n;
    _anchorXu = x1; _anchorYu = y1; _anchorZu = z1;
    _anchorXl = x2; _anchorYl = y2; _anchorZl = z2;
    if(!ifDraw)
    ifDraw = !ifDraw;

    float *x = new float[n*2];
    int i = 0;
    for(i=0; i<(n); i++)
        x[i] = x1[i];
    for(i=n; i<(n*2); i++)
        x[i] = x2[i-n];

    float *y = new float[n*2];
    i = 0;
    for(i=0; i<(n); i++)
        y[i] = y1[i];
    for(i=n; i<(n*2); i++)
        y[i] = y2[i-n];

    selectionSort(x, n);
    selectionSort(y, n*2);

    xMin = x[0]; xMax = x[n*2-1];
    yMax = y[0]; yMin = y[n*2-1];

    _cx = xMin + ((xMax - xMin)/2.0);
    _cy = yMin + ((yMax - yMin)/2.0);
    _cz = 0.0;
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

void CAirfoilDesigner::selectionSort(float arr[], int size)
{
    int indexOfMin, pass, j;

    for(pass=0; pass<size-1; pass++)
    {
        indexOfMin = pass;

        for(j=pass+1; j<size; j++)
            if(arr[j] < arr[indexOfMin])
                indexOfMin = j;

        std::swap(arr[pass], arr[indexOfMin]);
    }
}
