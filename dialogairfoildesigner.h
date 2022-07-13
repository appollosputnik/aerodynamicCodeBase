#ifndef DIALOGAIRFOILDESIGNER_H
#define DIALOGAIRFOILDESIGNER_H

#include <QDialog>
#include "CAirfoilDesignerWindow.h"
namespace Ui {
class DialogAirfoilDesigner;
}

class DialogAirfoilDesigner : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAirfoilDesigner(QWidget *parent = nullptr);
    ~DialogAirfoilDesigner();
    float  fact(int n);
private:
    int nKnots;
    static int i;
    static int N;
    float *xu, *yu, *zu, *xl, *yl, *zl;
    float *xAnchorU, *yAnchorU, *zAnchorU, *xAnchorL, *yAnchorL, *zAnchorL;
    Ui::DialogAirfoilDesigner *ui;
    CAirfoilDesigner *cairfoil_designer;
    float xMin, xMax, yMin, yMax;
private slots:
    void set_anchors();
    void set_bezier_knots();
    void push_apply_full();
    void push_apply_anchors();
    void push_read_anchors();

};

#endif // DIALOGAIRFOILDESIGNER_H
