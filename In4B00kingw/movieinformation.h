#ifndef MOVIEINFORMATION_H
#define MOVIEINFORMATION_H

#include <QMainWindow>

namespace Ui {
class MovieInformation;
}

class MovieInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit MovieInformation(QWidget *parent = nullptr);
    ~MovieInformation();

private:
    Ui::MovieInformation *ui;
};

#endif // MOVIEINFORMATION_H
