#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T13:04:25
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InkjetPlumber
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    preferencesdialog.cpp \
    maintenancejob.cpp \
    autoupdater.cpp \
    aboutdialog.cpp

HEADERS += mainwindow.h \
    version.h \
    preferencesdialog.h \
    maintenancejob.h \
    autoupdater.h \
    aboutdialog.h

FORMS += mainwindow.ui \
    preferencesdialog.ui \
    aboutdialog.ui

RESOURCES += \
    InkjetPlumber.qrc

ICON = InkjetPlumber.icns

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
    DEFINES += INKJETPLUMBER_DEBUG
} else {
    DESTDIR = build/release
    DEFINES += INKJETPLUMBER_RELEASE
}

OBJECTS_DIR = $${DESTDIR}/.generatedfiles
MOC_DIR = $${DESTDIR}/.generatedfiles
RCC_DIR = $${DESTDIR}/.generatedfiles
UI_DIR = $${DESTDIR}/.generatedfiles

mac {
    HEADERS += \
        cocoainitializer.h \
        sparkleautoupdater.h
    OBJECTIVE_SOURCES += \
        cocoainitializer.mm \
        sparkleautoUpdater.mm
    BUNDLE_DIR = $$quote($$DESTDIR/$${TARGET}.app)
    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_OBJECTIVE_CFLAGS_RELEASE = $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS  = -Wl,-rpath,@executable_path/../Frameworks
    QMAKE_POST_LINK += ditto -v \"$${PWD}/Sparkle/build/Release/Sparkle.framework/\" \"$${BUNDLE_DIR}/Contents/Frameworks/Sparkle.framework/\" 2>&1;
    QMAKE_POST_LINK += /Users/jefft/bin/codesign_app_bundle \"$${BUNDLE_DIR}\" 2>&1
    INCLUDEPATH += $$PWD/Sparkle/build/Release/Sparkle.framework/Headers/
    LIBS += -F$${PWD}/Sparkle/build/Release/
    LIBS += -framework Sparkle -framework AppKit
    QMAKE_INFO_PLIST = InkjetPlumber.plist
    plist.target = Info.plist
    plist.depends = InkjetPlumber.plist "$${DESTDIR}/$${TARGET}.app/Contents/Info.plist"
    plist.commands = $(DEL_FILE) \"$${DESTDIR}/$${TARGET}.app/Contents/Info.plist\" $$escape_expand(\n\t) \
    $(COPY_FILE) InkjetPlumber.plist \"$${DESTDIR}/$${TARGET}.app/Contents/Info.plist\"
    QMAKE_EXTRA_TARGETS = plist
    PRE_TARGETDEPS += $$plist.target
}
