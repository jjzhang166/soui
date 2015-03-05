#pragma once

class CImageMerger
{
friend class CMainDlg;
public:
    CImageMerger(void);
    ~CImageMerger(void);
    
    void OnInit(SWindow *pRoot);
    
    void AddFile(LPCWSTR pszFileName);
protected:
    void OnSave();
    void OnClear();
    void OnModeHorz();
    void OnModeVert();
    
    EVENT_MAP_BEGIN()
        EVENT_NAME_COMMAND(L"btn_save", OnSave)
        EVENT_NAME_COMMAND(L"btn_clear", OnClear)
        EVENT_NAME_COMMAND(L"radio_horz", OnModeHorz)
        EVENT_NAME_COMMAND(L"radio_vert", OnModeVert)        
    EVENT_MAP_BREAK()
    
    SWindow *m_pPageRoot;
    SImgCanvas *m_pImgCanvas;
};
