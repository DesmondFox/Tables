#include "globalcriteriestable.h"

GlobalCriteriesTable::GlobalCriteriesTable(ComparisionTable *table, QList<PairwiseComp*> lst, QWidget *parent)
    : QWidget(parent)
{
    pTableWgt   = new QTableWidget(0, 4, this);

    // Заголовки столбцов
    QStringList headerLabels;
    headerLabels << "КР 3Р"
                 << "ЛОК КР"
                 << "ГЛ КР 2Р"
                 << "ГЛ КР 3Р";
    pTableWgt->setHorizontalHeaderLabels(headerLabels);

    LoadData(table, lst);
    solveGlPrior(table, lst);

    QHBoxLayout *pHBox  = new QHBoxLayout();
    pHBox->addWidget(pTableWgt);
    this->setLayout(pHBox);
}

void GlobalCriteriesTable::LoadData(ComparisionTable *table, QList<PairwiseComp *> lst)
{
    QVector<QColor> colors;
    colors << QColor(238, 243, 252, 150)
           << QColor(185, 211, 255, 150)
           << QColor(255, 206, 255, 150)
           << QColor(248, 255, 206, 150);

    for (int t = 0; t < lst.length(); t++)
    {
        Data tmp = lst[t]->getData();

        QTableWidgetItem *itm3l = NULL;
        QTableWidgetItem *itmlc = NULL;
        QTableWidgetItem *itm2l = NULL;
        for (int it = 0; it < tmp.count; it++)
        {
            // Критерии 3 уровня
            itm3l = new QTableWidgetItem();
            itm3l->setText(tmp.labels[it]);
            itm3l->setBackgroundColor(QColor(247, 235, 238, 150));
            itm3l->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

            pTableWgt->insertRow(it + t*tmp.count);
            pTableWgt->setItem(it + t*tmp.count, 0, itm3l);

            // Локальные критерии
            itmlc = new QTableWidgetItem();
            itmlc->setText(QString::number(lst[t]->priorities[it]));
            itmlc->setBackgroundColor(colors[t]);
            itmlc->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            pTableWgt->setItem(it + t*tmp.count, 1, itmlc);

            // Глобальный приоритет 2 ур
//            if (it == 0)
//                pTableWgt->setSpan(t*tmp.count, 2, 2, 1);
            if (it == 0)
            {
                itm2l   = new QTableWidgetItem();
                itm2l->setText(QString::number(table->priorities[t]));
                itm2l->setBackgroundColor(QColor(230, 152, 15, 80));
                itm2l->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                pTableWgt->setItem(t*tmp.count, 2, itm2l);
            }

        }

    }
}

void GlobalCriteriesTable::solveGlPrior(ComparisionTable *table, QList<PairwiseComp *> lst)
{
    QVector<qreal> tmp;
    for (int t = 0; t < lst.length(); t++)
    {
        tmp.clear();
        for (int i = 0; i < lst[t]->priorities.length(); i++)
        {
            qreal solve = lst[t]->priorities[i]*table->priorities[t];
            tmp.append(solve);
        }
        lst[t]->setGlobalPriorities3lvl(tmp);
    }
    glPr3lvlToTable(lst);

}

void GlobalCriteriesTable::glPr3lvlToTable(QList<PairwiseComp *> lst)
{
    QTableWidgetItem *itm = NULL;
    for (int t = 0; t < lst.length(); t++)
    {
        for (int i = 0; i < lst[t]->getGlobalPriorities3lvl().length(); i++)
        {
            itm = new QTableWidgetItem();
            itm->setText(QString::number(lst[t]->getGlobalPriorities3lvl()[i]));
            itm->setBackgroundColor(QColor(50, 50, 255, 50));
            itm->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            pTableWgt->setItem(i + t*lst[t]->getGlobalPriorities3lvl().length(), 3, itm);
        }
    }
}
