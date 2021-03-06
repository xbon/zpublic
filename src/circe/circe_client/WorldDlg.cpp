#include "stdafx.h"
#include "resource.h"

#include "WorldDlg.h"
#include "World1Dlg.h"
#include "World2Dlg.h"
#include "World3Dlg.h"
#include "PlayerInfoDlg.h"

LRESULT CWorldDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CenterWindow(GetParent());
    return TRUE;
}

LRESULT CWorldDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    EndDialog(0);
    return 0;
}

LRESULT CWorldDlg::OnBnClickedJump(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码

    return 0;
}


LRESULT CWorldDlg::OnBnClickedWorld1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    ShowWindow(SW_HIDE);
    CWorld1Dlg dlg;
    dlg.DoModal();
    ShowWindow(SW_SHOW);
    return 0;
}


LRESULT CWorldDlg::OnBnClickedWorld2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    ShowWindow(SW_HIDE);
    CWorld2Dlg dlg;
    dlg.DoModal();
    ShowWindow(SW_SHOW);
    return 0;
}


LRESULT CWorldDlg::OnBnClickedWorld3(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    ShowWindow(SW_HIDE);
    CWorld3Dlg dlg;
    dlg.DoModal();
    ShowWindow(SW_SHOW);
    return 0;
}


LRESULT CWorldDlg::OnBnClickedWorldPalyerInfo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CPlayerInfoDlg dlg;
    dlg.DoModal();
    return 0;
}
