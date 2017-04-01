#ifndef RESULTTABLE_H
#define RESULTTABLE_H

#include <QTableWidget>
#include "pairwisecomp.h"

class ResultTable : public QTableWidget
{
public:
    ResultTable(QWidget *parent = 0);
    void setData(const QVector<PairwiseComp *> &vec2lvl, const QVector<PairwiseComp *> &vec3lvl);
    void solve();
    void clear();

private:
    QVector<PairwiseComp *> vectorOfTable2Lvl;
    QVector<PairwiseComp *> vectorOfTable3Lvl;

};

#endif // RESULTTABLE_H
