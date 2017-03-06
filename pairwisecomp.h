#ifndef PAIRWISECOMP_H
#define PAIRWISECOMP_H

#include "comparisiontable.h"

class PairwiseComp : public ComparisionTable
{
public:
    PairwiseComp(ComparisionTableData data, QString name = "", QWidget *parent = 0);

private:
    virtual void layoutWidgets();
    QLabel *lblName;

};

#endif // PAIRWISECOMP_H
