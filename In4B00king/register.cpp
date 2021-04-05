#include "register.h"
#include "ui_register.h"
#include "login.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <curl/curl.h>
#include <QApplication>

#define FROM    "<InForBooking@gmail.com>"
#define TO      "<testing@gmail.com>"
char* verify_email_OTP;
bool verified = false;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_Register_2_clicked()
{
    QString gender,email, pwd, pwd2, fname, lname;
    bool accountcreated = false;
    email = ui->Email->text();
    pwd = ui->Password->text();
    pwd2 = ui->Password_2->text();
    fname = ui->Fname->text();
    lname = ui->Lname->text();
    QString age = ui->Age->text();
    if(ui->Male->isChecked()){
        gender = "Male";
    }else if (ui->Female->isChecked()){
        gender = "Female";
    }
    if (ui->Email->text().isEmpty()){
        QMessageBox::warning(this, "Empty Email", "Please enter your email!");
    }else if (ui->Password->text().isEmpty() || ui->Password->text().isEmpty()){
        QMessageBox::warning(this, "Empty Password", "Please enter your password!");
    }else if(pwd != pwd2) {
        QMessageBox::warning(this, "Incorrect password", "Password does not match!");
    }else if (ui->Fname->text().isEmpty()){
        QMessageBox::warning(this, "Empty first name", "Please enter your first name!");
    }else if (ui->Lname->text().isEmpty()){
        QMessageBox::warning(this, "Empty last name", "Please enter your last name!");
    }else if (gender.isEmpty()){
        QMessageBox::warning(this, "Invalid gender", "Please select your gender!");
    }else if (!verified){
        QMessageBox::warning(this, "Verify Email", "Email not Verified.");
    }else{
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Register Account", "Are you sure you want to register this account?\nEmail:"+
                                                                  email + "\nFirst name:" + fname + "\nLast name:" + lname + "\nAge:" +
                                                                  age + "\nGender:" + gender, QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QSqlQuery query(MyDB::getInstance()->getDBInstance());
            query.prepare("INSERT INTO User(email_ID,password,first_name,last_name,age,gender,type) VALUES (:email, :password, :fname, :lname, :age, :gender, 'customer')");
            query.bindValue(":email", email);
            // "Salt"
            QString salted_password = email + pwd;
            // SHA1 Hash
            QByteArray hashed_password = QCryptographicHash::hash(salted_password.toUtf8(),QCryptographicHash::Md5);
            QString inputHash = QLatin1String(hashed_password.toHex());

            query.bindValue(":password", inputHash);
            query.bindValue(":fname", fname);
            query.bindValue(":lname", lname);
            query.bindValue(":age", age);
            query.bindValue(":gender", gender);
            query.exec();
            accountcreated = true;
        } else {
            qDebug() << "Yes was not clicked";
        }
    }
    if (accountcreated){
        this->close();
    }
}


// A Function to generate a unique OTP everytime
char * generate_email_OTP(int len)
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

    verify_email_OTP = &otp_array[0];
    return(&otp_array[0]);
}

// Variable to send the OTP to the user's email every time.
char *payload_text[] = {
        "To: " TO "\r\n",
        "From: " FROM "\r\n",
        "Subject: [InForBooking] Email Verification \r\n",
        "Your OTP is ",generate_email_OTP(6),"\r\n",

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

    data = payload_text[upload_ctx->lines_read];
    // inserts payload text into a char array
    if(data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;

        return len;
    }

    return 0;
}

void Register::on_Close_clicked()
{
    close();
}

void Register::on_sendemail_clicked()
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
    if (emailcheck){
            QMessageBox::warning(this, "Duplicate Email", "Please enter a new email, email has been used already!");
            //Can check add regex if want otherwise just skip
    }else{
        //Disable button and send email to verify
        qDebug() << "test was clicked";
        QString email;
        email = ui->Email->text();
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
            qDebug() << "Email Sent!";
            ui->sendemail->setEnabled(false);
        }
    }
    QMessageBox::information(this, "Verification", "Email sent! Please check your email and enter the verification code!");
}

void Register::on_verify_clicked()
{
    //Add the checking of curl email
    QString verifyText;
    qDebug() <<  "Verifying " << verify_email_OTP;
    verifyText = ui->verificationcode->text();
    if(verifyText == verify_email_OTP){
        qDebug() <<  "M A T C H E D";
        verified = true;
    }
    if (verified){
        QMessageBox::information(this, "Verified", "Verification successful");
    }else{
        QMessageBox::information(this, "Verification", "Wrong verification code! Please try again");
    }
}
