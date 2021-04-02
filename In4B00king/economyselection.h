#ifndef ECONOMYSELECTION_H
#define ECONOMYSELECTION_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class EconomySelection;
}

class EconomySelection : public QDialog
{
    Q_OBJECT

public:
    explicit EconomySelection(QWidget *parent = nullptr);
    ~EconomySelection();
    void updateSelection();

private:
    Ui::EconomySelection *ui;
};

#endif // ECONOMYSELECTION_H
