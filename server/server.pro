include(../nymea.pri)

TARGET = nymead
TEMPLATE = app

INCLUDEPATH += ../libnymea ../libnymea-core $$top_builddir

target.path = $$[QT_INSTALL_PREFIX]/bin
INSTALLS += target

QT += sql websockets network

greaterThan(QT_MAJOR_VERSION, 5) {
    QT += core5compat
} else {
    QT += xml
}

CONFIG += link_pkgconfig
PKGCONFIG += nymea-zigbee nymea-mqtt

LIBS += -L$$top_builddir/libnymea/ -lnymea \
        -L$$top_builddir/libnymea-core -lnymea-core

# Add rpath for easy running from the build dir, unless explicitly disabled
!norpath: {
    message("Adding rpath to nymead binary")
    LIBS += -Wl,-rpath ../libnymea/
    LIBS += -Wl,-rpath ../libnymea-core/
}

# Server files
include(qtservice/qtservice.pri)

SOURCES += main.cpp \
    nymeaservice.cpp \
    nymeaapplication.cpp

HEADERS += \
    nymeaservice.h \
    nymeaapplication.h


! CONFIG(disabledbus) {
    QT += dbus
}

! CONFIG(disablebt) {
    QT += bluetooth
}

! CONFIG (disabletunnelproxy) {
    LIBS += -lnymea-remoteproxyclient
}
