#ifndef GLOBALCRITERIESTABLE_H
#define GLOBALCRITERIESTABLE_H

#include <QWidget>

#include "comparisiontable.h"
#include "pairwisecomp.h"

class GlobalCriteriesTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit GlobalCriteriesTable(QWidget *parent = 0);

    void setData(ComparisionTable *table, const QVector<PairwiseComp*> &vec);
    void solve();
    void clear();


private:
    void solvePriorities3Lvl();

    QVector<PairwiseComp *> vectorOfTables;
    ComparisionTable        *pTable;
signals:

public slots:
};

#endif // GLOBALCRITERIESTABLE_H
