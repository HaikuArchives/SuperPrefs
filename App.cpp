/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#include "App.h"

const char* kAppName = "SuperPrefs";
const char* kSignature = "application/x-vnd.SuperPrefs";

App::App()
	:
	BApplication(kSignature)
{
	fMainWindow = new MainWindow();
	fMainWindow->Show();
}

int
main()
{
	App app;
	app.Run();
	return 0;
}
