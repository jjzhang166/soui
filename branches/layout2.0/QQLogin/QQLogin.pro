######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 21 17:00:01 2014
######################################################################

TEMPLATE = app
TARGET = qqlogin
DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += . \
			   ../utilities/include \
			   ../soui/include \
			   ../components \
			   
dir = ..
include($$dir/common.pri)

CONFIG(debug,debug|release){
	LIBS += utilitiesd.lib souid.lib
}
else{
	LIBS += utilities.lib soui.lib
}

PRECOMPILED_HEADER = stdafx.h

# Input
HEADERS += MainDlg.h \
           resource.h \
           ../controls.extend/STurn3DView.h \
           ../controls.extend/image3d/3dlib.h \
           ../controls.extend/image3d/3dmatrix.h \
           ../controls.extend/image3d/3dTransform.h \
           ../controls.extend/image3d/PerspectiveTransform.h
SOURCES += MainDlg.cpp \
           QQLogin.cpp \
           ../controls.extend/STurn3DView.cpp \
           ../controls.extend/image3d/3dlib.cpp \
           ../controls.extend/image3d/3dmatrix.cpp \
           ../controls.extend/image3d/3dtransform.cpp
           
RC_FILE += qqlogin.rc
