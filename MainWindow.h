/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PadView.h"
#include "LaunchButton.h"
#include <new>
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

class PadView;

enum {
	msg_sign					= 'axyz',
};

class MainWindow : public BWindow {
public:
                    MainWindow();
    virtual void    MessageReceived(BMessage* message);

    virtual bool    QuitRequested();
   	PadView*		fNetworkPadView;
    PadView*		fAppearancePadView;
    PadView*		fInputPadView;
  
private:
            static const int kMenuAppQuit	= 0000;
            static const int kAlphabeticalwise	= 0001;
            static const int kCategorywise	= 0002;
            static const int MSG_SETTINGS_CHANGED = 0003;		

            BMenuBar*           fMenuBar;
            BMenuItem*          fItem;
            BMenu*              fAppMenu;
            BBox*               fInputBox;
            BBox*               fAppearanceBox;  
            BBox*               fNetworkBox;
            BBox*               fSampleBox;
            BTextControl*       fSearch;
            char*				fAppSig;           
            bool				fSettingsChanged;
            int32 				orientation;
};

#endif
