QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../smart_calc_controller.c \
    ../modules/calculate.c \
    ../modules/deposit_calc.c \
    ../modules/input_validation.c \
    ../modules/loan_calc.c \
    ../modules/shunting_yard.c \
    ../modules/stack.c \
    ../modules/tokens_devider.c \
    about.cpp \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \
    qcustomplot.cpp \
    rpn.cpp

HEADERS += \
    ../smart_calc_controller.h \
    ../modules/headers/calculate.h \
    ../modules/headers/deposit_calc.h \
    ../modules/headers/input_validation.h \
    ../modules/headers/loan_calc.h \
    ../modules/headers/shunting_yard.h \
    ../modules/headers/stack.h \
    ../modules/headers/tokens_devider.h \
    about.h \
    credit.h \
    deposit.h \
    mainwindow.h \
    plot.h \
    qcustomplot.h \
    rpn.h

FORMS += \
    about.ui \
    credit.ui \
    deposit.ui \
    mainwindow.ui \
    plot.ui \
    rpn.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc \
    resourses.qrc

DISTFILES +=
