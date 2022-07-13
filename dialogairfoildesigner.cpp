#include "dialogairfoildesigner.h"
#include "ui_dialogairfoildesigner.h"
#include <QFileDialog>
#include <QTextStream>
#include <math.h>
#include <QSplitter>

int DialogAirfoilDesigner::i = 0;
int DialogAirfoilDesigner::N = 0;
DialogAirfoilDesigner::DialogAirfoilDesigner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAirfoilDesigner)
{


    ui->setupUi(this);
    connect(ui->pushButton_READ_ANCHORS, SIGNAL(clicked()), this, SLOT(push_read_anchors()));
    connect(ui->pushButton_APPLY_READ_ANCHORS, SIGNAL(clicked()), this, SLOT(push_apply_anchors()));
    connect(ui->pushButton_APPLY_FULL, SIGNAL(clicked()), this, SLOT(push_apply_full()));

    cairfoil_designer = new CAirfoilDesigner;
    ui->scrollArea_GRAPHICS_WINDOW->setWidget(cairfoil_designer);
    QSplitter *splitter1 = new QSplitter;
    splitter1->addWidget(ui->scrollArea_CONTROL_WIDGET);
    splitter1->addWidget(ui->widget_SCREEN);
    /////////////////////////////////////////////////////////////////////////////////////

    QSplitter *splitter2 = new QSplitter;
    splitter2->setOrientation(Qt::Vertical);
    splitter2->addWidget(ui->scrollArea_GRAPHICS_WINDOW);
    splitter2->addWidget(ui->textEdit_CONSOLE_WINDOW);
    ui->verticalLayout->addWidget(splitter2);
    ui->horizontalLayout->addWidget(splitter1);

    N = -1;
}

DialogAirfoilDesigner::~DialogAirfoilDesigner()
{
    delete ui;
}

void DialogAirfoilDesigner::push_apply_full()
{
    float chord = ui->lineEdit_CHORD_LENGTH->text().toFloat();
    float camber = ui->lineEdit_CAMBER->text().toFloat();
    float maxThickness = ui->lineEdit_MAX_THICKNESS->text().toFloat();
    int order = ui->lineEdit_ORDER->text().toInt();
    nKnots = ui->lineEdit_NO_KNOTS->text().toInt();

    xMin = 0.0;
    xMax = chord;
    yMax =  maxThickness/2.0 + camber;
    yMin = -(maxThickness/2.0) + camber;

    cairfoil_designer->set_domain(xMin-5.0, xMax+5.0, yMin-5.0, yMax+5.0);

    ////////////////////////////////////////////////////////////////////////////////
    //number of anchors
    //if control points and anchors are not read from file...

    if(N==-1)
    {
                N = 3;
                xAnchorU=nullptr, yAnchorU=nullptr, zAnchorU=nullptr;
                xAnchorL=nullptr, yAnchorL=nullptr, zAnchorL=nullptr;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(N) + "\n");
                xAnchorU = new float[N];
                yAnchorU = new float[N];
                zAnchorU = new float[N];

                xAnchorL = new float[N];
                yAnchorL = new float[N];
                zAnchorL = new float[N];

                xAnchorU[0] = 0.0;
                yAnchorU[0] = 0.0;
                zAnchorU[0] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorU[0]) + " " + QString::number(yAnchorU[0]) + " " + QString::number(zAnchorU[0]) + "\n");

                xAnchorU[1] = chord * .3;
                yAnchorU[1] = camber + (maxThickness/2.0);
                zAnchorU[1] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorU[1]) + " " + QString::number(yAnchorU[1]) + " " + QString::number(zAnchorU[1]) + "\n");

                xAnchorU[2] = chord;
                yAnchorU[2] = 0.0;
                zAnchorU[2] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorU[2]) + " " + QString::number(yAnchorU[2]) + " " + QString::number(zAnchorU[2]) + "\n");


                xAnchorL[0] = 0.0;
                yAnchorL[0] = 0.0;
                zAnchorL[0] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorL[0]) + " " + QString::number(yAnchorL[0]) + " " + QString::number(zAnchorL[0]) + "\n");

                xAnchorL[1] = chord * .3;
                yAnchorL[1] = camber - (maxThickness/2.0);
                zAnchorL[1] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorL[1]) + " " + QString::number(yAnchorL[1]) + " " + QString::number(zAnchorL[1]) + "\n");

                xAnchorL[2] = chord;
                yAnchorL[2] = 0.0;
                zAnchorL[2] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorL[2]) + " " + QString::number(yAnchorL[2]) + " " + QString::number(zAnchorL[2]) + "\n");
    }


    /////////////////////////////////////////////////////////////////////////////
    //Enter nKnots, order
    float *t = new float[nKnots];
    float inter_t = 1.0/(float)nKnots;
    for(int i=0; i<nKnots; i++)
    {
        if(i==0)
            t[i] = 0;
        else
            t[i] = t[i-1] + inter_t;
    }

    int *k = new int[N]; //3 values
    for(int m=0; m<N; m++)
        k[m] = m;
    float *nCk = new float[N]; //3 values

    for(i=0; i<N; i++)
    {
        float n1 = fact(N-1);
        float n2 = fact(N-1-k[i]);
        float n3 = fact(k[i]);
        nCk[i] = n1/(n2*n3);
    }

//Upper surfaces
///////////////////////////////////////////////////////////////////////////////////////////
    xu = new  float[nKnots];
    yu = new  float[nKnots];
    zu = new  float[nKnots];
    float basex = 0; float basey = 0; float basez=0;

    ui->textEdit_CONSOLE_WINDOW->append("Airfoil points-Upper:\n");

    for(i=0; i<nKnots; i++)
    {
        basex = 0, basey=0, basez=0;
        xu[i] = 0.0, yu[i] = 0.0, zu[i] = 0.0;
        for(int j=0; j<N; j++)
        {
            basex += nCk[j] * xAnchorU[j];
            basey += nCk[j] * yAnchorU[j];
            //basez += 0;

            xu[i] +=  basex * pow(1-t[i],(N-1)-k[j]) * pow(t[i],k[j]);
            yu[i] +=  basey * pow(1-t[i],(N-1)-k[j]) * pow(t[i],k[j]);
            zu[i] +=  0.0; //basez * pow(1-t[i],(N-1)-k[i]) * pow(t[i],k[i]);
        }
        ui->textEdit_CONSOLE_WINDOW->append(QString::number(xu[i]) + " " + QString::number(yu[i]) + " " + QString::number(zu[i]) + "\n");
    }

//Lower surfaces
////////////////////////////////////////////////////////////////////////////////////////
    xl = new  float[nKnots];
    yl = new  float[nKnots];
    zl = new  float[nKnots];

    ui->textEdit_CONSOLE_WINDOW->append("Airfoil points-Lower:\n");

    for(i=0; i<nKnots; i++)
    {
        basex = 0, basey=0, basez=0;
        xl[i] = 0.0, yl[i] = 0.0, zl[i] = 0.0;
        for(int j=0; j<N; j++)
        {
            basex += nCk[j] * xAnchorL[j];
            basey += nCk[j] * yAnchorL[j];
            //basez += 0;

            xl[i] +=  basex * pow(1-t[i],(N-1)-k[j]) * pow(t[i],k[j]);
            yl[i] +=  basey * pow(1-t[i],(N-1)-k[j]) * pow(t[i],k[j]);
            zl[i] +=  0.0; //basez * pow(1-t[i],(N-1)-k[i]) * pow(t[i],k[i]);
        }
        ui->textEdit_CONSOLE_WINDOW->append(QString::number(xl[i]) + " " + QString::number(yl[i]) + " " + QString::number(zl[i]) + "\n");
    }
/////////////////////////////////////////////////////////////////////////////////////////

    //Draw Airfoil...
    set_anchors();
    set_bezier_knots();
}
void DialogAirfoilDesigner::push_apply_anchors()
{

}
void DialogAirfoilDesigner::push_read_anchors()
{
    xAnchorU=nullptr, yAnchorU=nullptr, zAnchorU=nullptr;
    xAnchorL=nullptr, yAnchorL=nullptr, zAnchorL=nullptr;
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
                                                     ".",
                                                     ("DataAnchors (*.dat)"));
    QFile file(fileName);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          return;
       QTextStream in(&file);
       in >> N;

       ui->textEdit_CONSOLE_WINDOW->append(QString::number(N) + "\n");
       xAnchorU = new float[N];
       yAnchorU = new float[N];
       zAnchorU = new float[N];

       xAnchorL = new float[N];
       yAnchorL = new float[N];
       zAnchorL = new float[N];


       i=0;
       for(i=0; i<N/2; i++)
       {
            in >> xAnchorU[i] >> yAnchorU[i] >> zAnchorU[i];
            ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorU[i]) + " " + QString::number(yAnchorU[i]) + " " + QString::number(zAnchorU[i]) + "\n");
       }

       for(i=0; i<N/2; i++)
       {
            in >> xAnchorL[i] >> yAnchorL[i] >> zAnchorL[i];
            ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorU[i]) + " " + QString::number(yAnchorU[i]) + " " + QString::number(zAnchorU[i]) + "\n");
       }

       file.close();
}

float DialogAirfoilDesigner::fact(int n)
{
        int i;
        unsigned long long fact = 1;
        // shows error if the user enters a negative integer
        if (n < 0)
            printf("Error! Factorial of a negative number doesn't exist.");
        else {
            for (i = 1; i <= n; ++i) {
                fact *= i;
            }

            return fact;
        }      
}

void DialogAirfoilDesigner::set_anchors()
{
    cairfoil_designer->set_anchors(N, xAnchorU, yAnchorU, zAnchorU, xAnchorL, yAnchorL, zAnchorL );
}
void DialogAirfoilDesigner::set_bezier_knots()
{
    cairfoil_designer->set_bezier_knots(nKnots, xu, yu, zu, xl, yl, zl );
}
