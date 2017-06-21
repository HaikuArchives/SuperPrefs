/*
 * Copyright 2006-2009, Stephan Aßmus <superstippi@gmx.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */
#ifndef PAD_VIEW_H
#define PAD_VIEW_H

#include <View.h>
#include <StringView.h>

class BGroupLayout;
class LaunchButton;

#define DEFAULT_ICON_SIZE 32

class PadView : public BView {
public:
								PadView(const char* name);
	virtual						~PadView();

	// BView interface
	virtual	void				Draw(BRect updateRect);
	virtual	void				MessageReceived(BMessage* message);
	virtual	void				MouseDown(BPoint where);
	virtual	void				MouseUp(BPoint where);

	// PadView
			void				AddButton(LaunchButton* button, 
									const char* fLabel2,
									LaunchButton* beforeButton = NULL);
			void				DisplayMenu(BPoint where,
									LaunchButton* button = NULL) const;
			void				SetOrientation(enum orientation orientation);
			enum orientation	Orientation() const;
			uint32				IconSize() const;
			BString*			fLabel;
			void				SetIgnoreDoubleClick(bool refuse);
			bool				IgnoreDoubleClick() const;

private:
			BPoint				fDragOffset;
			bool				fDragging;
			bigtime_t			fClickTime;
			BStringView*		fLabelView;			
			BGroupLayout*		fButtonLayout;
			uint32				fIconSize;
};

#endif // PAD_VIEW_H
