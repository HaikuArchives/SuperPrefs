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
#include <fstream>
#include <vector>
#include "MainWindow.h"

class CategorySettingWindow: public BWindow {
	
static const uint32 kSetCategory = 'mnpl';

public:
							CategorySettingWindow();
		void				buildLayout();
		void				accessCat();
		void				postProcess(vector < pair<string, string> >& vAppCategory);							
private:
		BView*				fWindowView;
		BPopUpMenu*			fCategoryMenu;
		BMenuField* 		CategoryField;
		vector<BString>		vCustomApps;
		

};


#endif // CATEGORYSETTINGWINDOW_H
