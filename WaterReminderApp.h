
// WaterReminderApp.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CWaterReminderAppApp:
// Siehe WaterReminderApp.cpp für die Implementierung dieser Klasse
//

class CWaterReminderAppApp : public CWinApp
{
public:
	CWaterReminderAppApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CWaterReminderAppApp theApp;
