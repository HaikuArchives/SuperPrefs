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
	MSG_SIGN					= 'axyz',
};

class MainWindow : public BWindow {
public:
                    MainWindow();
    virtual void    MessageReceived(BMessage* message);
			void	bSetIcon(BButton* button, BString AppSign);
			void	bGetName(BString AppSign, BString* fAppName);
    virtual bool    QuitRequested();
 
private:
            static const int kMenuAppQuit	= 0000;
            static const int kAlphabeticalwise	= 0001;
            static const int kCategorywise	= 0002;
			
			BMessage* 			mButton;
			BGroupLayout*		AppearanceLayout;
			BGroupLayout*		IOLayout;
			BGroupLayout*		ConnectivityLayout;
			BGroupLayout*		SystemLayout;
			BGroupLayout*		UncategorizedLayout;
			BLayoutItem* 		layout;
			BString				fAppName;
            BMenuBar*           fMenuBar;
            BMenuItem*          fItem;
            BMenu*              fAppMenu;
            BBox*               fAppearanceBox;  
            BBox*               fConnectivityBox;
            BBox*               fSystemBox;
            BBox*               fUncategorizedBox;
            BBox*               fIOBox;
            BTextControl*       fSearch;
            char*				fAppSig;                      
};

#endif
