
// WaterReminderAppDlg.h: Headerdatei
//

#pragma once


// CWaterReminderAppDlg-Dialogfeld
class CWaterReminderAppDlg : public CDialogEx
{
// Konstruktion
public:
	CWaterReminderAppDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WATERREMINDERAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SendWhatsAppMessage(UINT_PTR nIDEvent);
	bool CWaterReminderAppDlg::ReadConfig(CString& phoneNumber, CString& apiKey);
public:
	CEdit intervalEditCtrl;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
