QT += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++ 17
ICON = icon.png

SOURCES += \
    ../../modules/calculate.c \
    ../../modules/credit_calc.c \
    ../../modules/deposit_calc.c \
    ../../modules/infix_to_postfix.c \
    ../../modules/mini_func.c \
    ../../modules/stack.c \
    credit.cpp \
    deposit.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../modules/modules.h \
    credit.h \
    deposit.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
      credit.ui \
      deposit.ui \
      graph.ui \
      mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Additional configuration for window title and centering
TARGET = SmartCalc

#Enable High DPI scaling
QT_AUTO_SCREEN_SCALE_FACTOR = 1
