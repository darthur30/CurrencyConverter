#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <sstream>
#include <string>


/********************************************/
/***             CONSTRUCTORS             ***/
/********************************************/
ResultDialog::ResultDialog( dec_type::decimal<2> originalValue, std::string currency1, std::string currency2, dec_type::decimal<2> amount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    connectSignalsAndSlots();
    setupText(originalValue, currency1, currency2, amount);
}


/********************************************/
/***        PRIVATE INIT FUNCTIONS        ***/
/********************************************/
inline void ResultDialog::connectSignalsAndSlots()
{
    connect( ui->pushButton_RD, SIGNAL( clicked() ), this, SLOT( closeSubWindow() )  );
}


inline void ResultDialog::setupText( dec_type::decimal<2> originalValue, std::string currency1, std::string currency2, dec_type::decimal<2> amount)
{
    std::stringstream ss;
    ss << originalValue << " " << currency1 << " to " << currency2 << "\n\n= " << amount;
    std::string temp = ss.str();
    ui->label_result->setText(temp.c_str());
}


/********************************************/
/***            SLOT FUNCTIONS            ***/
/********************************************/
void ResultDialog::closeSubWindow()
{
    qDebug() << "close sub window";
    this->close();
}


/********************************************/
/***              DESTRUCTORS             ***/
/********************************************/
ResultDialog::~ResultDialog()
{
    delete ui;
}


