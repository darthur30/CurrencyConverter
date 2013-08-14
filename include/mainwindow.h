#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//               (mainwindow.h)                //
//                                             //
//    Header contains declarations for:        //
//    ->  Ui namespace                         //
//    ->  Main Window Container Widget Class   //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <QMainWindow>
#include <QtCore>
#include <QtGUI>
#include <QDebug>
#include <string>
#include <math.h>
#include "decimal.h"


namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *main_model;
    QStringListModel *combobox_model;



    void setupUi();
    void setupModels();
    void linkModelsToWidgets();
    void connectSignalsAndSlots();
    std::vector<std::string> parseData(std::string rawData);
    void inputNewData(const std::vector<std::string> &sortedData);
    int* checkCurrencySelection();
    void convertToDouble(int selection [], double& rate1, double& rate2);
    double checkAmountEntered();
    dec_type::decimal<2> makeExchangeRateCalculation(dec_type::decimal<2> amount, double rate1, double rate2);
    void delay(const int duration);


private slots:
    void retrieveData();
    void calculate();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionAuthor_Information_triggered();
};

#endif // MAINWINDOW_H
