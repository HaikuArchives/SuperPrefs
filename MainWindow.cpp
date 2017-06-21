/*
 * Author:
 *		Anirudh M, m.anirudh18@gmail.com
 *
 * Copyright 2017. All rights reserved.
 * Distributed under the terms of the MIT license.
 */

#include "MainWindow.h"


MainWindow::MainWindow()
	:
	BWindow(BRect(), "SuperPrefs",B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
	 B_QUIT_ON_WINDOW_CLOSE),
		fAppearancePadView(new PadView("Appearance")),
		fInputPadView(new PadView("Input")),
		fNetworkPadView(new PadView("Network"))
{

	ResizeTo(720, 420);
	CenterOnScreen();
	
	//Menubar items
	
	fMenuBar = new BMenuBar("MenuBar");
	fAppMenu = new BMenu("File");
	fAppMenu->AddItem(new BMenuItem("Close", new BMessage(kMenuAppQuit), 
	'C', B_COMMAND_KEY));
	fMenuBar->AddItem(fAppMenu);
    fAppMenu = new BMenu("Settings");
    fItem = new BMenuItem("Sort Category wise",	new BMessage(kCategorywise));
	fItem->SetMarked(true);
    fAppMenu->AddItem(fItem);
    fItem = new BMenuItem("Sort Alphabetically", new BMessage(kAlphabeticalwise));
	fItem->SetMarked(false);
    fAppMenu->AddItem(fItem);fMenuBar->AddItem(fAppMenu);

    //Search Bar

	fSearch = new BTextControl("SearchBox", "Search:", NULL, NULL);
	fSearch->MakeFocus(true);
	
	//Box Layouts

	fAppearanceBox = new BBox((char*) NULL);
	fInputBox = new BBox((char*)NULL);
	fNetworkBox = new BBox((char*)NULL);
	
	fAppearanceBox->SetLabel("Appearance Preferences:");
	fNetworkBox->SetLabel("Network Preferences:");
	fInputBox->SetLabel("Input Preferences:");
	
	//Appearance

	LaunchButton* button = new LaunchButton("launch button", NULL,
		new BMessage(MSG_LAUNCH));
	button->SetTo("application/x-vnd.Haiku-Appearance", true);	//1
	fAppearancePadView->AddButton(button, "Appearance");
	//BString work;
	//work.SetTo("hi");
	//fAppearancePadView->SendLabel("s");
	LaunchButton* button2 = new LaunchButton("launch button2", NULL,
		new BMessage(MSG_LAUNCH));
	button2->SetTo("application/x-vnd.Haiku-Backgrounds", true);	//2
	fAppearancePadView->AddButton(button2, "Backgrounds");

	LaunchButton* button3 = new LaunchButton("launch button3", NULL,
		new BMessage(MSG_LAUNCH));
	button3->SetTo("application/x-vnd.Haiku-Screen", true);	//3
	fAppearancePadView->AddButton(button3, "Screen");
	
	fAppearancePadView->SetOrientation((enum orientation)orientation); //orientation-app
	
	BLayoutBuilder::Group<>(fAppearanceBox, B_VERTICAL, 0)
		.SetInsets(15)
		.Add(fAppearancePadView);
		
	//End of appearance
	
	//Input 
	
	LaunchButton* button4 = new LaunchButton("launch button4", NULL,
		new BMessage(MSG_LAUNCH));									//4
	button4->SetTo("application/x-vnd.Haiku-Keyboard", true);
	fInputPadView->AddButton(button4, "Keyboard");

	LaunchButton* button5 = new LaunchButton("launch button5", NULL,
		new BMessage(MSG_LAUNCH));									//5
	button5->SetTo("application/x-vnd.Haiku-Keymap", true);
	fInputPadView->AddButton(button5, "Keymap");

	LaunchButton* button6 = new LaunchButton("launch button6", NULL,
		new BMessage(MSG_LAUNCH));									//6
	button6->SetTo("application/x-vnd.Haiku-Mouse", true);
	fInputPadView->AddButton(button6, "Mouse");

	fInputPadView->SetOrientation((enum orientation)orientation); //orientation - input

	BLayoutBuilder::Group<>(fInputBox, B_VERTICAL, 0)
		.SetInsets(15)
		.Add(fInputPadView);
	
	//End of Input

	//Network
	
	LaunchButton* button7 = new LaunchButton("launch button7", NULL,
			new BMessage(MSG_LAUNCH));
	button7->SetTo("application/x-vnd.Haiku-Network", true);	//7
	fNetworkPadView->AddButton(button7, "Network");
	LaunchButton* button8 = new LaunchButton("launch button8", NULL,
		new BMessage(MSG_LAUNCH));
	button8->SetTo("application/x-vnd.Haiku-Locale", true);		//8
	fNetworkPadView->AddButton(button8, "Locale");
	LaunchButton* button9 = new LaunchButton("launch button9", NULL,
		new BMessage(MSG_LAUNCH));
	button9->SetTo("application/x-vnd.Be-PRNT", true);			//9
	fNetworkPadView->AddButton(button9, "Printer");

	//BString labelString = label.String();
	LaunchButton* button10 = new LaunchButton("launch button10", NULL,
		 new BMessage(MSG_LAUNCH));
	button10->SetTo("application/x-vnd.Haiku-RemoteDesktop", true);			//9
	fNetworkPadView->AddButton(button10, "Remote Desktop");

	LaunchButton* button11 = new LaunchButton("launch button11", NULL,
		 new BMessage(MSG_LAUNCH));
	button11->SetTo("application/x-vnd.Haiku-BluetoothPrefs", true);			//9
	fNetworkPadView->AddButton(button11, "Bluetooth");

	fNetworkPadView->SetOrientation((enum orientation)orientation); //orientation-net
	fNetworkBox->SetLabel("Network Preferences:");
	BLayoutBuilder::Group<>(fNetworkBox, B_VERTICAL, 0)
		.SetInsets(15)
		.Add(fNetworkPadView);
	
	//End of Network
	char name[B_FILE_NAME_LENGTH];
	entry_ref ref;
	be_roster->FindApp("application/x-vnd.Haiku-RemoteDesktop", &ref);
	BEntry entry(&ref);
	entry.GetName(name);
	BString fString;
	fString.SetTo(name);
	BStringView* SampleText = new BStringView("Sample",fString);	
	
	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.AddGroup(B_VERTICAL, 0)
			.Add(fMenuBar)
			.Add(fSearch)
				.SetInsets(4)
			.Add(fAppearanceBox)
			.Add(fInputBox)
			.Add(fNetworkBox)
			//.Add(SampleText)
	.End();
}


bool
MainWindow::QuitRequested() {
    return true;
}

//bool
//MainWindow::kCall() {
//
//char name[B_FILE_NAME_LENGTH];
//entry_ref ref;
//be_roster->FindApp("application/x-vnd.Haiku-Locale", &ref);
//BEntry entry(&ref);
//entry.GetName(name);
//
//return 0;
//
//}
void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {
			case MSG_SETTINGS_CHANGED: {
				fSettingsChanged = true;
				break;}
			case MSG_LAUNCH:
			{
			BView* pointer;
			if (message->FindPointer("be:source", (void**)&pointer) < B_OK)
				break;
			LaunchButton* button = dynamic_cast<LaunchButton*>(pointer);
			if (button == NULL)
				break;
			BString errorMessage;
			bool launchedByRef = false;
			if (button->Ref()) {
				BEntry entry(button->Ref(), true);
				if (entry.IsDirectory()) {
					// open in Tracker
					BMessenger messenger("application/x-vnd.Be-TRAK");
					if (messenger.IsValid()) {
						BMessage trackerMessage(B_REFS_RECEIVED);
						trackerMessage.AddRef("refs", button->Ref());
						status_t ret = messenger.SendMessage(&trackerMessage);
						if (ret < B_OK) {
							errorMessage = "Failed to send "
							"'open folder' command to Tracker.\n\nError: ";
							errorMessage << strerror(ret);
						} else
							launchedByRef = true;
					} else
						errorMessage = ("Failed to open folder - is Tracker "
							"running?");
				}
			} else {
					status_t ret = be_roster->Launch(button->Ref());
					if (ret < B_OK && ret != B_ALREADY_RUNNING) {
						BString errStr("Failed to launch '%1'.\n"
							"\nError:");
						BPath path(button->Ref());
						if (path.InitCheck() >= B_OK)
							errStr.ReplaceFirst("%1", path.Path());
						else
							errStr.ReplaceFirst("%1", button->Ref()->name);
						errorMessage << errStr.String() << " ";
						errorMessage << strerror(ret);
					} else
						launchedByRef = true;
				}

			if (!launchedByRef && button->AppSignature()) {
				status_t ret = be_roster->Launch(button->AppSignature());
				if (ret != B_OK && ret != B_ALREADY_RUNNING) {
					BString errStr("\n\nFailed to launch application "
						"with signature '%2'.\n\nError:");
					errStr.ReplaceFirst("%2", button->AppSignature());
					errorMessage << errStr.String() << " ";
					errorMessage << strerror(ret);
				} else {
					// clear error message on success (might have been
					// filled when trying to launch by ref)
					errorMessage = "";
				}
			} else if (!launchedByRef) {
				errorMessage = "Failed to launch 'something', "
					"error in Pad data.";
			}
			if (errorMessage.Length() > 0) {
				BAlert* alert = new BAlert("error", errorMessage.String(),
					"Bummer", NULL, NULL, B_WIDTH_FROM_WIDEST);
				alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
				alert->Go(NULL);
			}
			break;
		}
            case kMenuAppQuit:
            {
                be_app->PostMessage(B_QUIT_REQUESTED);
                break;
            }
            case kCategorywise:
                break;
            case kAlphabeticalwise:
                break;
        }
}
