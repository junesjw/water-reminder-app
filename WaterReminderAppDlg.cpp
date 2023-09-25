
// WaterReminderAppDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "WaterReminderApp.h"
#include "WaterReminderAppDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWaterReminderAppDlg-Dialogfeld



CWaterReminderAppDlg::CWaterReminderAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WATERREMINDERAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaterReminderAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INTERVAL_EDIT, intervalEditCtrl);
}

BEGIN_MESSAGE_MAP(CWaterReminderAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONSTART, &CWaterReminderAppDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CWaterReminderAppDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CWaterReminderAppDlg-Meldungshandler

BOOL CWaterReminderAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CWaterReminderAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CWaterReminderAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CWaterReminderAppDlg::ReadConfig(CString& phoneNumber, CString& apiKey)
{
	CStdioFile file;
	if (!file.Open(_T("config.txt"), CFile::modeRead))
		return false; // Return false if file could not be opened

	CString strLine;
	while (file.ReadString(strLine))
	{
		int separatorPos = strLine.Find('=');
		if (separatorPos != -1)
		{
			CString key = strLine.Left(separatorPos);
			CString value = strLine.Mid(separatorPos + 1);
			if (key.CompareNoCase(_T("phone")) == 0)
				phoneNumber = value;
			else if (key.CompareNoCase(_T("apikey")) == 0)
				apiKey = value;
		}
	}

	file.Close();
	return true;
}

void CWaterReminderAppDlg::OnBnClickedButtonStart()
{
	CString str = _T("");
	intervalEditCtrl.GetWindowTextW(str);

	int interval = _ttoi(str);

	if (interval <= 0)
	{
		AfxMessageBox(_T("Please enter a positive number for the interval."));
		return;
	}

	CString phoneNumber, apiKey;
	if (!ReadConfig(phoneNumber, apiKey))
	{
		AfxMessageBox(_T("Could not read the config file."));
		return;
	}

	SetTimer(1, interval, NULL);
}

void CWaterReminderAppDlg::OnBnClickedButtonStop()
{
	KillTimer(1);
}

void CWaterReminderAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		SendWhatsAppMessage(nIDEvent);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CWaterReminderAppDlg::SendWhatsAppMessage(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString phoneNumber, apiKey;

		if (!ReadConfig(phoneNumber, apiKey))
		{
			AfxMessageBox(_T("Could not read the config file."));
			return;
		}

		CString message = _T("Drink some water!");

		CString url;
		url.Format(_T("https://api.callmebot.com/whatsapp.php?phone=%s&text=%s&apikey=%s"), phoneNumber, message, apiKey);

		CInternetSession session(_T("WhatsApp Reminder"));
		CStdioFile* pFile = nullptr;
		try
		{
			pFile = session.OpenURL(url);
		}
		catch (CInternetException* pEx)
		{
			// Handle exception here (e.g., show a message box)
			pEx->Delete();
		}

		if (pFile)
		{
			// Optionally, read the response here if needed
			// ...

			pFile->Close();
			delete pFile;
		}

		session.Close();

		CDialog::OnTimer(nIDEvent);
	}
}