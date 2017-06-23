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
	BWindow(BRect(), "SuperPrefs",B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
	 B_QUIT_ON_WINDOW_CLOSE)
{

	ResizeTo(720, 420);
	CenterOnScreen();
	
	//Menubar items
	
	fMenuBar = new BMenuBar("MenuBar");
	fAppMenu = new BMenu("File");
	fAppMenu->AddItem(new BMenuItem("Close", new BMessage(kMenuAppQuit), 
	'C', B_COMMAND_KEY));
	fMenuBar->AddItem(fAppMenu);
    fAppMenu = new BMenu("Settings");
    fItem = new BMenuItem("Sort Category wise",	new BMessage(kCategorywise));
	fItem->SetMarked(true);
    fAppMenu->AddItem(fItem);
    fItem = new BMenuItem("Sort Alphabetically", new BMessage(kAlphabeticalwise));
	fItem->SetMarked(false);
    fAppMenu->AddItem(fItem);
    fMenuBar->AddItem(fAppMenu);
    fAppMenu = new BMenu("Help..");
    BMenuItem* item = new BMenuItem("About..", new BMessage(B_ABOUT_REQUESTED));
	item->SetTarget(be_app);
	fAppMenu->AddItem(item);
	fMenuBar->AddItem(fAppMenu);
	
    //Search Bar

	fSearch = new BTextControl("SearchBox", "Search:", NULL, NULL);
	fSearch->MakeFocus(true);
	
	//Box Layouts

	fAppearanceBox = new BBox((char*) NULL);
	fInputBox = new BBox((char*)NULL);
	fNetworkBox = new BBox((char*)NULL);
	fSampleBox = new BBox((char*)NULL);
	
	fAppearanceBox->SetLabel("Appearance Preferences:");
	fNetworkBox->SetLabel("Network Preferences:");
	fInputBox->SetLabel("Input Preferences:");
	fSampleBox->SetLabel("Sample Box - Test Area");
	
	BString AppearanceSign[3] = {"application/x-vnd.Haiku-Appearance",
	 "application/x-vnd.Haiku-Backgrounds", "application/x-vnd.Haiku-Screen" };
	 
	AppearanceLayout = BLayoutBuilder::Group<>
		(fAppearanceBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", AppearanceSign[i]);
	
		bGetName(AppearanceSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, mButton);
		bSetIcon(bSample, AppearanceSign[i]);	
		BLayoutItem* layout = AppearanceLayout->AddView(bSample);
	}
	
	BString InputSign[3] = {"application/x-vnd.Haiku-Keyboard",
	 "application/x-vnd.Haiku-Keymap", "application/x-vnd.Haiku-Mouse" };
	 
	InputLayout = BLayoutBuilder::Group<>
		(fInputBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", InputSign[i]);
	
		bGetName(InputSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, mButton);
		bSetIcon(bSample, InputSign[i]);	
		BLayoutItem* layout = InputLayout->AddView(bSample);
	}
		
	BString NetworkSign[3] = {"application/x-vnd.Be-MAIL",
	 "application/x-vnd.Haiku-Network", "application/x-vnd.Haiku-RemoteDesktop" };
	 
	NetworkLayout = BLayoutBuilder::Group<>
		(fNetworkBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", NetworkSign[i]);
	
		bGetName(NetworkSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, mButton);
		bSetIcon(bSample, NetworkSign[i]);	
		BLayoutItem* layout = NetworkLayout->AddView(bSample);
	}
	
	BString AppSign[2] = {"application/x-vnd.Haiku-Locale",
	 "application/x-vnd.Haiku-BluetoothPrefs"};

	BGroupLayout* GroupLayout =	BLayoutBuilder::Group<>
		(fSampleBox, B_HORIZONTAL, 0)
			.SetInsets(10)
	.Layout();
	
	for(int i=0; i<2; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", AppSign[i]);
	
		bGetName(AppSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, mButton);
		bSetIcon(bSample, AppSign[i]);	
		BLayoutItem* layout = GroupLayout->AddView(bSample);
	}
	
	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.AddGroup(B_VERTICAL, 0)
			.Add(fMenuBar)
			.Add(fSearch)
				.SetInsets(4)
			.Add(fAppearanceBox)
			.Add(fInputBox)
			.Add(fNetworkBox)
			.Add(fSampleBox)
	.End();
}

void
MainWindow::bGetName(BString AppSign, BString* fAppName) {
	char name[B_FILE_NAME_LENGTH];
	entry_ref ref;	
	be_roster->FindApp(AppSign, &ref);
	BEntry entry(&ref);
	entry.GetName(name);
	fAppName->SetTo(name);
}
	
void 
MainWindow::bSetIcon(BButton* button, BString AppSign) {
	
	BMimeType mime(AppSign); 
	BRect bRect(0, 0.0, B_LARGE_ICON - 1, B_LARGE_ICON -1);
	BBitmap *icon = new BBitmap(bRect, B_CMAP8);	
	
	mime.GetIcon(icon, B_LARGE_ICON);
	button->SetIcon(icon);	
}

bool
MainWindow::QuitRequested() {
    return true;
}

void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {
        	case MSG_SIGN: {
        		 BString AppSign;
        		 AppSign = message->GetString("mime_val");
        		 be_roster->Launch(AppSign);        		  
        		break;
        	}       
            case kMenuAppQuit:
            {
                be_app->PostMessage(B_QUIT_REQUESTED);
                break;
            }
            case kCategorywise:
                break;
            case kAlphabeticalwise:
                break;
        }
}
