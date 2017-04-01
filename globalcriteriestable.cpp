#include "globalcriteriestable.h"

GlobalCriteriesTable::GlobalCriteriesTable(QWidget *parent)
    : QTableWidget(parent)
{

    // Вставка столбцов
    for (int i = 0; i < 4; i++)
        this->insertColumn(i);

    // Заголовки столбцов
    QStringList headerLabels;
    headerLabels << "КР 3Р"
                 << "ЛОК КР"
                 << "ГЛ КР 2Р"
                 << "ГЛ КР 3Р";
    this->setHorizontalHeaderLabels(headerLabels);




}

void GlobalCriteriesTable::setData(ComparisionTable *table, const QVector<PairwiseComp *> &vec)
{
    pTable          = table;
    vectorOfTables  = vec;

    // Добавление строк в таблицу
    for (int i = 0; i < vectorOfTables.length(); i++)
        for (int j = 0; j < vectorOfTables[i]->labels.length(); j++)
            this->insertRow(0);

    if (this->columnCount() == 0)
        for (int i = 0; i < 4; i++)
            this->insertColumn(i);

    // Выделение памяти ячейкам
    for (int i = 0; i < this->rowCount(); i++)
        for (int j = 0; j < this->columnCount(); j++)
            this->setItem(i, j, new QTableWidgetItem);

    solve();

}

void GlobalCriteriesTable::solve()
{
    //
    // МЕТОД ДЛЯ ПРОСЧЕТА ДАННЫХ.
    //

    // Для разноцветности клеток
    QVector<QColor> colors;
    colors << QColor(238, 243, 252, 150)
           << QColor(185, 211, 255, 150)
           << QColor(255, 206, 255, 150)
           << QColor(248, 255, 206, 150);

    // Решить приоритеты 3 уровня
    solvePriorities3Lvl();

    // Названия строк и данные
    int tmp = 0;    // Индекс
    QTableWidgetItem *pName = NULL;
    QTableWidgetItem *pPrio = NULL;
    QTableWidgetItem *pGlPr = NULL;
    QTableWidgetItem *pCrit = NULL;
    for (int i = 0; i < vectorOfTables.length(); i++)
        for (int j = 0; j < vectorOfTables[i]->labels.length(); j++)
        {
            // Заголовки
            pName   = this->item(tmp, 0);
            pName->setText(vectorOfTables[i]->labels[j]);
            pName->setBackgroundColor(QColor(160, 160, 100, 90));
            pName->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            // Приоритеты
            pPrio   = this->item(tmp, 1);
            pPrio->setText(QString::number(vectorOfTables[i]->priorities[j]));
            pPrio->setBackgroundColor(colors[i]);
            pPrio->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            // Глобальные приоритеты
            if (j == 0)
            {
                pGlPr   = this->item(tmp, 2);
                pGlPr->setText(QString::number(pTable->priorities[i]));
                pGlPr->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                pGlPr->setBackgroundColor(QColor(200, 200, 100, 100));
            }

            // Глобальные критерии 3 уровня
            pCrit   = this->item(tmp, 3);
            pCrit->setText(QString::number(vectorOfTables[i]->getGlobalPriorities3lvl()[j]));
            pCrit->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            pCrit->setBackgroundColor(QColor(100, 50, 200, 100));

            tmp++;
        }


}

void GlobalCriteriesTable::clear()
{
    vectorOfTables.clear();

//    QTableWidgetItem *itm = NULL;
//    for (int i = 0; i < columnCount(); i++)
//        for (int j = 0; j < rowCount(); i++)
//        {
//            itm = this->item(i, j);
//            delete itm;
//        }

    for (int i = this->columnCount(); i >= 0; i--)
        this->removeColumn(i);
    for (int i = this->rowCount(); i >= 0; i--)
        this->removeRow(i);


}

void GlobalCriteriesTable::solvePriorities3Lvl()
{
    QVector<qreal> globCrit;

    for (int i = 0; i < vectorOfTables.length(); i++)
    {
        for (int j = 0; j < vectorOfTables[i]->priorities.length(); j++)
        {
            globCrit.append(vectorOfTables[i]->priorities[j]*pTable->priorities[i]);
        }
        vectorOfTables[i]->setGlobalPriorities3lvl(globCrit);
        globCrit.clear();
    }

}
