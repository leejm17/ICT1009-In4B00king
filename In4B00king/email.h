#ifndef EMAIL_H
#define EMAIL_H
#include <QDialog>

class email
{
public:
    email();
    void SendEmail(QString Email);
    QString generate_OTP(int len);

    QString getEmail_OTP() const;

    void setEmail_OTP(const QString &value);

private:
    QString email_OTP;
};

#endif // EMAIL_H
