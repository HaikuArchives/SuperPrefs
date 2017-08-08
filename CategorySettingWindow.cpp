/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */


#include "CategorySettingWindow.h"

CategorySettingWindow::CategorySettingWindow(vector<BString> vCustomApps) 
	: BWindow(BRect(),"Category Settings" 
		,B_TITLED_WINDOW, B_AUTO_UPDATE_SIZE_LIMITS ) {
			
			ResizeTo(400,400);
			CenterOnScreen();
			buildLayout(vCustomApps);	
}
void 
CategorySettingWindow::buildLayout(vector<BString> vCustomApps) {

	fCategoryMenu = new BPopUpMenu("Select Category..");
	
	fCategoryMenu->AddItem(new BMenuItem("Appearance",
		new BMessage(kSetCategory)));
	fCategoryMenu->AddItem(new BMenuItem("Input/Output",
		new BMessage(kSetCategory)));
	fCategoryMenu->AddItem(new BMenuItem("Connectivity",
		new BMessage(kSetCategory)));
	fCategoryMenu->AddItem(new BMenuItem("System",
		new BMessage(kSetCategory)));
	fCategoryMenu->AddItem(new BMenuItem("Uncategorized",
		new BMessage(kSetCategory)));	
	
	for(int i = 0; i<vCustomApps.size(); i++) {
		
		string* str = new string(vCustomApps[i]);
		*str += string(": ");
		CategoryField = new BMenuField("Category",
		str->c_str(), fCategoryMenu);
		CategoryField->SetAlignment(B_ALIGN_RIGHT);
	}
	
	BButton* bUpdate = new BButton("Apply Changes");
	
	fWindowView = new BView("Main Window View", 0);
	BLayoutBuilder::Group<>(fWindowView, B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING)
		.AddGroup(B_HORIZONTAL, B_USE_DEFAULT_SPACING)
			.Add(CategoryField)
		.End()
		.Add(bUpdate)
	.End();
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(fWindowView)
	.End();
}
	
