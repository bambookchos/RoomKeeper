#-------------------------------------------------
#
# Project created by QtCreator 2018-07-08T14:05:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoomKeeper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    secondui.cpp \
    login.cpp \
    personal/personal.cpp \
    personal/personal_edit.cpp \
    personal/personal_model.cpp \
    character/character_add.cpp \
    booking/booking_new.cpp \
    customer/customer_choose.cpp \
    customer/customer_add.cpp \
    booking/booking_finish.cpp \
    customer/customer_editor.cpp \
    reservations/reservations_table.cpp \
    room.cpp \
    character/character_edit.cpp \
    character/character_table.cpp \
    room/room_edit.cpp \
    room/room_add.cpp \
    booking/filter_row.cpp \
    reservations/reservations_edit.cpp \
    reservations/reservation_redactor.cpp \
    reservations/reservation_choose.cpp

HEADERS += \
        mainwindow.h \
    secondui.h \
    login.h \
    personal/personal.h \
    personal/personal_edit.h \
    personal/personal_model.h \
    character/character_add.h \
    booking/booking_new.h \
    customer/customer_choose.h \
    customer/customer_add.h \
    booking/booking_finish.h \
    customer/customer_editor.h \
    reservations/reservations_table.h \
    room.h \
    character/character_edit.h \
    character/character_table.h \
    room/room_edit.h \
    room/room_add.h \
    booking/filter_row.h \
    reservations/reservations_edit.h \
    reservations/reservation_redactor.h \
    reservations/reservation_choose.h

FORMS += \
        mainwindow.ui \
    second.ui \
    login.ui \
    personal/personal.ui \
    personal/personal_edit.ui \
    characteristic.ui \
    character/character_add.ui \
    booking/booking_new.ui \
    customer/customer_choose.ui \
    customer/customer_add.ui \
    booking/booking_finish.ui \
    customer/customer_editor.ui \
    character/character_edit.ui \
    room/room_edit.ui \
    room/room_add.ui \
    reservations/reservations_edit.ui \
    reservations/reservation_redactor.ui \
    reservations/reservation_choose.ui

    login.ui
QTPLUGIN += QSQLMYSQL

DISTFILES +=

RESOURCES += \
    images.qrc
