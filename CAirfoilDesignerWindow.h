#ifndef CAIRFOILDESIGNERWINDOW_H
#define CAIRFOILDESIGNERWINDOW_H

#include <QGLWidget>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLBuffer>
#include <QImage>
#include <QOpenGLFunctions>
#include <QTimer>

class CAirfoilDesigner : public QGLWidget
{
    Q_OBJECT

public:
    explicit CAirfoilDesigner(QWidget *parent = 0);
    ~CAirfoilDesigner();
    void drawFuselage(int n, float *xr, float *yr, float *zr, float *xl, float *yl, float *zl);
    void set_ifDrawAnchors();
    void set_ifDrawKnots();
    void set_ifDrawHGrid();
    void generateGridOverAirfoil(float n);
    void selectionSort(float arr[], int size);
    void set_anchors(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2);
    void set_bezier_knots(int n, float *x1, float *y1, float *z1, float *x2, float *y2, float *z2);
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    static bool ifDrawFuselage;
    int _nSlicesFuselage;
    float *xRightFuselage, *yRightFuselage, *zRightFuselage;
    float *xLeftFuselage, *yLeftFuselage, *zLeftFuselage;
    static bool ifDrawAnchors;
    static bool ifDrawKnots;
    static bool ifDrawHGrid;
    int nHGrid;
    float inter;
    float * xHyperbolic, *yHyperbolic, *chi, *eta;
    float _cx, _cy, _cz;
    QPointF old_pos, new_pos;
    float trans[3];
    float dx, dy;
    float zoomFactor;
    float xMin, xMax, yMin, yMax;
    int nAnchors, nKnots;
    float *_anchorXu, *_anchorYu, *_anchorZu, *_anchorXl, *_anchorYl, *_anchorZl;
    float *_knotsXu, *_knotsYu, *_knotsZu, *_knotsXl, *_knotsYl, *_knotsZl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Aircraft
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    GLfloat *ctrlX, *ctrlY, *ctrlZ;
    GLfloat **wingX, **wingY, **wingZ;
    GLfloat **fuslgX, **fuslgY, **fuslgZ;
    GLfloat **tailX, **tailY, **tailZ;
    GLfloat **finX, **finY, **finZ;
    GLfloat angles[9];
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QMatrix4x4 projection;
    GLint widthImg, heightImg;
    GLint *indices;
    GLfloat *vertices, *colors;
    GLuint list, object, theTorus;
    GLfloat m_rot[3];
    QBasicTimer timer;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
};
#endif // CAIRFOILDESIGNERWINDOW_H
