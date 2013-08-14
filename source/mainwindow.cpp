#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "programutilities.h"
#include "resultdialog.h"
#include "aboutdialog.h"
#include <QDebug>



/********************************************/
/***             CONSTRUCTORS             ***/
/********************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setupUi();
    setupModels();
    linkModelsToWidgets();
    connectSignalsAndSlots();
}


/********************************************/
/***         PRIVATE INIT FUNCTIONS       ***/
/********************************************/
inline void MainWindow::setupUi()
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->label_load->hide();
}


inline void MainWindow::setupModels()
{
    combobox_model = new QStringListModel(this);
    QStringList list;
    list << "USD" << "EUR" << "GDP" << "INR" << "AUD" << "CAD" << "ZAR" << "NZD" << "JPY";
    combobox_model->setStringList(list);

    std::vector<std::string>values( ProgUtilities::generateVector() );
    main_model = ProgUtilities::generateModel( values, ui->tableView );
}


inline void MainWindow::linkModelsToWidgets()
{
    ui->tableView->setModel(main_model);
    ui->comboBox_first->setModel(combobox_model);
    ui->comboBox_second->setModel(combobox_model);
}


inline void MainWindow::connectSignalsAndSlots()
{
    connect( ui->pushButton_retrieve, SIGNAL( clicked() ), this, SLOT( retrieveData() )  );
    connect( ui->pushButton_calculate, SIGNAL( clicked() ), this, SLOT( calculate() )  );
}


/********************************************/
/***            SLOT FUNCTIONS            ***/
/********************************************/
void MainWindow::retrieveData()
{    
    ui->progressBar->show();
    ui->label_load->show();
    delay(3);
    ProgUtilities::HttpRequest hr("http://www.dylan-arthur.com/scgi-bin/currencyconverter/currency.cgi");
    hr.execute();
    inputNewData( parseData( hr.getResult() ) );
    ui->progressBar->hide();
    ui->label_load->hide();
}


void MainWindow::calculate()
{
    double exRate1, exRate2;
    dec_type::decimal<2> amountEntered;
    convertToDouble( checkCurrencySelection(), exRate1, exRate2 );
    amountEntered = checkAmountEntered();
    ResultDialog rd(amountEntered, ui->comboBox_first->currentText().toStdString(),ui->comboBox_second->currentText().toStdString(), makeExchangeRateCalculation(amountEntered, exRate1, exRate2),this);
    rd.setModal(true);
    rd.exec();
}


void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}



void MainWindow::on_actionAbout_triggered()
{
    AboutDialog ad(this);
    ad.setModal(true);
    ad.exec();
}


void MainWindow::on_actionAuthor_Information_triggered()
{
    QDesktopServices::openUrl( QUrl("http://www.dylan-arthur.com", QUrl::TolerantMode) );
}


/********************************************/
/***       PRIVATE UTILITY FUNCTIONS      ***/
/********************************************/
inline std::vector<std::string> MainWindow::parseData(std::string rawData)
{ 
     std::string::size_type lastValue = 0;
     std::vector<std::string> tempVec;

     for(std::string::size_type i = 0; i != rawData.length(); ++i)
     {
         if(rawData[i] != '/') continue;
           else
           {
             std::string tempString = rawData.substr(lastValue, i - lastValue);
             lastValue = i + 1;
             tempVec.push_back(tempString);
           }
     }

    return tempVec;
}


inline void MainWindow::inputNewData(const std::vector<std::string> &sortedData)
{
     const int numRows = 9;

     for(int i = 0; i != numRows; ++i)
     {
         QString s_temp( sortedData[i].c_str() );
         QStandardItem* item = new QStandardItem(s_temp);
         main_model->setItem(i, 1, item);
     }

}


inline int* MainWindow::checkCurrencySelection()
 {
    int result [2];
    QString arr [] = { ui->comboBox_first->currentText(),  ui->comboBox_second->currentText() };

    for(int i = 0; i != 2; ++i)
    {
        if(arr[i] == "USD") result[i] = 0;
        if(arr[i] == "EUR") result[i] = 1;
        if(arr[i] == "GDP") result[i] = 2;
        if(arr[i] == "INR") result[i] = 3;
        if(arr[i] == "AUD") result[i] = 4;
        if(arr[i] == "CAD") result[i] = 5;
        if(arr[i] == "ZAR") result[i] = 6;
        if(arr[i] == "NZD") result[i] = 7;
        if(arr[i] == "JPY") result[i] = 8;
    }

    return result;
 }


inline void MainWindow::convertToDouble(int selection [], double& rate1, double& rate2)
 {
    rate1 = atof( main_model->item( selection[0], 1)->text().toStdString().c_str() );
    qDebug() << "convert2Double(1)-> " << main_model->item( selection[0], 1)->text().toStdString().c_str();
    rate2 = atof( main_model->item( selection[1], 1)->text().toStdString().c_str() );
    qDebug() << "convert2Double(2)-> " <<  main_model->item( selection[1], 1)->text().toStdString().c_str();
 }


inline double MainWindow::checkAmountEntered()
 {
    return atof( ui->lineEdit->text().toStdString().c_str() );
 }


inline dec_type::decimal<2> MainWindow::makeExchangeRateCalculation(dec_type::decimal<2> amount, double rate1, double rate2)
 {

    if( ui->comboBox_first->currentText() ==  ui->comboBox_second->currentText() )
    {
        return amount;
    }


    if( ui->comboBox_first->currentText() == "USD" && ui->comboBox_second->currentText() != "USD")
    {
        return amount * dec_type::decimal<2>(rate2);
    }


    if( ui->comboBox_first->currentText() != "USD" && ui->comboBox_second->currentText() == "USD")
    {
        return amount / dec_type::decimal<2>(rate1);
    }


    if( ui->comboBox_first->currentText() != "USD" && ui->comboBox_second->currentText() != "USD")
    {
        dec_type::decimal<2> temp;
        temp = amount / dec_type::decimal<2>(rate1);
        return temp *  dec_type::decimal<2>(rate2);
    }

 }


void MainWindow::delay(const int duration)
{
    QTime dieTime= QTime::currentTime().addSecs(duration);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


/********************************************/
/***              DESTRUCTORS             ***/
/********************************************/
MainWindow::~MainWindow()
{
    delete ui;
}


