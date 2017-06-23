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
	fSampleBox = new BBox((char*)NULL);
	
	fAppearanceBox->SetLabel("Appearance Preferences:");
	fNetworkBox->SetLabel("Network Preferences:");
	fInputBox->SetLabel("Input Preferences:");
	fSampleBox->SetLabel("Sample Box - Test Area");
	
	BString AppearanceSign[3] = {"application/x-vnd.Haiku-Appearance",
	 "application/x-vnd.Haiku-Backgrounds", "application/x-vnd.Haiku-Screen" };
	 
	AppearanceLayout = BLayoutBuilder::Group<>
		(fAppearanceBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		msg = new BMessage(msg_sign);
		msg->AddString("mime_val", AppearanceSign[i]);
	
		bGetName(AppearanceSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, msg);
		bSetIcon(bSample, AppearanceSign[i]);	
		BLayoutItem* layout = AppearanceLayout->AddView(bSample);
	}
	
	BString InputSign[3] = {"application/x-vnd.Haiku-Keyboard",
	 "application/x-vnd.Haiku-Keymap", "application/x-vnd.Haiku-Mouse" };
	 
	InputLayout = BLayoutBuilder::Group<>
		(fInputBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		msg = new BMessage(msg_sign);
		msg->AddString("mime_val", InputSign[i]);
	
		bGetName(InputSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, msg);
		bSetIcon(bSample, InputSign[i]);	
		BLayoutItem* layout = InputLayout->AddView(bSample);
	}
		
	BString NetworkSign[3] = {"application/x-vnd.Be-MAIL",
	 "application/x-vnd.Haiku-Network", "application/x-vnd.Haiku-RemoteDesktop" };
	 
	NetworkLayout = BLayoutBuilder::Group<>
		(fNetworkBox, B_HORIZONTAL, 0)
		.SetInsets(15)
	.Layout();
	
	for(int i=0; i<3; i++) {
		msg = new BMessage(msg_sign);
		msg->AddString("mime_val", NetworkSign[i]);
	
		bGetName(NetworkSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, msg);
		bSetIcon(bSample, NetworkSign[i]);	
		BLayoutItem* layout = NetworkLayout->AddView(bSample);
	}
	
	BString AppSign[2] = {"application/x-vnd.Haiku-Locale",
	 "application/x-vnd.Haiku-BluetoothPrefs"};

	BGroupLayout* GroupLayout =	BLayoutBuilder::Group<>
		(fSampleBox, B_HORIZONTAL, 0)
			.SetInsets(10)
	.Layout();
	
	for(int i=0; i<2; i++) {
		msg = new BMessage(msg_sign);
		msg->AddString("mime_val", AppSign[i]);
	
		bGetName(AppSign[i], &fAppName);		
		BButton* bSample = new BButton(fAppName, fAppName, msg);
		bSetIcon(bSample, AppSign[i]);	
		BLayoutItem* layout = GroupLayout->AddView(bSample);
	}
	
	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.AddGroup(B_VERTICAL, 0)
			.Add(fMenuBar)
			.Add(fSearch)
				.SetInsets(4)
			.Add(fAppearanceBox)
			.Add(fInputBox)
			.Add(fNetworkBox)
			.Add(fSampleBox)
	.End();
}

void
MainWindow::bGetName(BString AppSign, BString* fAppName) {
	char name[B_FILE_NAME_LENGTH];
	entry_ref ref;	
	be_roster->FindApp(AppSign, &ref);
	BEntry entry(&ref);
	entry.GetName(name);
	fAppName->SetTo(name);
}
	
void 
MainWindow::bSetIcon(BButton* button, BString AppSign) {
	
	BMimeType mime(AppSign); 
	BRect bRect(0, 0.0, B_LARGE_ICON - 1, B_LARGE_ICON -1);
	BBitmap *icon = new BBitmap(bRect, B_CMAP8);	
	
	mime.GetIcon(icon, B_LARGE_ICON);
	button->SetIcon(icon);	
}

bool
MainWindow::QuitRequested() {
    return true;
}

void
MainWindow::MessageReceived(BMessage* message)
{
        switch(message->what) {
        	case msg_sign: {
        		 BString AppSign;
        		 AppSign = message->GetString("mime_val");
        		 be_roster->Launch(AppSign);        		  
        		break;
        	}        	
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
