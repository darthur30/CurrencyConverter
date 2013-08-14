#include "programutilities.h"



QStandardItemModel* ProgUtilities::generateModel( const std::vector<std::string> &values, QObject *parent )
{
    const int numRows = 9;
    const int numColumns = 2;

    QStandardItemModel* model = new QStandardItemModel(numRows, numColumns, parent);



    for (int row = 0; row < numRows; ++row)
    {

        for (int column = 0; column < numColumns; ++column)
        {
               QString text;

               if(column == 0)  text = QString( (values.at(row)).c_str() );
                    else     text = QString('-');

               QStandardItem* item = new QStandardItem(text);
               model->setItem(row, column, item);
        }

     }

    return model;

}


