
#ifdef DLL_SOUI
# ifdef SOUI_EXPORTS
# pragma message("soui:dll export")
#  define SOUI_EXP __declspec(dllexport)
# else
# pragma message("soui:dll import")
#  define SOUI_EXP __declspec(dllimport)
# endif // SOUI_EXPORTS
#else
# pragma message("soui:lib")
#define SOUI_EXP
#endif

#define OR_API SOUI_EXP

// Change these values to use different versions
#ifndef WINVER 
#define WINVER        0x0500
#define _WIN32_WINNT    0x0501
#endif//WINVER

#define _WIN32_IE    0x0601
#define _RICHEDIT_VER    0x0200

#define _CRT_NON_CONFORMING_SWPRINTFS


# pragma warning(disable:4661)
# pragma warning(disable:4251)
# pragma warning(disable:4100)    //unreferenced formal parameter
# pragma warning(disable:4355)

#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <OleCtl.h>
#include <tchar.h>
#include <stdio.h>

#include <core/SDefine.h>

//import pugixml interface

#define _WTYPES_NS SOUI
#define _COLL_NS    SOUI
#include <souicoll.h>
#include <wtl.mini/msgcrack.h>
#include <wtl.mini/souimisc.h>
#include <wtl.mini/souigdi.h>
#include <atl.mini/atldef.h>
#include <atl.mini/scomcli.h>
#include <string/tstring.h>
#include <string/strcpcvt.h>
#include <pugixml/pugixml.hpp>

#include <trace.h>
#include <utilities.h>


#include <interface/render-i.h>
#include <interface/imgdecoder-i.h>

#include <SApp.h>
#include <helper/SAttrCracker.h>
#include <helper/color.h>
#include <res.mgr/sfontpool.h>
#include <res.mgr/sresprovider.h>

#include <control/souictrls.h>
#include <control/SMessageBox.h>


#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"utilities.lib")
