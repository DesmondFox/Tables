#include "pairwisecomp.h"

PairwiseComp::PairwiseComp(QWidget *parent)
    : ComparisionTable(parent)
{
    lblName     = new QLabel(this);
    lblName->setText("<font color=blue> Без имени </font>");

    layoutWidgets();
}

PairwiseComp::~PairwiseComp()
{
    clear();
}


void PairwiseComp::setGlobalPriorities3lvl(const QVector<qreal> &pr)
{
    globPr3lvl.clear();
    globPr3lvl = pr;
}

void PairwiseComp::setName(const QString &name)
{
    lblName->setText("<font color=blue>" + name + "</font>");
    nameOfTable = name;
}

void PairwiseComp::layoutWidgets()
{
    pLay->addWidget(lblName);
}
