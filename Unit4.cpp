//---------------------------------------------------------------------------

#include <fmx.h>
#include <Windows.hpp> // Include Windows header for PlaySound function
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)    //initializes the form when it is created.
    : TForm(Owner)
{
   ReminderTimer->Enabled = false;    //determines whether the timer is currently active or not, means that the timer will not trigger any events until it is explicitly enabled again.
}
//---------------------------------------------------------------------------
const int MillisecondsPerDay = 86400000;
void __fastcall TForm1::SetReminderBtnClick(TObject *Sender)      //event handler is executed when the user clicks the "Set Reminder" button.
{                                                            // calculates the remaining time until the reminder date and time set by the user.
	TDate reminderDate = ReminderDate->Date;           //Gets the reminder date from the ReminderDate control.
	TTime reminderTime = ReminderTime->Time;          //Gets the reminder time from the ReminderTime control.

	TDateTime reminderDateTime = reminderDate + reminderTime;  // Combines the date and time into a single TDateTime object.

	TDateTime remainingTime = reminderDateTime - Now();   //Calculates the remaining time, until the reminder by ;subtracting the current date and time ;from the reminder date and time.

	double remainingTimeInMilliseconds =
					 static_cast<double>(remainingTime) * MillisecondsPerDay;    //Converts the remaining time to milliseconds.

	ReminderTimer->Interval = remainingTimeInMilliseconds;  //Sets the interval of the ReminderTimer to the remaining time.
	ReminderTimer->Enabled = true;        // Enables the ReminderTimer to start counting down.

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ReminderTimerTimer(TObject *Sender){   //This event handler is executed when the ReminderTimer component triggers.
											  //disables the timer to prevent it from triggering again.
    ReminderTimer->Enabled = false;

	// Play sound when the reminder pops up  , plays a sound to notify the user about the reminder.
    ::PlaySoundW(L"Comfort Chain (Sped Up).wav", NULL, SND_FILENAME | SND_ASYNC);

    // Show pop-up message
	ShowMessage(ReminderMessage->Text);     //displays a pop-up message with the reminder message.
}
//---------------------------------------------------------------------------

