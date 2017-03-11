#ifndef PAIRWISECOMP_H
#define PAIRWISECOMP_H

#include "comparisiontable.h"

class PairwiseComp : public ComparisionTable
{
public:
    PairwiseComp(ComparisionTableData data, QString name = "", QWidget *parent = 0);

    inline QVector<qreal> getCriteries() { return priorities; }
    inline QVector<qreal> getGlobalPriorities3lvl() { return globPr3lvl; }
    void setGlobalPriorities3lvl(const QVector<qreal> &pr);

private:
    virtual void layoutWidgets();
    QLabel *lblName;
    QVector<qreal> globPr3lvl;

};

#endif // PAIRWISECOMP_H
