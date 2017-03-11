#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QString>
#include "comparisiontable.h"

struct DataBlock
{
    Data MainTable;
    QVector<Data> cmp2;
    QVector<Data> cmp3;
};

class DataProcessing : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessing(QObject *parent = 0);
    void loadFile(const QString &path);
    void saveFile(const QString &path, DataBlock &block);
    DataBlock getData();

//    Data getComparisionTableData();

private:
    Data comparisionTable;
    QVector<Data> compData2lvl;
    QVector<Data> compData3lvl;

signals:
    void error(int code);
    // error codes:
    // 1 - File not found
    // 2 - File has been corrumpted
    // 3 - Write error

    void doneLoading();

public slots:
};

#endif // DATAPROCESSING_H
