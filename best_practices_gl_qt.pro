QT       += core gui widgets

TARGET = BestPracticesGLQt
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwidget.cpp

HEADERS += \
    mainwidget.h

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
