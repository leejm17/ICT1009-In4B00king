#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "login.h"
#include <QMessageBox>
#include <curl/curl.h>
#include "register.h"
#include <QCryptographicHash>

#define FROM    "<InForBooking@gmail.com>"
#define TO      "<testing@gmail.com>"
char* forget_password_OTP;

forgetpassword::forgetpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
}

// A Function to generate a unique OTP everytime
char * generate_password_OTP(int len)
{
    srand(time(NULL));

    QString str = "abcdefghijklmnopqrstuvwxyz0123456789";
    int n = str.length();

    QString OTP;

    for (int i=1; i<=len; i++)
        OTP.push_back(str[rand() % n]);

    n = OTP.length();

    char* otp_array= new char;

    strcpy(otp_array, OTP.toStdString().c_str());

    forget_password_OTP = &otp_array[0];
    return(&otp_array[0]);
}

// Variable to send the OTP to the user's email every time.
char *forgetpw_text[] = {
        "To: " TO "\r\n",
        "From: " FROM "\r\n",
        "Subject: [InForBooking] Forgetten Password \r\n",
        "Your OTP is ",generate_password_OTP(6),". If this is not you, please ignore this message and change your password immediately.\r\n",

};

struct upload_status {
    int lines_read;
};

// checks to ensure that the size of the payload is not 0.
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = forgetpw_text[upload_ctx->lines_read];
    // inserts payload text into a char array
    if(data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;

        return len;
    }

    return 0;
}

forgetpassword::~forgetpassword()
{
    delete ui;
}

void forgetpassword::on_HomePage_clicked()
{
    close();
}

void forgetpassword::on_resetpassword_clicked()
{
    QString username = ui->Email->text();
    QString pwd1 = ui->pwd->text();
    QString pwd2 = ui->pwd2->text();
    QString salted_password = username + pwd1;
    // SHA1 Hash
    QByteArray hashed_password = QCryptographicHash::hash(salted_password.toUtf8(),QCryptographicHash::Md5);
    QString inputHash = QLatin1String(hashed_password.toHex());

    if (pwd1.isEmpty()){
        QMessageBox::warning(this, "Please enter new password", "Empty new password!");
    }else if (pwd2.isEmpty()){
        QMessageBox::warning(this, "Please confirm new password", "Empty confirm new password!");
    }else if (pwd1 == pwd2){
        QSqlQuery updatequery(MyDB::getInstance()->getDBInstance());
        updatequery.prepare("UPDATE User SET password ='"+ inputHash +"' WHERE email_ID='"+ username +"';");
        if(!updatequery.exec()){
                qDebug() << updatequery.lastError().text() << updatequery.lastQuery();
        }else{
            qDebug() << "read was successful "<< updatequery.lastQuery();
        }
        QMessageBox::information(this, "Successful Change", "Password has been changed");
        close();
    }else{
        QMessageBox::warning(this, "Password Mismatch", "Password does not match");
    }
}

void forgetpassword::on_resetpassword_3_clicked()
{
    bool emailcheck = false;
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString email = ui->Email->text();
    query.prepare("SELECT * FROM User WHERE email_ID='" + email + "';");
    if(!query.exec()){
            qDebug() << query.lastError().text() << query.lastQuery();
    }else if (query.exec()){
        if(query.next()){
            emailcheck = true;
        }
    }
    if (!emailcheck){
            QMessageBox::warning(this, "Invalid Email", "Email not found!");
    } else{
        //Disable send email button
        ui->resetpassword_3->setEnabled(false);

    }

    QByteArray ba = email.toLocal8Bit();
    const char *char_email = ba.data();
    #define TO char_email

    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    // Email Settings
    // TODO: Hide the Username and Password
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "InForBooking@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "!@QWaszx");
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long) CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        qDebug() << "loading cert";
        curl_easy_setopt(curl, CURLOPT_CAINFO, "../google.pem");
        curl_easy_setopt(curl, CURLOPT_CAPATH, "../google.pem");
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);
        recipients = curl_slist_append(recipients, TO);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        // Checks for
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_slist_free_all(recipients);

        curl_easy_cleanup(curl);
        qDebug() << "Forgot Password Email Sent!";
    }
    QMessageBox::information(this, "Verification", "Email sent! Please check your email and enter the verification code!");
}

void forgetpassword::on_verifyButton_clicked()
{
    QString verifyText;
    verifyText = ui->verify->text();
    if(verifyText == forget_password_OTP){
        qDebug() <<  "M A T C H E D";
        ui->resetpassword->setEnabled(true);
        QMessageBox::information(this, "Verified", "Verification successful");
        // Update Changed Password here.
    }else{
        QMessageBox::information(this, "Verification", "Wrong verification code! Please try again");
    }
}
