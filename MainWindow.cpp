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
		BButton* button = new BButton(fAppName, fAppName, mButton);
		bSetIcon(button, AppearanceSign[i]);	
		layout = AppearanceLayout->AddView(button);
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
		BButton* button = new BButton(fAppName, fAppName, mButton);
		bSetIcon(button, InputSign[i]);	
		layout = InputLayout->AddView(button);
	}
		
	BString NetworkSign[3] = {"application/x-vnd.Haiku-Mail",
	 "application/x-vnd.Haiku-Network", "application/x-vnd.Haiku-BluetoothPrefs" };
	 
	NetworkLayout = BLayoutBuilder::Group<>
		(fNetworkBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", NetworkSign[i]);
	
		bGetName(NetworkSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		bSetIcon(button, NetworkSign[i]);	
		layout = NetworkLayout->AddView(button);
	}
	
	BGroupLayout* GroupLayout =	BLayoutBuilder::Group<>
		(fSampleBox, B_VERTICAL, 0)
		.SetInsets(15)
	.Layout();

	//End of layout
	
	// Code to fetch Directory listings
			
	BPath path;	
	find_directory(B_SYSTEM_PREFERENCES_DIRECTORY, &path, true);
	BDirectory directory;
	entry_ref ref;
	BEntry entry;
	directory.SetTo(path.Path());

//	char **paths=0;
//	size_t path_count;
//	find_paths(B_FIND_PATH_PREFERENCES_DIRECTORY, NULL, &paths, path_count);

	vector<BString> vSign;				//To hold Signature of all Prefs
	vector<BString> vPath;				//To hold Path of all Prefs
	vector<BString> vName; 				//To hold Name of all Prefs
				
	map<BString,BString> NameSign;			//To map Name, Signature
	
	while(directory.GetNextRef(&ref)==B_OK) {
		char sign[B_MIME_TYPE_LENGTH];
		entry.SetTo(&ref, false);		
		entry.GetPath(&path);	
		BFile file(&entry, B_READ_ONLY);
		BAppFileInfo fileinfo(&file);
		fileinfo.GetSignature(sign);
		vPath.push_back(path.Path());	//Pushing path
		vSign.push_back(sign);			//Pushing sign
		bGetName(sign, &fAppName);
		vName.push_back(fAppName);		//Pushing name
		NameSign[fAppName]=sign;
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
	entry_ref ref;	
	be_roster->FindApp(AppSign, &ref);
	BEntry entry(&ref);
	BString LOCALIZED_APP;
	char EN_APP[B_FILE_NAME_LENGTH];
	entry.GetName(EN_APP);
	if(BLocaleRoster::Default()->GetLocalizedFileName(LOCALIZED_APP, ref)
			==B_OK) {
		*fAppName = LOCALIZED_APP;
	}
	else {				
		*fAppName = EN_APP;
	}
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

//	map<BString,BString>::iterator 
//		it = NameSign.begin();				//Iterator to NameSign
//	
//	for(int i = 0 ; i < 24 ; ++i) {
//		BStringView* NameView = new BStringView("Name:", it->first);
//		if(i!=23) ++it;
//		layout = GroupLayout->AddView(NameView);
//	}			
//
//	BStringView* SignView = new BStringView("Sign:", it->first);
