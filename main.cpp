#include "pairwisecomp.h"
#include "globalcriteriestable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Data dtCmp;
    dtCmp.count = 3;
    dtCmp.data  = QVector<qreal>() << 1 << 2 << 3
                                   << 0.33 << 1 << 2
                                   << 0.5 << 4 << 1;
    dtCmp.labels= QStringList()    << "Екон В."
                                   << "Соц В"
                                   << "Екол В.";
    ComparisionTable *com = new ComparisionTable(dtCmp);

    Data dt1;
    dt1.count = 2;
    dt1.data  = QVector<qreal>() << 1 << 3
                                 << 2 << 1;
    dt1.labels = QStringList() << "Варт Б"
                                 << "Прибуток";
    PairwiseComp *pw1 = new PairwiseComp(dt1, "Економочні вигоди");

    Data dt2;
    dt2.count = 2;
    dt2.data  = QVector<qreal>() << 1  << 4
                                 << 0.3<< 1;
    dt2.labels = QStringList() << "Ств Інф"
                                 << "Нов. Роб.М.";
    PairwiseComp *pw2 = new PairwiseComp(dt2, "Соц. Вигоди");

    Data dt3;
    dt3.count = 2;
    dt3.data  = QVector<qreal>() << 1    << 2
                                 << 0.25 << 1;
    dt3.labels = QStringList() << "Впл. Довк"
                                 << "Ест. Вигляд";
    PairwiseComp *pw3 = new PairwiseComp(dt3, "Екол. Вигоди");

    QList<PairwiseComp*> vec;
    vec.append(pw1);
    vec.append(pw2);
    vec.append(pw3);
//    vec << "test";
//        << pw2
//        << pw3;

    GlobalCriteriesTable table;
    table.show();

    return a.exec();
}
