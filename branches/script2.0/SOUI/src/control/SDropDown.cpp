/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 *
 * @file       SDropDown.cpp
 * @brief      SDropDownWnd��Դ�ļ�
 * @version    v1.0
 * @author     soui
 * @date       2014-05-25
 *
 * Describe  ���ļ���Ҫ����SDropDownWnd�����ʵ��
 */
#include "souistd.h"
#include "control/SDropDown.h"
#include <core/SMsgLoop.h>

namespace SOUI
{

    SDropDownWnd::SDropDownWnd(ISDropDownOwner* pOwner)
        :m_pOwner(pOwner)
        ,m_bClick(FALSE)
        ,m_uExitCode(IDCANCEL)
    {
        GetMsgLoop()->AddMessageFilter(this);
    }

    SDropDownWnd::~SDropDownWnd()
    {
        GetMsgLoop()->RemoveMessageFilter(this);
    }

    void SDropDownWnd::OnFinalMessage(HWND hWnd)
    {
        __super::OnFinalMessage(hWnd);
        delete this;
    }

    void SDropDownWnd::OnKillFocus( HWND wndFocus )
    {
        if(wndFocus != m_hWnd)
        {
            EndDropDown();
        }
    }

    BOOL SDropDownWnd::Create(LPCRECT lpRect ,LPVOID lParam,DWORD dwStyle,DWORD dwExStyle)
    {
        HWND hParent = m_pOwner->GetDropDownOwner()->GetContainer()->GetHostHwnd();
        HWND hWnd=CSimpleWnd::Create(NULL,dwStyle,dwExStyle,lpRect->left,lpRect->top,lpRect->right-lpRect->left,lpRect->bottom-lpRect->top,hParent,0);
        if(!hWnd) return FALSE;
        m_pOwner->OnDropDown(this);
        return TRUE;
    }

    void SDropDownWnd::OnLButtonDown( UINT nFlags, CPoint point )
    {
        CRect rcWnd;
        CSimpleWnd::GetClientRect(&rcWnd);
        if(!rcWnd.PtInRect(point))
        {
            EndDropDown();
        }else
        {
            m_bClick=TRUE;
            SetMsgHandled(FALSE);
        }
    }

    void SDropDownWnd::OnLButtonUp( UINT nFlags, CPoint point )
    {
        if(m_bClick)
        {
            LRESULT lRes=0;
            HWND hWnd=m_hWnd;
            CRect rcWnd;
            CSimpleWnd::GetClientRect(&rcWnd);
            SHostWnd::ProcessWindowMessage(m_hWnd,WM_LBUTTONUP,nFlags,MAKELPARAM(point.x,point.y),lRes);
            if(::IsWindow(hWnd) && !rcWnd.PtInRect(point))
                EndDropDown();//ǿ�ƹرյ�������
        } 
    }

    void SDropDownWnd::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
    {
        if(nChar==VK_RETURN)
            EndDropDown(IDOK);
        else if(nChar==VK_ESCAPE)
            EndDropDown();
        else 
            SetMsgHandled(FALSE);
    }

    void SDropDownWnd::EndDropDown(UINT uCode)
    {
        m_uExitCode=uCode;
        HWND hWnd=m_pOwner->GetDropDownOwner()->GetContainer()->GetHostHwnd();
        DestroyWindow();
        SetActiveWindow(hWnd);
    }

    void SDropDownWnd::OnDestroy()
    {
        m_pOwner->OnCloseUp(this,m_uExitCode);
        SetMsgHandled(FALSE);
    }

    BOOL SDropDownWnd::PreTranslateMessage( MSG* pMsg )
    {
        if(pMsg->message==WM_ACTIVATEAPP)
        {
            CSimpleWnd::SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
        }
        else if(pMsg->message == WM_MOUSEMOVE)
        {//���ڴ�����ʾ��͵�����setcapture�������ղ���setcursor��Ϣ��������WM_MOUSEMOVE��Ϣ��ģ��һ��setcursor��Ϣ��
            CSimpleWnd::SendMessage(WM_SETCURSOR,(WPARAM)m_hWnd,MAKELPARAM(HTCLIENT,WM_MOUSEMOVE));
        }
        return FALSE;
    }

    void SDropDownWnd::OnActivateApp( BOOL bActive, DWORD dwThreadID )
    {
        if(!bActive)
        {
            EndDropDown();
        }
    }

    int SDropDownWnd::OnMouseActivate( HWND wndTopLevel, UINT nHitTest, UINT message )
    {
        return MA_NOACTIVATEANDEAT;
    }

    BOOL SDropDownWnd::OnReleaseSwndCapture()
    {
        BOOL bRet=SHostWnd::OnReleaseSwndCapture();
        CSimpleWnd::SetCapture();
        return bRet;
    }

    SMessageLoop * SDropDownWnd::GetMsgLoop()
    {
        return m_pOwner->GetDropDownOwner()->GetContainer()->GetMsgLoop();
    }

}//end of namespace SOUI