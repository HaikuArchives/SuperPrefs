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

enum {
	MSG_SIGN					=  'axyz',
	QUERY						=  'srch',
	kMenuAppQuit				=	0000,
	kAlphabeticalwise			=	0001,
	kCategorywise				=	0002,
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
    		void	populateLayout();
    		void	mergeLayouts();

 
private:
			BMessage* 				mButton;
			BGroupLayout*			AppearanceLayout;
			BGroupLayout*			IOLayout;
			BGroupLayout*			ConnectivityLayout;
			BGroupLayout*			SystemLayout;
			BGroupLayout*			UncategorizedLayout;
			BGroupLayout*			MainLayout;
			BGroupLayout*			LogLayout;
			BLayoutItem* 			layout;
			BString					fAppName;
          	BMenuBar*           	fMenuBar;
          	BMenuItem*          	fItem;
         	BMenu*              	fAppMenu;
        	BBox*               	fAppearanceBox;  
         	BBox*              	 	fConnectivityBox;
         	BBox*               	fSystemBox;
         	BBox*					fLogBox;
         	BBox*           		fUncategorizedBox;
         	BBox*               	fIOBox;
         	BPath					path;
         	BDirectory				directory;
         	entry_ref				ref;
         	BEntry					entry;
         	BTextControl*       	tSearch;
         	vector<BString> 		vSign;				
			vector<BString> 		vPath;				
			vector<BString> 		vName;
			vector<BString> 		vTemp;  				
			map<BString, BString>	NameSign;	
			map<BString, BButton*>	NameButton;
         	char*					fAppSig;                      
};

#endif
