QT       += core gui widgets opengl

TARGET = BestPracticesGLQt
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    mainwidget_supplement_1.cpp \
    mainwidget_supplement_2.cpp \
    mainwidget_supplement_3.cpp \
    mainwindow.cpp

HEADERS += \
    mainwidget.h \
    mainwidget_supplement_1.h \
    mainwidget_supplement_2.h \
    mainwidget_supplement_3.h \
    mainwindow.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

OTHERS += \
airfoil_data_30307.txt \
Airfoildata.txt \
gl-widget-mouse-code.txt \
weather_data.txt

LIBS += -lOPENGL32 -lglu32

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=

FORMS += \
    mainwindow.ui
