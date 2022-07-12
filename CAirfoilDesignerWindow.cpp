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
CAirfoilDesigner::CAirfoilDesigner(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(10),
    indexBuf(QOpenGLBuffer::IndexBuffer)
{
    m_rot[0] = 0.0;
    m_rot[1] = 0.0;
    m_rot[2] = 0.0;

    timerEvent(0);
    update();
}

CAirfoilDesigner::~CAirfoilDesigner()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    arrayBuf.destroy();
    indexBuf.destroy();
    doneCurrent();
}

void CAirfoilDesigner::makeCube()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
//! [1]
//!
}

void CAirfoilDesigner::makeCheckImage(void)
{
    int i, j, c;

    for(i=0; i<checkImageHeight; i++) {
        for(j=0; j<checkImageWidth; j++)
        {
            c = ((((i&0x8==0)^((j&0x8)))==0))*255;
        }
    }
}

//! [0]
void CAirfoilDesigner::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void CAirfoilDesigner::idleFunc()
{
    QVector2D diff = QVector2D(5,-3);
    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;

    update();
}

void CAirfoilDesigner::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void CAirfoilDesigner::timerEvent(QTimerEvent *)
{

//    Decrease angular speed (friction)
      //angularSpeed *= 0.99;
      angularSpeed = 3.99;
/*
    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        // Request an update
        update();
    }

*/
      // Update rotation
      rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
      // Request an update
      update();

 /*   m_rot[0] =  15.50f;
    m_rot[1] = -15.50f;
    //m_rot[0] += .009;
    //m_rot[1] -= .009;
    #define clamp(x) x = x > 360.0f ? x-360.0f : x < -360.0f ? x+=360.0f : x
    clamp(m_rot[0]);
    clamp(m_rot[1]);
    update(); */

//! [1]
}

/* Draw a torus */
void CAirfoilDesigner::torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * (double)M_PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}

void CAirfoilDesigner::LoadGLTextures( const char * name )
{
    QImage img;

    if(!img.load("cube.png")){
        //std::cerr << "ERROR in loading image" << std::endl;
    }
/*
    QImage t = QGLWidget::convertToGLFormat(img);
    int wInter = t.width();
    int hInter = t.height();
    int n = 0;
    glGenTextures(6, texName4);

    for(int j=0; j<2; j++)
    {
        for(int i=0; i<3; i++)
        {
            n = i*j+i+j;
            glBindTexture(GL_TEXTURE_2D, texName4[n]);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, wInter, hInter, 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glBindTexture( GL_TEXTURE_2D, 0 );

       }
        n++;
    }

    */
}


void CAirfoilDesigner::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    timer.start(12, this);
    timerEvent(nullptr);
    update();
    idleFunc();
}

//! [3]
void CAirfoilDesigner::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void CAirfoilDesigner::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void CAirfoilDesigner::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    //glOrtho(-5.0, 5.0, 5.0, -5.0, -5.0, 5.0);
    gluPerspective(27.0, aspect, 1.0, 100.0);
    gluLookAt(0, 0, -10.0, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    timerEvent(nullptr);
    update();
}

//! [5]
void CAirfoilDesigner::drawCube()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    vertices =new GLfloat[72] {
        // Vertex data for face 0
        (-3.0f, -3.0f,  3.0f),  // v0
        ( 3.0f, -3.0f,  3.0f), // v1
        (-3.0f,  3.0f,  3.0f),  // v2
       ( 3.0f,  3.0f,  3.0f), // v3

        // Vertex data for face 1
       ( 3.0f, -3.0f,  3.0f), // v4
      ( 3.0f, -3.0f, -3.0f), // v5
     ( 3.0f,  3.0f,  3.0f), // v6
    ( 3.0f,  3.0f, -3.0f), // v7

        // Vertex data for face 2
   ( 3.0f, -3.0f, -3.0f), // v8
  (-3.0f, -3.0f, -3.0f), // v9
  ( 3.0f,  3.0f, -3.0f), // v10
   (-3.0f,  3.0f, -3.0f), // v11

        // Vertex data for face 3
(-3.0f, -3.0f, -3.0f), // v12
     (-3.0f, -3.0f,  3.0f), // v13
      (-3.0f,  3.0f, -3.0f), // v14
   (-3.0f,  3.0f,  3.0f), // v15

        // Vertex data for face 4
  (-3.0f, -3.0f, -3.0f), // v16
    ( 3.0f, -3.0f, -3.0f), // v17
   (-3.0f, -3.0f,  3.0f), // v18
    ( 3.0f, -3.0f,  3.0f), // v19

        // Vertex data for face 5
  (-3.0f,  3.0f,  3.0f), // v20
   ( 3.0f,  3.0f,  3.0f), // v21
     (-3.0f,  3.0f, -3.0f), // v22
  ( 3.0f,  3.0f, -3.0f), // v23
    };

   indices = new GLint[24] {

        0,1,2,
        2,0,3,
        3,4,2,
        2,5,4,
        4,7,5,
        5,6,7,
        7,0,1,
        1,6,7

    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
   colors = new GLfloat [72] {
         0.0, 1.0, 0.0 ,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         0.0, 1.0, 0.0, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         0.0, 1.0, 0.0, // 0Face 2 - triangle strip ( v8,  v9, v10, v11)
        0.0, 1.0, 0.0, // Face 3 - triangle strip (v12, v13, v14, v15)
        0.0, 1.0, 0.0, // Face 4 - triangle strip (v16, v17, v18, v19)
        0.0, 1.0, 0.0 ,     // Face 5 - triangle strip (v20, v21, v22, v23)
           0.0, 1.0, 0.0 ,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
           0.0, 1.0, 0.0, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
           0.0, 1.0, 0.0, // 0Face 2 - triangle strip ( v8,  v9, v10, v11)
          0.0, 1.0, 0.0, // Face 3 - triangle strip (v12, v13, v14, v15)
          0.0, 1.0, 0.0, // Face 4 - triangle strip (v16, v17, v18, v19)
          0.0, 1.0, 0.0   ,   // Face 5 - triangle strip (v20, v21, v22, v23)
           0.0, 1.0, 0.0 ,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
           0.0, 1.0, 0.0, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
           0.0, 1.0, 0.0, // 0Face 2 - triangle strip ( v8,  v9, v10, v11)
          0.0, 1.0, 0.0, // Face 3 - triangle strip (v12, v13, v14, v15)
          0.0, 1.0, 0.0, // Face 4 - triangle strip (v16, v17, v18, v19)
          0.0, 1.0, 0.0 ,     // Face 5 - triangle strip (v20, v21, v22, v23)
             0.0, 1.0, 0.0 ,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
             0.0, 1.0, 0.0, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
             0.0, 1.0, 0.0, // 0Face 2 - triangle strip ( v8,  v9, v10, v11)
            0.0, 1.0, 0.0, // Face 3 - triangle strip (v12, v13, v14, v15)
            0.0, 1.0, 0.0, // Face 4 - triangle strip (v16, v17, v18, v19)
            0.0, 1.0, 0.0   ,   // Face 5 - triangle strip (v20, v21, v22, v23)
    };
   //theTorus = glGenLists (1);
   //glNewList(theTorus, GL_COMPILE);
   //torus(8, 25);
   //glEndList();

   //glEnableClientState(GL_VERTEX_ARRAY);
   //glEnableClientState(GL_NORMAL_ARRAY);
   //glEnableClientState(GL_COLOR_ARRAY);
   //glVertexPointer(3,GL_FLOAT,72*sizeof(GLfloat),vertices);
   //glColorPointer (3,GL_FLOAT,72*sizeof(GLfloat),colors);
   //glDrawArrays(GL_TRIANGLES, 0, *indices);
   //glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_SHORT, 0);
   //glDisableClientState(GL_COLOR_ARRAY);
   //glDisableClientState(GL_NORMAL_ARRAY);
   //glDisableClientState(GL_VERTEX_ARRAY);
}


void CAirfoilDesigner::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Drawing anchors
    for(int i=0; i<nAnchors; i++)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(_anchorXu[i], _anchorYu[i], _anchorZu[i]);
        glVertex3f(_anchorXl[i], _anchorYl[i], _anchorZl[i]);
        glEnd();
    }

    for(int i=0; i<nKnots; i++)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(_knotsXu[i], _knotsYu[i], _knotsZu[i]);
        glVertex3f(_knotsXl[i], _knotsYl[i], _knotsZl[i]);
        glEnd();
    }

    glFlush();
}

void CAirfoilDesigner::set_anchors(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
     nAnchors = n;
    _anchorXu = x1; _anchorYu = y1; _anchorZu = z1;
    _anchorXl = x2; _anchorYl = y2; _anchorZl = z2;
}
void CAirfoilDesigner::set_bezier_knots(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2)
{
     nKnots = n;
    _knotsXu = x1; _knotsYu = y1; _knotsZu = z1;
    _knotsXl = x2; _knotsYl = y2; _knotsZl = z2;
}
