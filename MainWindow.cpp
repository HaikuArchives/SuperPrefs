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
	BWindow(BRect(),"SuperPrefs",B_TITLED_WINDOW,
		B_AUTO_UPDATE_SIZE_LIMITS | B_NOT_RESIZABLE)
{
	ResizeTo(920, 480);

	CenterOnScreen();
	buildBox();
	buildLayout();
	buildMenubar();
	
	fetchApps();
	fetchPreflets();
	populateLayout();	
	mergeLayouts();
	mergeLayoutsCategory();
	cPref->SetValue(B_CONTROL_ON);
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

	for(map<BString, BString>::const_iterator it=NameSign.begin(); it != NameSign.end(); ++ it, ++ splitCount) {
		
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", it->second);
		
		BButton* button = new BButton(it->first, it->first, mButton);		
		button->SetFlat(true);
		bSetIcon(button, it->second);
		NameButtonAlphabetical[it->first] = button;
				
		if(splitCount % 6 == 0 || splitCount == 0)
		{
			vView = new BGroupView(B_HORIZONTAL);
			vLayout = vView->GroupLayout();			
		}
		
		vLayout->AddView(button);
		if(splitCount % 6 == 0 || splitCount == 0)
			AlphabeticalLayout->AddView(vView);
	}	// Alphabetical	
	
	for(map<BString, BString>::const_iterator it=AppsNameSign.begin(); it != AppsNameSign.end(); ++ it, ++ splitCount) {
		
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", it->second);
		
		BButton* button = new BButton(it->first, it->first, mButton);		
		button->SetFlat(true);
		bSetIcon(button, it->second);
		NameButtonApps[it->first] = button;
				
		if(splitCount % 6 == 0 || splitCount == 0)
		{
			vView = new BGroupView(B_HORIZONTAL);
			vLayout = vView->GroupLayout();			
		}
		
		vLayout->AddView(button);
		if(splitCount % 6 == 0 || splitCount == 0)
			AppsLayout->AddView(vView);
	}	// Alphabetical	
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
MainWindow::fetchApps() {

	find_directory(B_SYSTEM_APPS_DIRECTORY, &path, true);
	directory.SetTo(path.Path());

	while(directory.GetNextRef(&ref)==B_OK) {
		char sign[B_MIME_TYPE_LENGTH];
		entry.SetTo(&ref, false);		
		entry.GetPath(&path);	
		BFile file(&entry, B_READ_ONLY);
		BAppFileInfo fileinfo(&file);
		fileinfo.GetSignature(sign);
		vAppsPath.push_back(path.Path());	//Pushing path
		vAppsSign.push_back(sign);			//Pushing sign
		bGetName(sign, &fAppName);
		vAppsName.push_back(fAppName);		//Pushing name
		AppsNameSign[fAppName]=sign;
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

    mCategory = new BMenuItem("Sort Category wise", new BMessage(kCategorywise));	
    fAppMenu->AddItem(mCategory);
    mCategory->SetMarked(true); 	// Marked by Default
    
    mAlphabetical = new BMenuItem("Sort Alphabetically", new BMessage(kAlphabeticalwise));
    fAppMenu->AddItem(mAlphabetical);
	mAlphabetical->SetMarked(false);

    fMenuBar->AddItem(fAppMenu);
    fAppMenu = new BMenu("Help..");
    BMenuItem* item = new BMenuItem("About..", new BMessage(B_ABOUT_REQUESTED));
	item->SetTarget(be_app);
	fAppMenu->AddItem(item);
	fMenuBar->AddItem(fAppMenu);
}

void
MainWindow::mergeLayouts() {
	
	cApps = new BCheckBox("Apps", new BMessage(B_APPS));
	cPref = new BCheckBox("Preferences", new BMessage(B_PREFS));

	root = new BGroupLayout(B_VERTICAL, 0);
	this->SetLayout(root);
	vView = new BGroupView(B_VERTICAL);
	vLayout = vView->GroupLayout();
	this->AddChild(vView);
	vLayout->AddView(fMenuBar);
	vLayout->AddView(fSearchBox);
	vLayout->SetInsets(2);	
		
	SearchSplitGroup = new BSplitView(B_HORIZONTAL);
	SearchSplitGroup->SetName("Splitter");
	BLayoutBuilder::Split<>(SearchSplitGroup)
			.Add(tSearch)
			.Add(cApps)
			.Add(cPref);
			
	SearchQuery = new BStringView("Search Text","");	
	SearchLayout->AddView(SearchQuery);
	SearchLayout->AddView(SearchSplitGroup);
}

void
MainWindow::buildBox() {
	
	fAlphabeticalBox = new BBox((char*) NULL);
	fAppsBox = new BBox((char*) NULL);
	fAppearanceBox = new BBox((char*) NULL);
	fIOBox = new BBox((char*)NULL);
	fConnectivityBox = new BBox((char*)NULL);
	fSystemBox = new BBox((char*)NULL);
	fUncategorizedBox = new BBox((char*)NULL);
	fSearchBox = new BBox((char*)NULL);
		
	fAlphabeticalBox->SetLabel("All Preferences [A-Z]");
	fAppearanceBox->SetLabel("Appearance Preferences:");
	fAppsBox->SetLabel("All Apps [A-Z]");
	fConnectivityBox->SetLabel("Connectivity Preferences:");
	fIOBox->SetLabel("Input/Output Preferences:");
	fSystemBox->SetLabel("System Preferences:");
	fUncategorizedBox->SetLabel("Uncategorized:");
	fSearchBox->SetLabel("Search:");
}

void
MainWindow::buildLayout() {
	
	AppsLayout = BLayoutBuilder::Group<>
		(fAppsBox, B_VERTICAL, 0)
		.SetInsets(15)
	.Layout();
	
	AlphabeticalLayout = BLayoutBuilder::Group<>
		(fAlphabeticalBox, B_VERTICAL, 0)
		.SetInsets(15)
	.Layout();
		 
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
	
	SearchLayout = BLayoutBuilder::Group<>
		(fSearchBox, B_VERTICAL, 0)
		.SetInsets(15)
	.Layout();
	
	tSearch = new BTextControl("Search:", "Enter query here: ", NULL, NULL);
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
	int tSearchLength = Query->Length();
	
	map<BString, BButton*>::iterator 
		it = NameButton.begin();						
	
	FlatTrue();
	
	if(tSearchLength > 1) {
	
	vTemp.clear();
		
	sort(vName.begin(), vName.begin()+vName.size());	//Optional
	
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
			Query->operator<<('.');
		}
	}
	
	SearchQuery->SetText(Query->String());
	
	FlatFalse(vTemp);
	
	}
	else {
		SearchQuery->SetText("");
	}
}	

void
MainWindow::FlatFalse(vector<BString>& vTemp) {
	
	for(int i = 0 ; i < vTemp.size() ; i ++ ) {
		NameButton[vTemp[i]]->SetFlat(false);		
		NameButton[vTemp[i]]->SetViewColor((rgb_color) {64,64,64,255});
		NameButton[vTemp[i]]->SetFont(be_bold_font);
		NameButtonAlphabetical[vTemp[i]]->SetFlat(false);		
		NameButtonAlphabetical[vTemp[i]]->SetViewColor((rgb_color) {64,64,64,255});
		NameButtonAlphabetical[vTemp[i]]->SetFont(be_bold_font);
	}
}

void
MainWindow::FlatTrue() {	

	for(int i = 0 ; i < 24 ; ++i) {
		NameButton[vName[i]]->SetFlat(true);
		NameButton[vName[i]]->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		NameButton[vName[i]]->SetFont(be_plain_font);
		NameButtonAlphabetical[vName[i]]->SetFlat(true);
		NameButtonAlphabetical[vName[i]]->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		NameButtonAlphabetical[vName[i]]->SetFont(be_plain_font);
	}	
}

void
MainWindow::mergeLayoutsCategory() {

  	if(mAlphabetical->IsMarked()) { 
  		vLayout->RemoveView(fAlphabeticalBox); 
  		mCategory->SetMarked(true);
  		mAlphabetical->SetMarked(false);
  	}
  	else {
  		SplitGroup = new BSplitView(B_HORIZONTAL);
		SplitGroup->SetName("Splitter");
		BLayoutBuilder::Split<>(SplitGroup)
			.Add(fConnectivityBox)
			.Add(fUncategorizedBox);
  	}
  	if(!mAlphabetical->IsMarked()) {
		vLayout->AddView(fAppearanceBox);
		vLayout->AddView(fIOBox);
		vLayout->AddView(SplitGroup);
  		vLayout->AddView(fSystemBox);
  	}
}

void
MainWindow::mergeLayoutsAlphabetical() {

	mCategory->SetMarked(false);
	mAlphabetical->SetMarked(true);
	vLayout->RemoveView(fAppearanceBox);
	vLayout->RemoveView(fIOBox);
	vLayout->RemoveView(SplitGroup);
	vLayout->RemoveView(fSystemBox);
	vLayout->AddView(fAlphabeticalBox);
	//FlatFalse();
}

void
MainWindow::mergeLayoutsApps() {
	
	if(mCategory->IsMarked()) {
		vLayout->RemoveView(fAppearanceBox);
		vLayout->RemoveView(fIOBox);
		vLayout->RemoveView(SplitGroup);
		vLayout->RemoveView(fSystemBox);
		vLayout->RemoveView(SplitGroup);
	}
	if(mAlphabetical->IsMarked()) {
		vLayout->RemoveView(fAlphabeticalBox);
		vLayout->RemoveView(SplitGroup);
	}
	vLayout->AddView(fAppsBox);
	mAlphabetical->SetMarked(true);
	mCategory->SetMarked(false);
	
	if(checked % 2 ==0) { vLayout->RemoveView(fAppsBox); cPref->SetValue(B_CONTROL_ON); }
}

void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {
        	case B_APPS:
        	{	checked++;
        		cPref->SetValue(B_CONTROL_OFF);
        		mergeLayoutsApps();
        		break;
        	}
        	case B_PREFS:
        	{
        		checked = 0;
        		break;
        	}	
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
            {		
            	if(!mCategory->IsMarked())
            		mergeLayoutsCategory();
            		 
           	  		break;
            }
            case kAlphabeticalwise:
            {
            	if(!mAlphabetical->IsMarked())
            		mergeLayoutsAlphabetical();
                break;
            }
		}
}
