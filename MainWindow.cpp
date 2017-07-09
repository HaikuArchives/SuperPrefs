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
	BWindow(BRect(),"SuperPrefs",B_TITLED_WINDOW_LOOK,
 	B_NORMAL_WINDOW_FEEL, B_ASYNCHRONOUS_CONTROLS | B_NOT_RESIZABLE)
{

	ResizeTo(920, 480);

	CenterOnScreen();
	buildBox();
	buildLayout();
	buildMenubar();
	populateLayout();
	fetchPreflets();	
	mergeLayouts();
}

void
MainWindow::populateLayout() {
	
	BString AppearanceSign[4] = {"application/x-vnd.Haiku-Appearance",
	 "application/x-vnd.Haiku-Backgrounds", "application/x-vnd.Haiku-DeskbarPreferences", 
	 "application/x-vnd.Haiku-ScreenSaver" };
	 
	BString ConnectivitySign[3] = {"application/x-vnd.Haiku-BluetoothPrefs",
	 "application/x-vnd.Haiku-Network", "application/x-vnd.Haiku-Mail" };	 
	 	
	BString IOSign[7] = {"application/x-vnd.Haiku-Screen",
	 "application/x-vnd.Haiku-Touchpad", "application/x-vnd.Haiku-Keyboard",
	 "application/x-vnd.Haiku-Keymap", "application/x-vnd.Be-PRNT", 
	 "application/x-vnd.Haiku-Mouse", "application/x-vnd.Haiku-Media" };	 
	 	
	BString SystemSign[7] = {"application/x-vnd.Haiku-Shortcuts", 
	"application/x-vnd.Haiku-Notifications", "application/x-vnd.Haiku-Time",
	"application/x-vnd.Haiku-TrackerPreferences", "application/x-vnd.Haiku-FileTypes",
	"application/x-vnd.Haiku-Locale", "application/x-vnd.Haiku-Sounds" };
		
	BString UncategorizedSign[3] = {"application/x-vnd.Haiku-DataTranslations", 
	"application/x-vnd.Haiku-VirtualMemory", "application/x-vnd.Haiku-Repositories"};	
	
	/* TODO: Add an attribute to .rdef of every preflet to denote its cateogry or a similar
			method to avoid hardcoded categories.	*/
			
	for(int i=0; i<4; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", AppearanceSign[i]);
	
		bGetName(AppearanceSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		NameButton[fAppName] = button;
		bSetIcon(button, AppearanceSign[i]);	
		layout = AppearanceLayout->AddView(button);
	}	// Appearance
	
	for(int i=0; i<3; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", ConnectivitySign[i]);
	
		bGetName(ConnectivitySign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		NameButton[fAppName] = button;
		bSetIcon(button, ConnectivitySign[i]);	
		layout = ConnectivityLayout->AddView(button);
	}	// Connectivity
	
	for(int i=0; i<7; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", IOSign[i]);
	
		bGetName(IOSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		NameButton[fAppName] = button;
		bSetIcon(button, IOSign[i]);	
		layout = IOLayout->AddView(button);
	} 	// Input/Output
 
	for(int i=0; i<7; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", SystemSign[i]);
	
		bGetName(SystemSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		NameButton[fAppName] = button;
		bSetIcon(button, SystemSign[i]);	
		layout = SystemLayout->AddView(button);
	}	// System

	for(int i=0; i<3; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", UncategorizedSign[i]);
	
		bGetName(UncategorizedSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		
		button->SetFlat(true);
		NameButton[fAppName] = button;
		bSetIcon(button, UncategorizedSign[i]);	
		layout = UncategorizedLayout->AddView(button);
	}	// Uncategorized
}	

void
MainWindow::fetchPreflets() {

	find_directory(B_SYSTEM_PREFERENCES_DIRECTORY, &path, true);
	directory.SetTo(path.Path());

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
}

void
MainWindow::buildMenubar() {
	
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
}

void
MainWindow::mergeLayouts() {
		
	root = new BGroupLayout(B_VERTICAL, 0);
	this->SetLayout(root);

	vView = new BGroupView(B_VERTICAL);
	vLayout = vView->GroupLayout();
	this->AddChild(vView);
	vLayout->AddView(fMenuBar);
	vLayout->AddView(tSearch);
	vLayout->SetInsets(2);
	vLayout->AddView(fAppearanceBox);
	vLayout->AddView(fIOBox);
	vLayout->AddView(fSystemBox);

	BSplitView* SplitGroup = new BSplitView(B_HORIZONTAL);
	SplitGroup->SetName("Splitter");
	BLayoutBuilder::Split<>(SplitGroup)
		.Add(fConnectivityBox)
		.Add(fUncategorizedBox);
				
	vLayout->AddView(SplitGroup);
	vLayout->AddView(fLogBox);
	
	
//	MainLayout = BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
//		.AddGroup(B_VERTICAL, 0)
//			.Add(fMenuBar)
//				.AddGlue(0.25)
//			.Add(tSearch)
//				.SetInsets(5)
//			.Add(fAppearanceBox)
//			.Add(fIOBox)
//			.Add(fSystemBox)
//			.AddSplit(B_HORIZONTAL, 0, 0)
//				.Add(fConnectivityBox)	
//				.Add(fUncategorizedBox)
//			.End()
//			.Add(fLogBox)
//	.End()
//	.Layout();

}

void
MainWindow::buildBox() {

	fAppearanceBox = new BBox((char*) NULL);
	fIOBox = new BBox((char*)NULL);
	fConnectivityBox = new BBox((char*)NULL);
	fSystemBox = new BBox((char*)NULL);
	fUncategorizedBox = new BBox((char*)NULL);
	fLogBox = new BBox((char*)NULL);
	
	fAppearanceBox->SetLabel("Appearance Preferences:");
	fConnectivityBox->SetLabel("Connectivity Preferences:");
	fIOBox->SetLabel("Input/Output Preferences:");
	fSystemBox->SetLabel("System Preferences:");
	fUncategorizedBox->SetLabel("Uncategorized");
	fLogBox->SetLabel("Log");
}

void
MainWindow::buildLayout() {
		 
	AppearanceLayout = BLayoutBuilder::Group<>
		(fAppearanceBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	ConnectivityLayout = BLayoutBuilder::Group<>
		(fConnectivityBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();	

	IOLayout = BLayoutBuilder::Group<>
		(fIOBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	SystemLayout = BLayoutBuilder::Group<>
		(fSystemBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	UncategorizedLayout = BLayoutBuilder::Group<>
		(fUncategorizedBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	LogLayout = BLayoutBuilder::Group<>
		(fLogBox, B_VERTICAL, 0)
		.SetInsets(15)
	.Layout();
	
	//Search Bar
	
	tSearch = new BTextControl("Search:", "Search: ", NULL, NULL);
	tSearch->SetModificationMessage(new BMessage(QUERY));	
	tSearch->MakeFocus(true);
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
MainWindow::fSearch() {
	
	BString* Query = new BString(tSearch->Text());
	BStringView* SearchQuery = new BStringView("Search","");	
	int tSearchLength = Query->Length();
	if(tSearchLength > 1) {
	
	vTemp.clear();
	map<BString, BButton*>::iterator 
		it = NameButton.begin();						//Iterator to NameSign
	
	for(int i = 0 ; i < 24 ; ++i) {
		NameButton[vName[i]]->SetFlat(true);
		NameButton[vName[i]]->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		NameButton[vName[i]]->SetFont(be_plain_font);
		if(i!=23) ++it;
	}		
	
	sort(vName.begin(), vName.begin()+vName.size());	//Not necessary, done for better understanding
	
	
	layout = LogLayout->AddView(SearchQuery);
	int occurences = 0, found = 0;
	for(int i = 0 ; i < vName.size() ; i++) 
  		if(vName[i].IFindFirst(*Query) != B_ERROR) {
			occurences++;		
			found = 1;
			vTemp.push_back(vName[i]);
		}
	
	if(found)	Query->operator<<(": Found. Occurences: ");	
	else 		Query->operator<<(": Not Found. Occurences: ");
	Query->operator<<(occurences);
	Query->operator<<('.');

	if(found) {
		if(vTemp.size() > 1) {
			Query->operator<<(" Associated Apps: ");
			for(int i = 0 ; i < vTemp.size() ; i++) {
				Query->operator<<(vTemp[i]);
				if(i != vTemp.size() - 1)	Query->operator<<(", ");
				else	Query->operator<<('.');
			}
		}
		else {
			Query->operator<<(" Associated App: ");
			Query->operator<<(vTemp[0]);
		}
	}

	SearchQuery->SetText(Query->String());
	for(int i = 0 ; i < vTemp.size() ; i ++ ) {
		NameButton[vTemp[i]]->SetFlat(false);		
		NameButton[vTemp[i]]->SetViewColor((rgb_color) {255,64,64,255});
		NameButton[vTemp[i]]->SetFont(be_bold_font);
	}
	}
	
}	

void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {
        	case QUERY:
        	{
        		fSearch();
        		break;
        	}        		
        	case MSG_SIGN: 
        	{        		
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
