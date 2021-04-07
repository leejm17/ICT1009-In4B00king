#ifndef BOOKINGINFO_H
#define BOOKINGINFO_H

#include <QDialog>
class BookingInfo
{
private:
    int show_ID;
    QString selected_Time, selected_Date, hall_Type;
public:
    BookingInfo();
    BookingInfo(int, QString, QString, QString);
    void set_show_ID(int), set_selected_Time(QString), set_selected_Date(QString), set_hall_Type(QString);
    int get_show_ID();
    QString get_selected_Time(), get_selected_Date(), get_hall_Type();
};

#endif // BOOKINGINFO_H
