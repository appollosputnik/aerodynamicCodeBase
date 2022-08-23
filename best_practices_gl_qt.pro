QT       += core gui widgets opengl

TARGET = BestPracticesGLQt
TEMPLATE = app

INCLUDEPATH += D:\qwt-6.1.4\src

SOURCES += \
    CAirfoilDesignerWindow.cpp \
    dialogairfoildesigner.cpp \
    dialogterrain.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwidget_supplement_1.cpp \
    mainwidget_supplement_2.cpp \
    mainwidget_supplement_3.cpp \
    mainwindow.cpp \
    mainwindow_.cpp \
    scrollzoomer.cpp \
    scrollbar.cpp \
    incrementalplot.cpp \
    randomplot.cpp

HEADERS += \
    CAirfoilDesignerWindow.h \
    dialogairfoildesigner.h \
    dialogterrain.h \
    mainwidget.h \
    mainwidget_supplement_1.h \
    mainwidget_supplement_2.h \
    mainwidget_supplement_3.h \
    mainwindow.h \
    mainwindow_.h \
    scrollzoomer.h \
    scrollbar.h \
    incrementalplot.h \
    randomplot.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

OTHERS += \
airfoil_data_30307.txt \
Airfoildata.txt \
gl-widget-mouse-code.txt \
weather_data.txt

LIBS += -LD:\qwt-6.1.4\lib -lqwt -lOPENGL32 -lglu32

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=

FORMS += \
    dialogairfoildesigner.ui \
    dialogterrain.ui \
    mainwindow.ui
