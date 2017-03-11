#include "dataprocessing.h"

DataProcessing::DataProcessing(QObject *parent) : QObject(parent)
{

}

void DataProcessing::loadFile(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        emit error(1);
        return;
    }

    QTextStream strm(&file);

    QString line;
    QStringList list;
    while (!strm.atEnd())
        list.append(strm.readLine());

    if (list[0] != "# _HEADER")
    {
        emit error(2);
        return;
    }

    int count3lvl = 0;
    for (int i = 0; i < list.length(); i++)
    {
        // Заголовки таблицы 1 ур
        if (list[i] == "# _HEADER")
        {
            QStringList lst = QString(list[i+1]).split(":");
            comparisionTable.labels = lst;
            comparisionTable.count  = lst.length();

            QVector<QString> numbers = QString(list[i+2]).split(" ").toVector();
            for (int i = 0; i < numbers.length(); i++)
                comparisionTable.data.append(numbers[i].toDouble());
        }
        // Заголовки таблицы 2 ур
        if (list[i] == "# _2_LVL")
        {
            int a = i + 1;
            while (true)
            {
                if (list[a] == "# _3_LVL")
                    break;
                Data d;
                d.labels = QString(list[a]).split(":");
                d.count  = QString(list[a]).split(":").length();

                QVector<QString> numbers = QString(list[a+1]).split(" ").toVector();
                for (int i = 0; i < numbers.length(); i++)
                   d.data.append(numbers[i].toDouble());

                compData2lvl.append(d);

                a+=2;

                count3lvl += d.labels.length();
            }
        }
        // Заголовки таблицы 3 ур
        if (list[i] == "# _3_LVL")
        {
            QStringList lst = QString(list[i+1]).split(":");
            for (int c = 0; c < count3lvl; c++)
            {
                Data d;
                d.labels = lst;
                d.count  = lst.length();

                QVector<QString> numbers = QString(list[i+c+2]).split(" ").toVector();
                for (int i = 0; i < numbers.length(); i++)
                   d.data.append(numbers[i].toDouble());

                compData3lvl.append(d);

            }
        }
    }
    qDebug() << count3lvl;
}

void DataProcessing::saveFile(const QString &path, DataBlock &block)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        emit error(3);
        return;
    }
    QTextStream strm(&file);

    QString tmp;
    /// Сформируем список
    QStringList list;
    list.append("# _HEADER");

    // 1 LVL
    // Заголовки
    for (int i = 0; i < block.MainTable.labels.length(); i++)
        tmp += block.MainTable.labels[i] + ":";
    tmp.replace(tmp.length()-1, tmp.length(), "");
    list.append(tmp);
    tmp.clear();
    // Данные
    for (int i = 0; i < block.MainTable.data.length(); i++)
        tmp += QString::number(block.MainTable.data[i]) + " ";
    tmp.replace(tmp.length()-1, tmp.length(), "");
    list.append(tmp);
    tmp.clear();

    list.append("# _2_LVL");
    // 2 LVL
    for (int i = 0; i < block.cmp2.length(); i++)
    {
        // Заголовки
        for (int j = 0; j < block.cmp2[i].labels.length(); j++)
            tmp += block.cmp2[i].labels[j] + ":";
        tmp.replace(tmp.length()-1, tmp.length(), "");
        list.append(tmp);
        tmp.clear();
        // Данные
        for (int j = 0; j < block.cmp2[i].data.length(); j++)
            tmp += QString::number(block.cmp2[i].data[j]) + " ";
        tmp.replace(tmp.length()-1, tmp.length(), "");
        list.append(tmp);
        tmp.clear();
    }

    list.append("# _3_LVL");
    // 3 LVL
    // Заголовки
    for (int i = 0; i < block.cmp3[0].labels.length(); i++)
        tmp += block.cmp3[0].labels[i] + ":";
    tmp.replace(tmp.length()-1, tmp.length(), "");
    list.append(tmp);
    tmp.clear();
    // Данные
    for (int i = 0; i < block.cmp3.length(); i++)
    {
        for (int j = 0; j < block.cmp3[i].data.length(); j++)
            tmp += QString::number(block.cmp3[i].data[j]) + " ";
        tmp.replace(tmp.length()-1, tmp.length(), "");
        list.append(tmp);
        tmp.clear();
    }

    for (int i = 0; i < list.length(); i++)
        strm << list[i] << endl;
}

DataBlock DataProcessing::getData()
{
    DataBlock block;
    block.MainTable = comparisionTable;
    block.cmp2      = compData2lvl;
    block.cmp3      = compData3lvl;
    return block;
}

//Data DataProcessing::getComparisionTableData()
//{
//    return
//}
