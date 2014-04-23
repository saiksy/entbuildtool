// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

struct TAB_INFO 
{
	CString strName;
	HWND hwnd;

	TAB_INFO(LPCTSTR lpName, HWND hwndDlg) :
		strName(lpName), hwnd(hwndDlg)
	{

	}
};

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	UIUpdateChildWindows();
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	_InitTabCtrl();

	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

void CMainDlg::_InitTabCtrl()
{
	CSimpleArray<TAB_INFO> _ArrTabInfo;

	m_tabMain.Attach(GetDlgItem(IDC_TAB_MAIN));

	// Create Child Dlg
	m_TagDlg.Create(m_tabMain);
	m_MakeCabDlg.Create(m_tabMain);
	
	// add to array
	_ArrTabInfo.Add(TAB_INFO(_T("Tag"), m_TagDlg.m_hWnd));
	_ArrTabInfo.Add(TAB_INFO(_T("MakeCab"), m_MakeCabDlg.m_hWnd));

	CWindow _wnd;
	CRect _rcTab;

	m_tabMain.GetClientRect(&_rcTab);

	_rcTab.top += 21;
	_rcTab.left += 2;
	_rcTab.bottom -= 2;
	_rcTab.right -= 3;

	for (int i = 0; i < _ArrTabInfo.GetSize(); i++)
	{
		m_tabMain.AddItem(_ArrTabInfo[i].strName);
		_wnd.Detach();
		_wnd.Attach(_ArrTabInfo[i].hwnd);

		_wnd.MoveWindow(&_rcTab);
	}

	::ShowWindow(_ArrTabInfo[0].hwnd, SW_SHOW);
	m_tabMain.SetCurSel(0);

}
