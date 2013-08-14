#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QDebug>
#include "decimal.h"


namespace Ui{
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ResultDialog(dec_type::decimal<2> originalValue, std::string currency1, std::string currency2, dec_type::decimal<2> amount, QWidget *parent = 0);
    ~ResultDialog();
    
private:
    Ui::ResultDialog *ui;
    void connectSignalsAndSlots();
    void setupText(dec_type::decimal<2> originalValue, std::string currency1, std::string currency2, dec_type::decimal<2> amount);

public slots:
    void closeSubWindow();

};

#endif // RESULTDIALOG_H
