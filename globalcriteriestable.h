#ifndef GLOBALCRITERIESTABLE_H
#define GLOBALCRITERIESTABLE_H

#include <QWidget>

#include "comparisiontable.h"
#include "pairwisecomp.h"

class GlobalCriteriesTable : public QWidget
{
    Q_OBJECT
public:
    explicit GlobalCriteriesTable(ComparisionTable *table, QList<PairwiseComp*> lst, QWidget *parent = 0);
    QVector<qreal> glPriorities;

private:
    QTableWidget *pTableWgt;
    void LoadData(ComparisionTable *table, QList<PairwiseComp*> lst);
    void solveGlPrior(ComparisionTable *table, QList<PairwiseComp *> lst);
    void glPr3lvlToTable(QList<PairwiseComp *> lst);
signals:

public slots:
};

#endif // GLOBALCRITERIESTABLE_H
