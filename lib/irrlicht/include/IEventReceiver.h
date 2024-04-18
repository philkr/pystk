// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_EVENT_RECEIVER_H_INCLUDED__
#define __I_EVENT_RECEIVER_H_INCLUDED__

#include "ILogger.h"
#include "Keycodes.h"
#include "irrString.h"

namespace irr
{
	//! Enumeration for all event types there are.
	enum EEVENT_TYPE
	{
		//! An event of the graphical user interface.
		/** GUI events are created by the GUI environment or the GUI elements in response
		to mouse or keyboard events. When a GUI element receives an event it will either
		process it and return true, or pass the event to its parent. If an event is not absorbed
		before it reaches the root element then it will then be passed to the user receiver. */
		EET_GUI_EVENT = 0,

		//! A log event
		/** Log events are only passed to the user receiver if there is one. If they are absorbed by the
		user receiver then no text will be sent to the console. */
		EET_LOG_TEXT_EVENT,

		//! A user event with user data.
		/** This is not used by Irrlicht and can be used to send user
		specific data though the system. The Irrlicht 'window handle'
		can be obtained from IrrlichtDevice::getExposedVideoData()
		The usage and behavior depends on the operating system:
		Windows: send a WM_USER message to the Irrlicht Window; the
			wParam and lParam will be used to populate the
			UserData1 and UserData2 members of the SUserEvent.
		Linux: send a ClientMessage via XSendEvent to the Irrlicht
			Window; the data.l[0] and data.l[1] members will be
			casted to s32 and used as UserData1 and UserData2.
		MacOS: Not yet implemented
		*/
		EET_USER_EVENT,
		
		//! Pass on raw events from the OS
		EET_SYSTEM_EVENT,
		
		//! Application state events like a resume, pause etc.
		EET_APPLICATION_EVENT,

		//! This enum is never used, it only forces the compiler to
		//! compile these enumeration values to 32 bit.
		EGUIET_FORCE_32_BIT = 0x7fffffff

	};

	//! Enumeration for all mouse input events
	enum EMOUSE_INPUT_EVENT
	{
		//! Left mouse button was pressed down.
		EMIE_LMOUSE_PRESSED_DOWN = 0,

		//! Right mouse button was pressed down.
		EMIE_RMOUSE_PRESSED_DOWN,

		//! Middle mouse button was pressed down.
		EMIE_MMOUSE_PRESSED_DOWN,

		//! Left mouse button was left up.
		EMIE_LMOUSE_LEFT_UP,

		//! Right mouse button was left up.
		EMIE_RMOUSE_LEFT_UP,

		//! Middle mouse button was left up.
		EMIE_MMOUSE_LEFT_UP,

		//! The mouse cursor changed its position.
		EMIE_MOUSE_MOVED,

		//! The mouse wheel was moved. Use Wheel value in event data to find out
		//! in what direction and how fast.
		EMIE_MOUSE_WHEEL,

		//! Left mouse button double click.
		//! This event is generated after the second EMIE_LMOUSE_PRESSED_DOWN event.
		EMIE_LMOUSE_DOUBLE_CLICK,

		//! Right mouse button double click.
		//! This event is generated after the second EMIE_RMOUSE_PRESSED_DOWN event.
		EMIE_RMOUSE_DOUBLE_CLICK,

		//! Middle mouse button double click.
		//! This event is generated after the second EMIE_MMOUSE_PRESSED_DOWN event.
		EMIE_MMOUSE_DOUBLE_CLICK,

		//! Left mouse button triple click.
		//! This event is generated after the third EMIE_LMOUSE_PRESSED_DOWN event.
		EMIE_LMOUSE_TRIPLE_CLICK,

		//! Right mouse button triple click.
		//! This event is generated after the third EMIE_RMOUSE_PRESSED_DOWN event.
		EMIE_RMOUSE_TRIPLE_CLICK,

		//! Middle mouse button triple click.
		//! This event is generated after the third EMIE_MMOUSE_PRESSED_DOWN event.
		EMIE_MMOUSE_TRIPLE_CLICK,

		//! No real event. Just for convenience to get number of events
		EMIE_COUNT
	};

	//! Masks for mouse button states
	enum E_MOUSE_BUTTON_STATE_MASK
	{
		EMBSM_LEFT    = 0x01,
		EMBSM_RIGHT   = 0x02,
		EMBSM_MIDDLE  = 0x04,

		//! currently only on windows
		EMBSM_EXTRA1  = 0x08,

		//! currently only on windows
		EMBSM_EXTRA2  = 0x10,

		EMBSM_FORCE_32_BIT = 0x7fffffff
	};
    
    //! Enumeration for all touch input events
	enum ETOUCH_INPUT_EVENT
	{
		//! Touch was pressed down.
		ETIE_PRESSED_DOWN = 0,

		//! Touch was left up.
		ETIE_LEFT_UP,

		//! The touch changed its position.
		ETIE_MOVED,

		//! No real event. Just for convenience to get number of events
		ETIE_COUNT
	};
	
	enum ESYSTEM_EVENT_TYPE
	{
		//! From Android command handler for native activity messages
		ESET_ANDROID_CMD = 0,

		// TODO: for example ESET_WINDOWS_MESSAGE for win32 message loop events

		//! No real event, but to get number of event types
		ESET_COUNT
	};
	
	//! Enumeration for a commonly used application state events (it's useful mainly for mobile devices)
	enum EAPPLICATION_EVENT_TYPE
	{
		//! The application will be resumed.
		EAET_WILL_RESUME = 0,
		
		//! The application has been resumed.
		EAET_DID_RESUME,
		
		//! The application will be paused.
		EAET_WILL_PAUSE,
		
		//! The application has been paused.
		EAET_DID_PAUSE,

		//! The application will be terminated.
		EAET_WILL_TERMINATE,
		
		//! The application received a memory warning.
		EAET_MEMORY_WARNING,

		//! No real event, but to get number of event types.
		EAET_COUNT
	};

	namespace gui
	{

		class IGUIElement;

		//! Enumeration for all events which are sendable by the gui system
		enum EGUI_EVENT_TYPE
		{
			//! A gui element has lost its focus.
			/** GUIEvent.Caller is losing the focus to GUIEvent.Element.
			If the event is absorbed then the focus will not be changed. */
			EGET_ELEMENT_FOCUS_LOST = 0,

			//! A gui element has got the focus.
			/** If the event is absorbed then the focus will not be changed. */
			EGET_ELEMENT_FOCUSED,

			//! The mouse cursor hovered over a gui element.
			/** If an element has sub-elements you also get this message for the subelements */
			EGET_ELEMENT_HOVERED,

			//! The mouse cursor left the hovered element.
			/** If an element has sub-elements you also get this message for the subelements */
			EGET_ELEMENT_LEFT,

			//! An element would like to close.
			/** Windows and context menus use this event when they would like to close,
			this can be cancelled by absorbing the event. */
			EGET_ELEMENT_CLOSED,

			//! A button was clicked.
			EGET_BUTTON_CLICKED,

			//! A scrollbar has changed its position.
			EGET_SCROLL_BAR_CHANGED,

			//! A checkbox has changed its check state.
			EGET_CHECKBOX_CHANGED,

			//! A new item in a listbox was selected.
			/** NOTE: You also get this event currently when the same item was clicked again after more than 500 ms. */
			EGET_LISTBOX_CHANGED,

			//! An item in the listbox was selected, which was already selected.
			/** NOTE: You get the event currently only if the item was clicked again within 500 ms or selected by "enter" or "space". */
			EGET_LISTBOX_SELECTED_AGAIN,

			//! A file has been selected in the file dialog
			EGET_FILE_SELECTED,

			//! A directory has been selected in the file dialog
			EGET_DIRECTORY_SELECTED,

			//! A file open dialog has been closed without choosing a file
			EGET_FILE_CHOOSE_DIALOG_CANCELLED,

			//! 'Yes' was clicked on a messagebox
			EGET_MESSAGEBOX_YES,

			//! 'No' was clicked on a messagebox
			EGET_MESSAGEBOX_NO,

			//! 'OK' was clicked on a messagebox
			EGET_MESSAGEBOX_OK,

			//! 'Cancel' was clicked on a messagebox
			EGET_MESSAGEBOX_CANCEL,

			//! In an editbox 'ENTER' was pressed
			EGET_EDITBOX_ENTER,

			//! The text in an editbox was changed. This does not include automatic changes in text-breaking.
			EGET_EDITBOX_CHANGED,

            //! The marked area in an editbox was changed.
			EGET_EDITBOX_MARKING_CHANGED,

			//! The tab was changed in an tab control
			EGET_TAB_CHANGED,

			//! A menu item was selected in a (context) menu
			EGET_MENU_ITEM_SELECTED,

			//! The selection in a combo box has been changed
			EGET_COMBO_BOX_CHANGED,

			//! The value of a spin box has changed
			EGET_SPINBOX_CHANGED,

			//! A table has changed
			EGET_TABLE_CHANGED,
			EGET_TABLE_HEADER_CHANGED,
			EGET_TABLE_SELECTED_AGAIN,

			//! A tree view node lost selection. See IGUITreeView::getLastEventNode().
			EGET_TREEVIEW_NODE_DESELECT,

			//! A tree view node was selected. See IGUITreeView::getLastEventNode().
			EGET_TREEVIEW_NODE_SELECT,

			//! A tree view node was expanded. See IGUITreeView::getLastEventNode().
			EGET_TREEVIEW_NODE_EXPAND,

			//! A tree view node was collapsed. See IGUITreeView::getLastEventNode().
			EGET_TREEVIEW_NODE_COLLAPSE,

			//! deprecated - use EGET_TREEVIEW_NODE_COLLAPSE instead. This
			//! may be removed by Irrlicht 1.9
			EGET_TREEVIEW_NODE_COLLAPS = EGET_TREEVIEW_NODE_COLLAPSE,

			//! No real event. Just for convenience to get number of events
			EGET_COUNT
		};
	} // end namespace gui


//! SEvents hold information about an event. See irr::IEventReceiver for details on event handling.
struct SEvent
{
	//! Any kind of GUI event.
	struct SGUIEvent
	{
		//! IGUIElement who called the event
		gui::IGUIElement* Caller;

		//! If the event has something to do with another element, it will be held here.
		gui::IGUIElement* Element;

		//! Type of GUI Event
		gui::EGUI_EVENT_TYPE EventType;

	};

	//! Any kind of log event.
	struct SLogEvent
	{
		//! Pointer to text which has been logged
		const c8* Text;

		//! Log level in which the text has been logged
		ELOG_LEVEL Level;
	};

	//! Any kind of user event.
	struct SUserEvent
	{
		//! Some user specified data as int
		s32 UserData1;

		//! Another user specified data as int
		s32 UserData2;
	};
	
	// Raw events from the OS
	struct SSystemEvent
	{
		//! Android command handler native activity messages.
		struct SAndroidCmd
		{
			//!  APP_CMD_ enums defined in android_native_app_glue.h from the Android NDK
			s32 Cmd;
		};

		// TOOD: more structs for iphone, Windows, X11, etc.

		ESYSTEM_EVENT_TYPE EventType;
		union
		{
			struct SAndroidCmd AndroidCmd;
		};
	};
	
	// Application state event
	struct SApplicationEvent
	{
		EAPPLICATION_EVENT_TYPE EventType;
	};

	EEVENT_TYPE EventType;
	union
	{
		struct SGUIEvent GUIEvent;
		struct SLogEvent LogEvent;
		struct SUserEvent UserEvent;
		struct SSystemEvent SystemEvent;
		struct SApplicationEvent ApplicationEvent;
	};

};

//! Interface of an object which can receive events.
/** Many of the engine's classes inherit IEventReceiver so they are able to
process events. Events usually start at a postEventFromUser function and are
passed down through a chain of event receivers until OnEvent returns true. See
irr::EEVENT_TYPE for a description of where each type of event starts, and the
path it takes through the system. */
class IEventReceiver
{
public:

	//! Destructor
	virtual ~IEventReceiver() {}

	//! Called if an event happened.
	/** Please take care that you should only return 'true' when you want to _prevent_ Irrlicht
	* from processing the event any further. So 'true' does mean that an event is completely done.
	* Therefore your return value for all unprocessed events should be 'false'.
	\return True if the event was processed.
	*/
	virtual bool OnEvent(const SEvent& event) = 0;
};

} // end namespace irr

#endif

