#pragma once


// CTagDlg dialog

class CTagDlg : public CDialogImpl<CTagDlg>
{
public:
	CTagDlg();   // standard constructor
	virtual ~CTagDlg();

// Dialog Data
	enum { IDD = IDD_DLG_TAG };

	BEGIN_MSG_MAP(CTagDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

protected:
};
