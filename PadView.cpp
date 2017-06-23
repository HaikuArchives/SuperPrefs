/*
 * Copyright 2006-2009, Stephan Aßmus <superstippi@gmx.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */

#include "PadView.h"

#include <stdio.h>
#include <Application.h>
#include <Catalog.h>
#include <GroupLayout.h>
#include <MenuItem.h>
#include <Message.h>
#include <PopUpMenu.h>
#include <Region.h>
#include <Screen.h>
#include <SpaceLayoutItem.h>
#include <String.h>

#include "LaunchButton.h"
#include "MainWindow.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "LaunchBox"

static bigtime_t sActivationDelay = 40000;
enum {
	MSG_TOGGLE_LAYOUT			= 'tgll',
	MSG_SET_IGNORE_DOUBLECLICK	= 'strd'
};


PadView::PadView(const char* name)
	: BView(name, B_WILL_DRAW, NULL),
	  fDragging(false),
	  fClickTime(0),
	  fButtonLayout(new BGroupLayout(B_VERTICAL, 4)),
	  fIconSize(DEFAULT_ICON_SIZE)
{
	SetViewColor(B_TRANSPARENT_32_BIT);
	SetLowColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	get_click_speed(&sActivationDelay);
	fButtonLayout->SetInsets(2, 7, 2, 2);
	SetLayout(fButtonLayout);
}


PadView::~PadView()
{
}


void
PadView::Draw(BRect updateRect)
{
	rgb_color background = LowColor();
	rgb_color light = tint_color(background, B_LIGHTEN_MAX_TINT);
	rgb_color shadow = tint_color(background, B_DARKEN_2_TINT);
	BRect r(Bounds());
	FillRect(r, B_SOLID_LOW);
}


void
PadView::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_TOGGLE_LAYOUT:
			if (fButtonLayout->Orientation() == B_HORIZONTAL) {
				// fButtonLayout->SetInsets(2, 7, 2, 2);
				// fButtonLayout->SetOrientation(B_VERTICAL);
				fButtonLayout->SetInsets(7, 2, 2, 2);
				fButtonLayout->SetOrientation(B_HORIZONTAL);
			} else {
				fButtonLayout->SetInsets(7, 2, 2, 2);
				fButtonLayout->SetOrientation(B_HORIZONTAL);
			}
			break;
		case MSG_SET_IGNORE_DOUBLECLICK:
			SetIgnoreDoubleClick(!IgnoreDoubleClick());
			break;

		default:
			BView::MessageReceived(message);
			break;
	}
}


void
PadView::MouseDown(BPoint where)
{

}


void
PadView::MouseUp(BPoint where)
{

}

void
PadView::AddButton(LaunchButton* button, LaunchButton* beforeButton)
{
	
	char name[B_FILE_NAME_LENGTH];
	entry_ref ref;	
	be_roster->FindApp(button->AppSignature(), &ref);
	BEntry entry(&ref);
	entry.GetName(name);

	fLabelView = new BStringView("Label View:",NULL);
	fLabelView->SetText(name);
	
	fButtonLayout->AddView(fLabelView);
	if (beforeButton) {
		fButtonLayout->AddView(fButtonLayout->IndexOfView(beforeButton), button);
	}
	else {
		fButtonLayout->AddView(button);
	
	}

}

void
PadView::DisplayMenu(BPoint where, LaunchButton* button) const
{
	//Menu removed
}


void
PadView::SetOrientation(enum orientation orientation)
{
	if (orientation == B_VERTICAL) {
		// fButtonLayout->SetInsets(2, 7, 2, 2);
		// fButtonLayout->SetOrientation(B_VERTICAL);
		fButtonLayout->SetInsets(2, 2, 2, 2);
		fButtonLayout->SetOrientation(B_HORIZONTAL);
	} else {
		fButtonLayout->SetInsets(2, 2, 2, 2);
		fButtonLayout->SetOrientation(B_HORIZONTAL);
	}
}


enum orientation
PadView::Orientation() const
{
	return fButtonLayout->Orientation();
}


uint32
PadView::IconSize() const
{
	return fIconSize;
}


void
PadView::SetIgnoreDoubleClick(bool refuse)
{
	LaunchButton::SetIgnoreDoubleClick(refuse);

}


bool
PadView::IgnoreDoubleClick() const
{
	return LaunchButton::IgnoreDoubleClick();
}
