#pragma once

#include "shostwnd.h"
#include "smsgloop.h"

namespace SOUI
{
    class SOUI_EXP SHostDialog : public SHostWnd , public SMessageLoop
    {
    public:
        SHostDialog(LPCTSTR pszXmlName);
        ~SHostDialog(void);
        
        INT_PTR DoModal(HWND hParent=NULL);
        
        void EndDialog(INT_PTR nResult);

    protected:
        void OnOK();
        void OnCancel();

        EVENT_MAP_BEGIN()
            EVENT_ID_COMMAND(IDOK,OnOK)
            EVENT_ID_COMMAND(IDCANCEL,OnCancel)
        EVENT_MAP_END()
    
        INT_PTR m_nRetCode;
    };

}
