/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#include "MainWindow.h"

MainWindow::MainWindow()
	:
	BWindow(BRect(), "SuperPrefs", B_TITLED_WINDOW,
		B_AUTO_UPDATE_SIZE_LIMITS)
{
	ResizeTo(640, 360);
	CenterOnScreen();

    fMenuBar = new BMenuBar("MenuBar");
    fAppMenu = new BMenu("File");
    fAppMenu->AddItem(new BMenuItem("Close",
        new BMessage(kMenuAppQuit), 'C', B_COMMAND_KEY));
    fMenuBar->AddItem(fAppMenu);

    fAppMenu = new BMenu("Settings");
    fItem = new BMenuItem("Sort Category wise",
		new BMessage(kCategorywise));
	fItem->SetMarked(true);
    fAppMenu->AddItem(fItem);
    fItem = new BMenuItem("Sort Alphabetically",
		new BMessage(kAlphabeticalwise));
    fItem->SetMarked(false);
    fAppMenu->AddItem(fItem);
    fMenuBar->AddItem(fAppMenu);

	fSearch = new BTextControl("SearchBox", "Search:", NULL, NULL);
	fSearch->MakeFocus(true);

	fAppearanceBox = new BBox((char*) NULL);
	fAppearanceBox->SetLabel("Appearance Preferences:");

	fInputBox = new BBox((char*)NULL);
	fInputBox->SetLabel("Input Preferences:");

	fNetworkBox = new BBox((char*)NULL);
	fNetworkBox->SetLabel("Network Preferences:");

	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(fMenuBar)
		.AddGroup(B_HORIZONTAL, 0)
		.SetInsets(5,5,5,5)
			.Add(fSearch)
		.End()
        .AddGroup(B_VERTICAL, 0)
		.SetInsets(5,5,5,5)
			.Add(fAppearanceBox)
			.Add(fInputBox)
			.Add(fNetworkBox)
		.End()
	.End();
}

bool
MainWindow::QuitRequested() {
    return true;
}

void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {

            case kMenuAppQuit:
                be_app->PostMessage(B_QUIT_REQUESTED);
                break;
            case kCategorywise:
                break;
            case kAlphabeticalwise:
                break;
        }
}
