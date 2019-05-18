/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */
#include "Catalog.h"
#include "App.h"
#include <private/interface/AboutWindow.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"

using namespace std;
const char* kAppName = "SuperPrefs";
const char* kSignature = "application/x-vnd.SuperPrefs";

App::App()
	:
	BApplication(kSignature)
{
	fMainWindow = new MainWindow();
	fMainWindow->Show();
	fMainWindow->Activate();
}

void
App::AboutRequested() {
	BAboutWindow* about = new BAboutWindow(kAppName, kSignature);
	about->AddDescription(B_TRANSLATE("Control Panel with Search for Haiku"));
	about->AddCopyright(2017, 
		"\nAnirudh M\n(m.anirudh18@gmail.com)\nhttp://www.anirudhmurali.com");
	about->SetVersion("1.0");
	about->Show();
}

int
main()
{
	App app;
	app.Run();
	return 0;
}
