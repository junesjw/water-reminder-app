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

CWaterReminderAppDlg::CWaterReminderAppDlg(CWnd* pParent)
	: CDialogEx(IDD_WATERREMINDERAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaterReminderAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INTERVAL_EDIT, intervalEditCtrl);
	DDX_Control(pDX, IDC_REMINDER_MESSAGE, reminderMessageEditCtrl);
	DDX_Control(pDX, IDC_API_KEY, apiKeyEditCtrl);
	DDX_Control(pDX, IDC_PHONE_NUMBER, phoneNumberEditCtrl);
}

BEGIN_MESSAGE_MAP(CWaterReminderAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONSTART, &CWaterReminderAppDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CWaterReminderAppDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()

BOOL CWaterReminderAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetWindowLong(this->m_hWnd, GWL_STYLE, GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_SYSMENU);

	CString phoneNumber, apiKey;
	if (ReadEnvironmentVariables(phoneNumber, apiKey))
	{
		phoneNumberEditCtrl.SetWindowTextW(phoneNumber);
		apiKeyEditCtrl.SetWindowTextW(apiKey);
	}

	return TRUE;
}

void CWaterReminderAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
HCURSOR CWaterReminderAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CWaterReminderAppDlg::ReadEnvironmentVariables(CString& phoneNumber, CString& apiKey)
{
	char* pVal = nullptr;
	size_t sz = 0;

	if (_dupenv_s(&pVal, &sz, "PHONE_NUMBER") != 0 || pVal == nullptr)
		return false;

	phoneNumber = pVal;
	free(pVal);

	if (_dupenv_s(&pVal, &sz, "API_KEY") != 0 || pVal == nullptr)
		return false;

	apiKey = pVal;
	free(pVal);

	return true;
}

void CWaterReminderAppDlg::OnBnClickedButtonStart()
{
	CString phoneNumber, apiKey;
	CString str = _T("");
	intervalEditCtrl.GetWindowTextW(str);

	int interval = _ttoi(str);

	if (interval <= 0)
	{
		AfxMessageBox(_T("Please enter a positive number for the interval."));
		return;
	}

	phoneNumberEditCtrl.GetWindowTextW(phoneNumber);
	apiKeyEditCtrl.GetWindowTextW(apiKey);

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
		CString phoneNumber, apiKey, reminderMessage, message, url;
		phoneNumberEditCtrl.GetWindowTextW(phoneNumber);
		apiKeyEditCtrl.GetWindowTextW(apiKey);
		reminderMessageEditCtrl.GetWindowTextW(reminderMessage);

		if (phoneNumber.IsEmpty() || apiKey.IsEmpty())
		{
			AfxMessageBox(_T("Phone Number or API Key is empty."));
			return;
		}

		if (reminderMessage.IsEmpty())
			message = _T("Drink some water!");
		else
			message = reminderMessage;

		url.Format(_T("https://api.callmebot.com/whatsapp.php?phone=%s&text=%s&apikey=%s"), phoneNumber, message, apiKey);

		CInternetSession session(_T("WhatsApp Reminder"));
		CStdioFile* pFile = nullptr;
		try
		{
			pFile = session.OpenURL(url);
		}
		catch (CInternetException* pEx)
		{
			pEx->Delete();
		}

		if (pFile)
		{
			pFile->Close();
			delete pFile;
		}

		session.Close();

		CDialog::OnTimer(nIDEvent);
	}
}