#include "pairwisecomp.h"
#include "globalcriteriestable.h"
#include "mainwindow.h"
#include "dataprocessing.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Data dtCmp;
//    dtCmp.count = 3;
//    dtCmp.data  = QVector<qreal>() << 1 << 2 << 3
//                                   << 0.33 << 1 << 2
//                                   << 0.5 << 4 << 1;
//    dtCmp.labels= QStringList()    << "Екон В."
//                                   << "Соц В"
//                                   << "Екол В.";
//    ComparisionTable *com = new ComparisionTable(dtCmp);

//    Data dt1;
//    dt1.count = 2;
//    dt1.data  = QVector<qreal>() << 1 << 3
//                                 << 2 << 1;
//    dt1.labels = QStringList() << "Варт Б"
//                                 << "Прибуток";
//    Data dt2;
//    dt2.count = 2;
//    dt2.data  = QVector<qreal>() << 1  << 4
//                                 << 0.3<< 1;
//    dt2.labels = QStringList() << "Ств Інф"
//                                 << "Нов. Роб.М.";
//    Data dt3;
//    dt3.count = 2;
//    dt3.data  = QVector<qreal>() << 1    << 2
//                                 << 0.25 << 1;
//    dt3.labels = QStringList() << "Впл. Довк"
//                                 << "Ест. Вигляд";
//    QVector<Data> vec;
//    vec.append(dt1);
//    vec.append(dt2);
//    vec.append(dt3);




//    DataBlock bl;
//    bl.MainTable    = dtCmp;
//    bl.cmp2         = vec;

    DataProcessing *da = new DataProcessing();
    da->loadFile("text.eps");

    da->saveFile("set.eps", da->getData());

    return a.exec();
}
