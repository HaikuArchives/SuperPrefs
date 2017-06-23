/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#ifndef APP_H
#define APP_H

#include "MainWindow.h"
#include <View.h>
#include <Window.h>
#include <Button.h>
#include <Application.h>
#include <LayoutBuilder.h>

class App: public BApplication
{
public:
                        App();
		void			AboutRequested();
		//void 			MessageReceived(BMessage* message);
private:
            MainWindow* fMainWindow;
};

#endif
