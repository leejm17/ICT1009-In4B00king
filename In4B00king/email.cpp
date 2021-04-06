#include "email.h"
#include <QMessageBox>
#include <curl/curl.h>
#include <QApplication>

email::email()
{

}

char toEmail[50];
char fromEmail[] = "<InForBooking@gmail.com>";
char bodyText[] = "123456";

char *payload_text[] = {
        "To: ", toEmail ,"\r\n",
        "From: ", fromEmail, "\r\n",
        "Subject: [InForBooking] Email Verification \r\n",
        "Your OTP is ",bodyText,"\r\n",

};

// A Function to generate a unique OTP everytime
QString email::generate_OTP(int len)
{
    // Uses computer clock to control seed to ensure each OTP is unique.
    srand(time(NULL));
    QString test;
    QString str = "abcdefghijklmnopqrstuvwxyz0123456789";
    int n = str.length();

    for (int i=1; i<=len; i++)
        test.push_back(str[rand() % n]);

    return test;
}

QString email::getEmail_OTP() const
{
    return email_OTP;
}

void email::setEmail_OTP(const QString &value)
{
    email_OTP = value;
}

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
}

void email::SendEmail(QString email){
    setEmail_OTP(generate_OTP(6));
    qDebug() << email_OTP;
    strcpy_s(toEmail, email.toStdString().c_str());
    strcpy_s(bodyText, email_OTP.toStdString().c_str());

    // Initializing CURL
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;
    upload_ctx.lines_read = 0;
    curl = curl_easy_init();

    // Email Settings
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "InForBooking@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "!@QWaszx");
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long) CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "../google.pem");
        curl_easy_setopt(curl, CURLOPT_CAPATH, "../google.pem");
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, fromEmail);
        recipients = curl_slist_append(recipients, toEmail);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        // Checks to ensure that the email has been sent out successfully.
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

}
