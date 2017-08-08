/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */
 
#ifndef CATEGORYSETTINGWINDOW_H
#define CATEGORYSETTINGWINDOW_H


#include <Window.h>
#include "MainWindow.h"

class CategorySettingWindow: public BWindow {
	
static const uint32 kSetCategory = 'mnpl';

public:
							CategorySettingWindow(vector<BString> vCustomApps);
		void				buildLayout(vector<BString> vCustomApps);							
private:
		BView*				fWindowView;
		BPopUpMenu*			fCategoryMenu;
		BMenuField* 		CategoryField;
		

};


#endif // CATEGORYSETTINGWINDOW_H
