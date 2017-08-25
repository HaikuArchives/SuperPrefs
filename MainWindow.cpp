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
		B_AUTO_UPDATE_SIZE_LIMITS | B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE)
{
	ResizeTo(920, 480);
	CenterOnScreen();
	buildBox();
	buildLayout();
	buildMenubar();
	PrefSource();
	Keywords();	
	AppSource();	
	populateLayout();
	mergeLayouts();
	mergeLayoutsCategory();
	tSearch->MakeFocus(true);
}

void
MainWindow::Keywords() {

	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-TrackerPreferences"),BString("File Explorer Settings")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Mouse"),BString("Scroll Click")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Time"),BString("Clock Timezone")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Network"),BString("Internet DNS Mac")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Touchpad"),BString("Trackpad")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-VirtualMemory"),BString("Virtual Memory")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Sounds"),BString("None")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-ScreenSaver"),BString("None")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Media"),BString("None")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Shortcuts"),BString("Hotkey")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-DataTranslations"),BString("None")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-DeskbarPreferences"),BString("None")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Be-PRNT"),BString("None")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Appearance"),BString("Font Size Color")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Backgrounds"),BString("Wallpaper Workspaces")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-BluetoothPrefs"),BString("Connection Bluetooth")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-FileTypes"),BString("Info")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Keyboard"),BString("Keys")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Keymap"),BString("Layout")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Locale"),BString("Language Translation Regional")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Mail"),BString("Inbox")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Notifications"),BString("Push Alert")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Repositories"),BString("Source Packages")));
	RelatedKeywords.push_back(make_pair(BString("application/x-vnd.Haiku-Screen"),BString("Resolution Dimensions")));

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
			
	for(int i=0; i < sizeof(AppearanceSign)/sizeof(AppearanceSign[0]) ; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", AppearanceSign[i]);
		
		bGetName(AppearanceSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		NameButton[fAppName] = button;
		bSetIcon(button, AppearanceSign[i]);	
		layout = AppearanceLayout->AddView(button);
		vSystemApps.push_back(fAppName);
	}	// Appearance
	
	for(int i=0; i < sizeof(ConnectivitySign)/sizeof(ConnectivitySign[0]) ; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", ConnectivitySign[i]);
	
		bGetName(ConnectivitySign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		NameButton[fAppName] = button;
		bSetIcon(button, ConnectivitySign[i]);	
		layout = ConnectivityLayout->AddView(button);
		vSystemApps.push_back(fAppName);
	}	// Connectivity
	
	for(int i=0; i < sizeof(IOSign)/sizeof(IOSign[0]) ; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", IOSign[i]);
	
		bGetName(IOSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		NameButton[fAppName] = button;
		bSetIcon(button, IOSign[i]);	
		layout = IOLayout->AddView(button);
		vSystemApps.push_back(fAppName);
	} 	// Input/Output
 
	for(int i=0; i < sizeof(SystemSign)/sizeof(SystemSign[0]) ; i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", SystemSign[i]);
	
		bGetName(SystemSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);
		button->SetFlat(true);
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		NameButton[fAppName] = button;
		bSetIcon(button, SystemSign[i]);	
		layout = SystemLayout->AddView(button);
		vSystemApps.push_back(fAppName);
	}	// System

	for(int i=0; i < sizeof(UncategorizedSign)/sizeof(UncategorizedSign[0]); i++) {
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", UncategorizedSign[i]);
	
		bGetName(UncategorizedSign[i], &fAppName);		
		BButton* button = new BButton(fAppName, fAppName, mButton);		
		button->SetFlat(true);
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		NameButton[fAppName] = button;
		bSetIcon(button, UncategorizedSign[i]);	
		layout = UncategorizedLayout->AddView(button);
		vSystemApps.push_back(fAppName);
	}	// Uncategorized

	for(int i=0; i < vSign.size(); i++) {
		bGetName(vSign[i], &fAppName);	
		int flag_check = 0;
		if (!(std::find(vSystemApps.begin(), vSystemApps.end(), fAppName) != vSystemApps.end()))
		{ 	flag_check = 1;
   			mButton = new BMessage(MSG_SIGN);
			mButton->AddString("mime_val", vSign[i]);
			BButton* button = new BButton(fAppName, fAppName, mButton);
			button->SetFlat(true);
			button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
			NameButton[fAppName] = button;
			bSetIcon(button, vSign[i]);	
			layout = CustomLayout->AddView(button);
		}
		if(flag_check == 1)			 	
  			customStatus = 1;
	}	// Custom
	
	int splitCount = 0;
	for(map<BString, BString>::const_iterator it=NameSign.begin(); it != NameSign.end(); ++ it, ++ splitCount) {
		
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", it->second);
		
		BButton* button = new BButton(it->first, it->first, mButton);		
		button->SetFlat(true);
		bSetIcon(button, it->second);
		NameButtonAlphabetical[it->first] = button;
		button->SetExplicitMinSize(BSize(120.0, 45.0));
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		if(splitCount % 6 == 0 || splitCount == 0)
		{
			vView = new BGroupView(B_HORIZONTAL);
			vLayout = vView->GroupLayout();			
		}
		
		vLayout->AddView(button);
		if(splitCount % 6 == 0 || splitCount == 0)
			AlphabeticalLayout->AddView(vView);
	}	// Alphabetical	
	
	
	splitCount = 0;	
	for(map<BString, BString>::const_iterator it=AppsNameSign.begin(); it != AppsNameSign.end(); ++ it, ++ splitCount) {
		
		mButton = new BMessage(MSG_SIGN);
		mButton->AddString("mime_val", it->second);
		
		BButton* button = new BButton(it->first, it->first, mButton);		
		button->SetFlat(true);
		bSetIcon(button, it->second);
		NameButtonApps[it->first] = button;
		button->SetExplicitMinSize(BSize(120.0, 45.0));
		button->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));
		if(splitCount == 0 || splitCount % 6 == 0)
		{
			vView = new BGroupView(B_HORIZONTAL);
			vLayout = vView->GroupLayout();		
		}
		
		vLayout->AddView(button);
		if(splitCount % 6 == 0)
			AppsLayout->AddView(vView);
	}	//Apps		
}	

void
MainWindow::PrefSource() {
	
	fetchPreflets(B_USER_PREFERENCES_DIRECTORY);
	fetchPreflets(B_SYSTEM_PREFERENCES_DIRECTORY);
	fetchPreflets(B_PREFERENCES_DIRECTORY);
}
void
MainWindow::AppSource() {
	
	fetchApps(B_USER_APPS_DIRECTORY);
	fetchApps(B_SYSTEM_APPS_DIRECTORY);
	fetchApps(B_APPS_DIRECTORY);
}
void
MainWindow::fetchPreflets(directory_which path_pref) {

	BPath path;	BDirectory	directory;
	find_directory(path_pref, &path, true);
		
	directory.SetTo(path.Path());
		
	while(directory.GetNextRef(&ref)==B_OK) {
		char sign[B_MIME_TYPE_LENGTH];
		entry.SetTo(&ref, false);		
		entry.GetPath(&path);	
		BFile file(&entry, B_READ_ONLY);
		BAppFileInfo fileinfo(&file);
		fileinfo.GetSignature(sign);
		vPath.push_back(path.Path());	//Pushing path		
		if (std::find(vSign.begin(), vSign.end(), sign) == vSign.end())
		vSign.push_back(sign);			//Pushing sign
		sAllPreflets.insert(sign);
		bGetName(sign, &fAppName);
		vName.push_back(fAppName);		//Pushing name
		NameSign[fAppName]=sign;
	}	
}

void
MainWindow::fetchApps(directory_which path_pref) {

	
	BPath path;	BDirectory	directory;
	find_directory(path_pref, &path, true);
		
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
	fAppMenu->AddItem(new BMenuItem("Quit", new BMessage(kMenuAppQuit), 
	'Q', B_COMMAND_KEY));
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
	root = new BGroupLayout(B_VERTICAL, 0);
	this->SetLayout(root);
	
	root->AddView(fMenuBar);
	vView = new BGroupView(B_VERTICAL);
	vLayout = vView->GroupLayout();
	this->AddChild(vView);
	vLayout->AddView(fSearchBox);
	vLayout->SetInsets(2);	

	SearchSplitGroup = new BSplitView(B_HORIZONTAL);
	SearchSplitGroup->SetName("Splitter");
	BLayoutBuilder::Split<>(SearchSplitGroup)
			.Add(tSearch)
			.Add(cApps);
			
	SearchQuery = new BStringView("Search Text","");	
	// SearchLayout->AddView(SearchQuery);
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
	fCustomBox = new BBox((char*)NULL);
	fSearchBox = new BBox((char*)NULL);
		
	fAlphabeticalBox->SetLabel("All Preferences [A-Z]");
	fAppearanceBox->SetLabel("Appearance Preferences:");
	fAppsBox->SetLabel("All Apps [A-Z]");
	fConnectivityBox->SetLabel("Connectivity Preferences:");
	fIOBox->SetLabel("Input/Output Preferences:");
	fSystemBox->SetLabel("System Preferences:");
	fUncategorizedBox->SetLabel("Uncategorized:");
	fCustomBox->SetLabel("Custom Preferences:");
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
	
	CustomLayout = BLayoutBuilder::Group<>
		(fCustomBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	SearchLayout = BLayoutBuilder::Group<>
		(fSearchBox, B_VERTICAL, 0)
		.SetInsets(15)
	.Layout();
	
	tSearch = new BTextControl("Search:", "Enter query here: ", NULL, NULL);
	tSearch->SetModificationMessage(new BMessage(QUERY));
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
	BRect bRect(0, 0.0, B_LARGE_ICON - 1, B_LARGE_ICON - 1);
	BBitmap *icon = new BBitmap(bRect, B_RGBA32);	
	
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
	FlatTrue();
	if(checked % 2 == 0) {
		
	if(tSearchLength > 1) {
		
	vTemp.clear();
	for(int i = 0 ; i < vName.size() ; i++) 
  		if(vName[i].IFindFirst(*Query) != B_ERROR) {
			vTemp.push_back(vName[i]);
		}
	
	for(int i=0;i<RelatedKeywords.size();i++) {
		if(RelatedKeywords[i].second.IFindFirst(*Query) != B_ERROR
			&& RelatedKeywords[i].second != "None") {			
				bGetName(RelatedKeywords[i].first, &fAppName);
				vTemp.push_back(fAppName);
		}
	}
	FlatFalse(vTemp);	
	}
	}
	else {
				
	if(tSearchLength > 2) {
	vTemp.clear();
	for(int i = 0 ; i < vAppsName.size() ; i++) 
  		if(vAppsName[i].IFindFirst(*Query) != B_ERROR) {
			vTemp.push_back(vAppsName[i]);
		}	
	FlatFalse(vTemp);	
	}
	}	
}	

void
MainWindow::FlatFalse(vector<BString>& vTemp) {
	
	if(checked % 2 == 0) {
	for(int i = 0 ; i < vTemp.size() ; i ++ ) {
		NameButton[vTemp[i]]->SetFlat(false);		
		NameButton[vTemp[i]]->SetViewColor((rgb_color) {64,64,64,255});
		NameButton[vTemp[i]]->SetFont(be_bold_font);
		NameButtonAlphabetical[vTemp[i]]->SetFlat(false);		
		NameButtonAlphabetical[vTemp[i]]->SetViewColor((rgb_color) {64,64,64,255});
		NameButtonAlphabetical[vTemp[i]]->SetFont(be_bold_font);
	}
	}
	else {
		for(int i = 0 ; i < vTemp.size() ; i ++ ) {
		NameButtonApps[vTemp[i]]->SetFlat(false);		
		NameButtonApps[vTemp[i]]->SetViewColor((rgb_color) {64,64,64,255});
		NameButtonApps[vTemp[i]]->SetFont(be_bold_font);
	}
	}			
}

void
MainWindow::FlatTrue() {	

	if(checked % 2 == 0) {
	for(int i = 0 ; i < vName.size() ; ++i) {
		NameButton[vName[i]]->SetFlat(true);
		NameButton[vName[i]]->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		NameButton[vName[i]]->SetFont(be_plain_font);
		NameButtonAlphabetical[vName[i]]->SetFlat(true);
		NameButtonAlphabetical[vName[i]]->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		NameButtonAlphabetical[vName[i]]->SetFont(be_plain_font);
	}	
	}
	else {
		for(int i = 0 ; i < vAppsName.size() ; ++ i ) {
		NameButtonApps[vAppsName[i]]->SetFlat(true);		
		NameButtonApps[vAppsName[i]]->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
		NameButtonApps[vAppsName[i]]->SetFont(be_plain_font);
	}
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
  		if(customStatus==1) vLayout->AddView(fCustomBox);
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
	vLayout->RemoveView(fCustomBox);
	vLayout->AddView(fAlphabeticalBox);
}

void
MainWindow::mergeLayoutsApps() {
	
	if(mCategory->IsMarked()) {
		vLayout->RemoveView(fAppearanceBox);
		vLayout->RemoveView(fIOBox);
		vLayout->RemoveView(fCustomBox);
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
	
	if(checked % 2 ==0) { 
		vLayout->RemoveView(fAppsBox);  
		if(!mCategory->IsMarked())
          	mergeLayoutsCategory();	
		}
}

void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {
        	case B_APPS:
        	{	
        		cApps->SetEnabled(true);
        		checked++;
        		mergeLayoutsApps();         		
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
            	if(checked % 2 != 0)
            	{
            		BAlert* alert = new BAlert("AppsCategory", 
            		"No Categorization available for Apps", "OK");
            		alert->Go();
            	}
            	if(!mCategory->IsMarked() && checked % 2 == 0)
            		mergeLayoutsCategory();
            		 
           	  		break;
            }
            case kAlphabeticalwise:
            {
            	if(!mAlphabetical->IsMarked() && checked % 2 ==0)
            		mergeLayoutsAlphabetical();
                break;
            }
		}
}
