#ifndef EDITMOVIES_H
#define EDITMOVIES_H

#include <QDialog>

namespace Ui {
class editmovies;
}

class editmovies : public QDialog
{
    Q_OBJECT

public:
    explicit editmovies(QWidget *parent = nullptr);
    ~editmovies();

private:
    Ui::editmovies *ui;
};

#endif // EDITMOVIES_H
