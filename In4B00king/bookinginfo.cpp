#include "bookinginfo.h"

BookingInfo::BookingInfo()
{
}
BookingInfo::BookingInfo(int showID, QString selectedDate, QString selectedTime, QString hallType)
{
    show_ID=showID;
    selected_Date=selectedDate;
    selected_Time=selectedTime;
    hall_Type=hallType;
}

QString BookingInfo::get_selected_Date(){
    return selected_Date;
}

QString BookingInfo::get_selected_Time(){
    return selected_Time;
}

QString BookingInfo::get_hall_Type(){
    return hall_Type;
}

int BookingInfo::get_show_ID(){
    return show_ID;
}

void BookingInfo::set_selected_Date(QString selectedDate){
    selected_Date=selectedDate;
}

void BookingInfo::set_selected_Time(QString selectedTime){
    selected_Time=selectedTime;
}

void BookingInfo::set_hall_Type(QString hallType){
    hall_Type = hallType;
}
