#ifndef PAIRWISECOMP_H
#define PAIRWISECOMP_H

#include "comparisiontable.h"

class PairwiseComp : public ComparisionTable
{
public:
    PairwiseComp(QWidget *parent = 0);
    ~PairwiseComp();

    inline QVector<qreal> getCriteries() { return priorities; }
    inline QVector<qreal> getGlobalPriorities3lvl() { return globPr3lvl; }
    inline QString getName() { return nameOfTable; }

    void setGlobalPriorities3lvl(const QVector<qreal> &pr);
    void setName(const QString &name);

private:
    virtual void layoutWidgets();
    QLabel *lblName;
    QVector<qreal> globPr3lvl;
    QString nameOfTable;
};

#endif // PAIRWISECOMP_H
