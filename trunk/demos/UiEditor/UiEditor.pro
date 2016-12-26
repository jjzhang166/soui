######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 23 19:29:41 2014
######################################################################

TEMPLATE = app
TARGET = UiEditor

INCLUDEPATH += . \
		../../utilities/include \
		../../soui/include \
		../../components \
		../../config \
		../../controls.extend \


dir = ../..
include($$dir/common.pri)

CONFIG(debug,debug|release){
	LIBS += utilitiesd.lib souid.lib
}
else{
	LIBS += utilities.lib soui.lib
}

PRECOMPILED_HEADER = stdafx.h
RC_FILE += uieditor.rc

SOURCES+=../../controls.extend/image3d/3dlib.cpp
SOURCES+=../../controls.extend/image3d/3dmatrix.cpp
SOURCES+=../../controls.extend/image3d/3dtransform.cpp
SOURCES+=../../controls.extend/ExtendSkins.cpp
SOURCES+=../../controls.extend/imre/ImgProvider.cpp
SOURCES+=../../controls.extend/imre/RichEditObj.cpp
SOURCES+=../../controls.extend/imre/RichEditObjFactory.cpp
SOURCES+=../../controls.extend/imre/RichEditOleBase.cpp
SOURCES+=../../controls.extend/imre/RichEditOleCallback.cpp
SOURCES+=../../controls.extend/imre/RichEditOleCtrls.cpp
SOURCES+=../../controls.extend/SAnimImg.cpp
SOURCES+=../../controls.extend/SButtonEx.cpp
SOURCES+=../../controls.extend/SChromeTabCtrl.cpp
SOURCES+=../../controls.extend/SFreeMoveWindow.cpp
SOURCES+=../../controls.extend/gif/SGifPlayer.cpp
SOURCES+=../../controls.extend/SImageEx.cpp
SOURCES+=../../controls.extend/SImageMaskWnd.cpp
SOURCES+=../../controls.extend/SImagePlayer.cpp
SOURCES+=../../controls.extend/imre/SImRichedit.cpp
SOURCES+=../../controls.extend/gif/SSkinAPNG.cpp
SOURCES+=../../controls.extend/gif/SSkinGif.cpp
SOURCES+=../../controls.extend/SSkinMutiFrameImg.cpp
SOURCES+=../../controls.extend/SSplitBar.cpp
SOURCES+=../../controls.extend/STabCtrl2.cpp
SOURCES+=../../controls.extend/SText.cpp
SOURCES+=../../controls.extend/STurn3DView.cpp
SOURCES+=../../controls.extend/SScrollText.cpp
SOURCES+=../../controls.extend/image3d/3dlib.h
SOURCES+=../../controls.extend/image3d/3dmatrix.h
SOURCES+=../../controls.extend/image3d/3dTransform.h
SOURCES+=./DesignerView.cpp
SOURCES+=./DlgAbout.cpp
SOURCES+=./DlgCreatePro.cpp
SOURCES+=./DlgInput.cpp
SOURCES+=./DlgNewLayout.cpp
SOURCES+=./DlgNewSkin.cpp
SOURCES+=./DlgSkinSelect.cpp
SOURCES+=./DlgStyleManage.cpp
SOURCES+=./MainDlg.cpp
SOURCES+=./ScintillaWnd.cpp
SOURCES+=./SImageSwitcher.cpp
SOURCES+=./SMoveWnd.cpp
SOURCES+=./SMyButton.cpp
SOURCES+=./SSwitch.cpp
SOURCES+=./SToolbox.cpp
SOURCES+=./UIEditor.cpp
SOURCES+=./SouiRealWndHandler.cpp
SOURCES+=./propgrid/SPropertyGrid.cpp
SOURCES+=./SPropertyGridEx.cpp
SOURCES+=./propgrid/propitem/SPropertyItem-Color.cpp
SOURCES+=./propgrid/propitem/SPropertyItem-Option.cpp
SOURCES+=./propgrid/propitem/SPropertyItem-Size.cpp
SOURCES+=./propgrid/propitem/SPropertyItem-Text.cpp
SOURCES+=./propgrid/SPropertyItemBase.cpp
SOURCES+=./trayicon/SShellNotifyIcon.cpp
SOURCES+=./colorpicker/ColourPopup.cpp
SOURCES+=./colorpicker/SColorPicker.cpp
SOURCES+=./DlgFontSelect.cpp

HEADERS+=./Adapter.h
HEADERS+=./CDebug.h
HEADERS+=./CNewGuid.h
HEADERS+=./DesignerView.h
HEADERS+=./DlgAbout.h
HEADERS+=./DlgCreatePro.h
HEADERS+=./DlgInput.h
HEADERS+=./DlgNewLayout.h
HEADERS+=./DlgNewSkin.h
HEADERS+=./DlgSkinSelect.h
HEADERS+=./DlgStyleManage.h
HEADERS+=./MainDlg.h
HEADERS+=./resource.h
HEADERS+=./SciLexer.h
HEADERS+=./Scintilla.h
HEADERS+=./ScintillaWnd.h
HEADERS+=./SImageSwitcher.h
HEADERS+=./SMoveWnd.h
HEADERS+=./SMyButton.h
HEADERS+=./SSwitch.h
HEADERS+=./SToolbox.h
HEADERS+=./SouiRealWndHandler.h
HEADERS+=./propgrid/SPropertyEmbedWndHelper.hpp
HEADERS+=./propgrid/SPropertyGrid.h
HEADERS+=./SPropertyGridEx.h
HEADERS+=./propgrid/propitem/SPropertyItem-Color.h
HEADERS+=./propgrid/SPropertyItem-i.h
HEADERS+=./propgrid/propitem/SPropertyItem-Option.h
HEADERS+=./propgrid/propitem/SPropertyItem-Size.h
HEADERS+=./propgrid/propitem/SPropertyItem-Text.h
HEADERS+=./propgrid/SPropertyItemBase.h
HEADERS+=./trayicon/SShellNotifyIcon.h
HEADERS+=./colorpicker/ColourPopup.h
HEADERS+=./colorpicker/SColorPicker.h
HEADERS+=./colorpicker/Tooltipctrl.h
HEADERS+=./DlgFontSelect.h
HEADERS+=../../controls.extend/ExtendSkins.h
HEADERS+=../../controls.extend/imre/ImgProvider.h
HEADERS+=../../controls.extend/imre/IRichEditObjHost.h
HEADERS+=../../controls.extend/image3d/PerspectiveTransform.h
HEADERS+=../../controls.extend/imre/RichEditObj.h
HEADERS+=../../controls.extend/imre/RichEditObjFactory.h
HEADERS+=../../controls.extend/imre/RichEditOleBase.h
HEADERS+=../../controls.extend/imre/RichEditOleCallback.h
HEADERS+=../../controls.extend/imre/RichEditOleCtrls.h
HEADERS+=../../controls.extend/gif/SAniImgFrame.h
HEADERS+=../../controls.extend/SAnimImg.h
HEADERS+=../../controls.extend/SButtonEx.h
HEADERS+=../../controls.extend/SChromeTabCtrl.h
HEADERS+=../../controls.extend/SFreeMoveWindow.h
HEADERS+=../../controls.extend/gif/SGifPlayer.h
HEADERS+=../../controls.extend/SImageEx.h
HEADERS+=../../controls.extend/SImageMaskWnd.h
HEADERS+=../../controls.extend/SImagePlayer.h
HEADERS+=../../controls.extend/imre/SImRichEdit.h
HEADERS+=../../controls.extend/gif/SSkinAPNG.h
HEADERS+=../../controls.extend/gif/SSkinGif.h
HEADERS+=../../controls.extend/SSkinMutiFrameImg.h
HEADERS+=../../controls.extend/SSplitBar.h
HEADERS+=../../controls.extend/STabCtrl2.h
HEADERS+=../../controls.extend/SText.h
HEADERS+=../../controls.extend/STurn3DView.h
HEADERS+=../../controls.extend/SScrollText.h
