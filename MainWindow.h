/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <new>
#include <Alert.h>
#include <string>
#include <Directory.h>
#include <FindDirectory.h>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <string.h>
#include <View.h>
#include <Window.h>
#include <Button.h>
#include <Box.h>
#include <Mime.h>
#include <Bitmap.h>
#include <File.h>
#include <Entry.h>
#include <IconUtils.h>
#include <Resources.h>
#include <image.h>
#include <vector>
#include <Node.h>
#include <NodeInfo.h>
#include <AppFileInfo.h>
#include <ListView.h>
#include <Application.h>
#include <GroupLayoutBuilder.h>
#include <LayoutBuilder.h>
#include <LayoutItem.h>
#include <LocaleRoster.h>
#include <InterfaceKit.h>
#include <MenuBar.h>
#include <Path.h>
#include <PathFinder.h>
#include <TextControl.h>
#include <ScrollView.h>
#include <StringView.h>
#include <MenuItem.h>
#include <ControlLook.h>
#include <GroupView.h>
#include <Roster.h>
#include <IconButton.h>
#include "CategorySettingWindow.h"

class CategorySettingWindow;

enum {
	MSG_SIGN					=  'axyz',
	QUERY						=  'srch',
	B_APPS						=  'apps',
	B_PREFS						=	'pref',
	kMenuAppQuit				=	0000,
	kAlphabeticalwise			=	0001,
	kCategorywise				=	0002,
	kCategoryLaunch				=	0003,
};

class MainWindow : public BWindow {
public:
                    MainWindow();
	virtual	void    MessageReceived(BMessage* message);
			void	bSetIcon(BButton* button, BString AppSign);
			void	bGetName(BString AppSign, BString* fAppName);
	virtual bool    QuitRequested();
    		void	fSearch();
    		void	buildMenubar();
    		void	buildBox();
    		void	buildLayout();
    		void	fetchPreflets();
    		void	fetchApps();
    		void	populateLayout();
    		void	mergeLayouts();
    		void 	mergeLayoutsCategory();
    		void	mergeLayoutsAlphabetical();
    		void	mergeLayoutsApps();
    		void	FlatTrue();
    		void 	FlatFalse(vector<BString>& vTemp);
			vector<BString>			vCustomApps;	
private:
			BMessage*				mMenu;
			BMessage* 				mButton;
			BGroupLayout*			AppsLayout;
			BGroupLayout*			AlphabeticalLayout;
			BGroupLayout*			AppearanceLayout;
			BGroupLayout*			IOLayout;
			BGroupLayout*			ConnectivityLayout;
			BGroupLayout*			SystemLayout;
			BGroupLayout*			UncategorizedLayout;
			BGroupLayout*			CustomLayout;
			BGroupLayout*			MainLayout;
			BGroupLayout*			SearchLayout;
			BGroupLayout*			root;
			BGroupLayout*			vLayout;
			BLayoutItem* 			layout;			
			BSplitView* 			SplitGroup;
			BSplitLayout*			SplitLayout;
			BSplitView* 			SearchSplitGroup;
			BSplitLayout*			SearchSplitLayout;
			BGroupView*				vView;
			BStringView* 			SearchQuery;
			BString					fAppName;
			BString					fSystemAppName;
          	BMenuBar*           	fMenuBar;
          	BMenuItem*          	mCategory;
          	BMenuItem*          	mAlphabetical;
          	BMenuItem*          	fItem;
         	BMenu*              	fAppMenu;
         	BBox*					fAlphabeticalBox;
         	BBox*					fAppsBox;
        	BBox*               	fAppearanceBox;  
         	BBox*              	 	fConnectivityBox;
         	BBox*               	fSystemBox;
         	BBox*					fSearchBox;
         	BBox*           		fUncategorizedBox;
         	BBox*               	fIOBox;
         	BBox*					fCustomBox;
         	BPath					path;
         	BDirectory				directory;
         	entry_ref				ref;
         	BEntry					entry;
         	BTextControl*       	tSearch;
         	BCheckBox* 				cApps;
         	vector<BString> 		vSign;				
			vector<BString> 		vPath;				
			vector<BString> 		vName;
			vector<BString>			vSystemApps;
			vector<BString> 		vAppsSign;				
			vector<BString> 		vAppsPath;				
			vector<BString> 		vAppsName;
			vector<BString> 		vTemp;  				
			map<BString, BString>	NameSign;	
			map<BString, BString>	AppsNameSign;
			map<BString, BButton*>	NameButton;
			map<BString, BButton*>	NameButtonAlphabetical;
			map<BString, BButton*>	NameButtonApps;
         	char*					fAppSig;
         	int						checked;
         	CategorySettingWindow*	fCategorySettingWindow;
};

#endif
