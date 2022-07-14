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
    ui(new Ui::DialogAirfoilDesigner),
    xu(NULL),
    yu(NULL),
    zu(NULL),
    xl(NULL),
    yl(NULL),
    zl(NULL),
    xu_(NULL),
    yu_(NULL),
    zu_(NULL),
    xl_(NULL),
    yl_(NULL),
    zl_(NULL),
    xAnchorU(NULL),
    yAnchorU(NULL),
    zAnchorU(NULL),
    xAnchorL(NULL),
    yAnchorL(NULL),
    zAnchorL(NULL),
    xAnchorU_(NULL),
    yAnchorU_(NULL),
    zAnchorU_(NULL),
    xAnchorL_(NULL),
    yAnchorL_(NULL),
    zAnchorL_(NULL)
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
    float max_thickness_pos = ui->lineEdit_MAX_THICKNESS_POS->text().toFloat();

    if(N==-1) {
    N = 3;
    if(xAnchorU) {delete [] xAnchorU; xAnchorU=nullptr;}
    if(yAnchorU) {delete [] yAnchorU; yAnchorU=nullptr;}
    if(zAnchorU) {delete [] zAnchorU; zAnchorU=nullptr;}
    if(xAnchorL) {delete [] xAnchorL; xAnchorL=nullptr;}
    if(yAnchorL) {delete [] yAnchorL; yAnchorL=nullptr;}
    if(zAnchorL) {delete [] zAnchorL; zAnchorL=nullptr;}

    ui->textEdit_CONSOLE_WINDOW->append(QString::number(N) + "\n");
    xAnchorU = new float[N];
    yAnchorU = new float[N];
    zAnchorU = new float[N];

    xAnchorL = new float[N];
    yAnchorL = new float[N];
    zAnchorL = new float[N];


    xAnchorU_ = new float[N];
    yAnchorU_ = new float[N];
    zAnchorU_ = new float[N];

    xAnchorL_ = new float[N];
    yAnchorL_ = new float[N];
    zAnchorL_ = new float[N];
    xMin = 0.0;
    xMax = chord;
    yMax =  maxThickness/2.0 + camber;
    yMin = -(maxThickness/2.0) + camber;
                xAnchorU[0] = 0.0;
                yAnchorU[0] = 0.0;
                zAnchorU[0] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorU[0]) + " " + QString::number(yAnchorU[0]) + " " + QString::number(zAnchorU[0]) + "\n");

                xAnchorU[1] = max_thickness_pos;
                yAnchorU[1] = (camber + (maxThickness/2.0));
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

                xAnchorL[1] = max_thickness_pos;
                yAnchorL[1] = (camber - (maxThickness/2.0));
                zAnchorL[1] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorL[1]) + " " + QString::number(yAnchorL[1]) + " " + QString::number(zAnchorL[1]) + "\n");

                xAnchorL[2] = chord;
                yAnchorL[2] = 0.0;
                zAnchorL[2] = 0.0;
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xAnchorL[2]) + " " + QString::number(yAnchorL[2]) + " " + QString::number(zAnchorL[2]) + "\n");

                for(i=0; i<N; i++)
                {

                    xAnchorU_[i] = xAnchorU[N-1-i];
                    yAnchorU_[i] = yAnchorU[N-1-i];
                    zAnchorU_[i] = zAnchorU[N-1-i];

                    xAnchorL_[i] = xAnchorL[N-1-i];
                    yAnchorL_[i] = yAnchorL[N-1-i];
                    zAnchorL_[i] = zAnchorL[N-1-i];
                }

                for(i=0; i<N; i++)
                {
                    yAnchorU[i] *= -1.0;
                    yAnchorL[i] *= -1.0;
                }



                /////////////////////////////////////////////////////////////////////////////
                //Enter nKnots, order
                float *t = new float[nKnots];
                float inter_t = 1.0/((float)nKnots-1);
                for(i=0; i<nKnots; i++)
                {
                    if(i==0)
                        t[i] = 0;
                    else
                        t[i] = t[i-1] + inter_t;
                }

                int *k = new int[N]; //3 values
                for(int m=0; m<N; m++)
                    k[m] = m+1;
                float *nCk = new float[N]; //3 values

                for(i=0; i<N; i++)
                {
                    float n1 = fact(N);
                    float n2 = fact(N-k[i]);
                    float n3 = fact(k[i]);
                    nCk[i] = n1/(n2*n3);
                }
///////////////////////////////////////////////////////////////////////////

    if(xu) {delete [] xu; xu = nullptr;}  if(xu_) {delete [] xu_; xu_ = nullptr;}
    if(yu) {delete [] yu; yu = nullptr;}  if(yu_) {delete [] yu_; yu_ = nullptr;}
    if(zu) {delete [] zu; zu = nullptr;}  if(zu_) {delete [] yu_; zu_ = nullptr;}


////////////////////////////////////////////////////////////////////////////////


    //Upper surfaces
                ///////////////////////////////////////////////////////////////////////////////////////////
                    xu = new  float[nKnots], xu_ = new  float[nKnots];
                    yu = new  float[nKnots], yu_ = new  float[nKnots];
                    zu = new  float[nKnots], zu_ = new  float[nKnots];
                    float basex = 0; float basey = 0; float basez=0;

                    ui->textEdit_CONSOLE_WINDOW->append("Airfoil points-Upper:\n");

                    for(i=0; i<nKnots; i++)
                    {
                        basex = 0, basey=0, basez=0;
                        xu[i] = 0.0, yu[i] = 0.0, zu[i] = 0.0;
                        for(int j=0; j<N; j++)
                        {
                            basex += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * xAnchorU[j];
                            basey += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * yAnchorU[j];
                            //basez += 0;

                            xu[i] +=  basex;
                            yu[i] +=  basey;
                            zu[i] +=  0.0; //basez * pow(1-t[i],(N-1)-k[i]) * pow(t[i],k[i]);
                        }
                        ui->textEdit_CONSOLE_WINDOW->append(QString::number(xu[i]) + " " + QString::number(yu[i]) + " " + QString::number(zu[i]) + "\n");
                    }

                    for(i=0; i<nKnots; i++)
                    {
                        xu_[i] = (xu[i] + (xu[nKnots-1] - xu[nKnots-1-i]))/2.0;
                        yu_[i] = yu[nKnots-1-i];
                        zu_[i] = zu[nKnots-1-i];
                    }



    //Lower surfaces
                ////////////////////////////////////////////////////////////////////////////////////////
                    xl = new  float[nKnots], xl_ = new  float[nKnots];
                    yl = new  float[nKnots], yl_ = new  float[nKnots];
                    zl = new  float[nKnots], zl_ = new  float[nKnots];

                    ui->textEdit_CONSOLE_WINDOW->append("Airfoil points-Lower:\n");

                    for(i=0; i<nKnots; i++)
                    {
                        basex = 0, basey=0, basez=0;
                        xl[i] = 0.0, yl[i] = 0.0, zl[i] = 0.0;
                        for(int j=0; j<N; j++)
                        {
                            basex += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * xAnchorL[j];
                            basey += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * yAnchorL[j];
                            //basez += 0;

                            xl[i] +=  basex;
                            yl[i] +=  basey;
                            zl[i] +=  0.0; //basez * pow(1-t[i],(N-1)-k[i]) * pow(t[i],k[i]);
                        }
                        ui->textEdit_CONSOLE_WINDOW->append(QString::number(xl[i]) + " " + QString::number(yl[i]) + " " + QString::number(zl[i]) + "\n");
                    }

                    for(i=0; i<nKnots; i++)
                    {
                        xl_[i] = (xl[i] + (xl[nKnots-1] - xl[nKnots-1-i]))/2.0;
                        yl_[i] = yl[nKnots-1-i];
                        zl_[i] = zl[nKnots-1-i];
                    }

                    //Draw Airfoil...
                    set_anchors();
                    set_bezier_knots();

                    N=-1;
 }

    else {
            /////////////////////////////////////////////////////////////////////////////
            //Enter nKnots, order
            float *t = new float[nKnots];
            float inter_t = 1.0/((float)nKnots-1);
            for(i=0; i<nKnots; i++)
            {
                if(i==0)
                    t[i] = 0;
                else
                    t[i] = t[i-1] + inter_t;
            }

            int *k = new int[N]; //3 values
            for(int m=0; m<N; m++)
                k[m] = m+1;
            float *nCk = new float[N]; //3 values

            for(i=0; i<N; i++)
            {
                float n1 = fact(N);
                float n2 = fact(N-k[i]);
                float n3 = fact(k[i]);
                nCk[i] = n1/(n2*n3);
            }
            if(xu) {
                delete [] xu;
                xu = nullptr;
            }  if(xu_) {delete [] xu_; xu_ = nullptr;}
            if(yu) {delete [] yu; yu = nullptr;}  if(yu_) {delete [] yu_; yu_ = nullptr;}
            if(zu) {delete [] zu; zu = nullptr;}  if(zu_) {delete [] yu_; zu_ = nullptr;}
        //Upper surfaces
        ///////////////////////////////////////////////////////////////////////////////////////////
            xu = new  float[nKnots], xu_ = new  float[nKnots];
            yu = new  float[nKnots], yu_ = new  float[nKnots];
            zu = new  float[nKnots], zu_ = new  float[nKnots];
            float basex = 0; float basey = 0; float basez=0;

            ui->textEdit_CONSOLE_WINDOW->append("Airfoil points-Upper:\n");

            for(i=0; i<nKnots; i++)
            {
                basex = 0, basey=0, basez=0;
                xu[i] = 0.0, yu[i] = 0.0, zu[i] = 0.0;
                for(int j=0; j<N; j++)
                {
                    basex += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * xAnchorU[j];
                    basey += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * yAnchorU[j];
                    //basez += 0;

                    xu[i] +=  basex;
                    yu[i] +=  basey;
                    zu[i] +=  0.0; //basez * pow(1-t[i],(N-1)-k[i]) * pow(t[i],k[i]);
                }
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xu[i]) + " " + QString::number(yu[i]) + " " + QString::number(zu[i]) + "\n");
            }

            for(i=0; i<nKnots; i++)
            {
                xu_[i] = (xu[i] + (xu[nKnots-1] - xu[nKnots-1-i]))/2.0;
                yu_[i] = yu[nKnots-1-i];
                zu_[i] = zu[nKnots-1-i];
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xu_[i]) + " " + QString::number(yu_[i]) + " " + QString::number(zu_[i]) + "\n");
            }
        //Lower surfaces
        ////////////////////////////////////////////////////////////////////////////////////////
            xl = new  float[nKnots], xl_ = new  float[nKnots];
            yl = new  float[nKnots], yl_ = new  float[nKnots];
            zl = new  float[nKnots], zl_ = new  float[nKnots];

            ui->textEdit_CONSOLE_WINDOW->append("Airfoil points-Lower:\n");

            for(i=0; i<nKnots; i++)
            {
                basex = 0, basey=0, basez=0;
                xl[i] = 0.0, yl[i] = 0.0, zl[i] = 0.0;
                for(int j=0; j<N; j++)
                {
                    basex += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * xAnchorL[j];
                    basey += nCk[j] * pow(1-t[i],(N)-k[j]) * pow(t[i],k[j]) * yAnchorL[j];
                    //basez += 0;

                    xl[i] +=  basex;
                    yl[i] +=  basey;
                    zl[i] +=  0.0; //basez * pow(1-t[i],(N-1)-k[i]) * pow(t[i],k[i]);
                }
                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xl[i]) + " " + QString::number(yl[i]) + " " + QString::number(zl[i]) + "\n");
            }

            for(i=0; i<nKnots; i++)
            {
                xl_[i] = (xl[i] + (xl[nKnots-1] - xl[nKnots-1-i]))/2.0;
                yl_[i] = yl[nKnots-1-i];
                zl_[i] = zl[nKnots-1-i];

                ui->textEdit_CONSOLE_WINDOW->append(QString::number(xl_[i]) + " " + QString::number(yl_[i]) + " " + QString::number(zl_[i]) + "\n");

            }
            //Draw Airfoil...
            set_anchors();
            set_bezier_knots();
            }
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
    cairfoil_designer->set_bezier_knots(nKnots, xu_, yu_, zu, xl_, yl_, zl );
}
