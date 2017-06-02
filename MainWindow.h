/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <View.h>
#include <Window.h>
#include <Button.h>
#include <Box.h>
#include <Application.h>
#include <LayoutBuilder.h>
#include <MenuBar.h>
#include <TextControl.h>
#include <MenuItem.h>


class MainWindow : public BWindow {
public:
                    MainWindow();
    virtual void    MessageReceived(BMessage* message);
    virtual bool    QuitRequested();
private:
            static const int kMenuAppQuit	= 0000;
            static const int kAlphabeticalwise	= 0001;
            static const int kCategorywise	= 0002;

            BMenuBar*   fMenuBar;
            BMenuItem*  fItem;
            BMenu*      fAppMenu;
            BBox*       fInputBox;
            BBox*       fAppearanceBox;
            BBox*       fNetworkBox;
            BTextControl*   fSearch;
};

#endif
