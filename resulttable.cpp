#include "resulttable.h"

ResultTable::ResultTable(QWidget *parent)
    : QTableWidget(parent)
{
    // Добавление столбцов

    for (int i = 0; i < 2; i++)
        this->insertColumn(i);

}

void ResultTable::setData(const QVector<PairwiseComp *> &vec2lvl, const QVector<PairwiseComp *> &vec3lvl)
{
    vectorOfTable2Lvl   = vec2lvl;
    vectorOfTable3Lvl   = vec3lvl;

    if (this->columnCount() == 0)
        for (int i = 0; i < 2; i++)
            this->insertColumn(i);

    // Добавим пустые строки и столбцы
    // строки
    for (int i = 0; i < vectorOfTable2Lvl.length(); i++)
        for (int j = 0; j < vectorOfTable2Lvl[i]->labels.length(); j++)
            this->insertRow(0);
    // для подписи "глоб приор. критериев"
    this->insertRow(0);
    // столбцы
    for (int i = 0; i < vectorOfTable3Lvl[0]->labels.length(); i++)
        this->insertColumn(2);


    // Выделим память под клетки
    for (int i = 0; i < this->rowCount(); i++)
        for (int j = 0; j < this->columnCount(); j++)
            this->setItem(i, j, new QTableWidgetItem);

    // Добавим заголовки для столбцов
    QStringList labels;
    labels << "Критерии 3 уровня"
           << "Глоб. критерии 3 ур";
    labels.append(vectorOfTable3Lvl[0]->labels);
    this->setHorizontalHeaderLabels(labels);

    // Подпись "Глобальные приоритеты критериев" и фон клеток
    QTableWidgetItem *pItm;
    for (int i = 0; i < columnCount(); i++)
    {
        pItm    = this->item(rowCount()-1, i);

        if (i == 0)
            pItm->setText("Глобальные приор. критериев");

        pItm->setBackgroundColor(QColor(0, 0, 255, 190));
        pItm->setTextColor(QColor(255, 252, 132));
        pItm->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    }

    solve();

}

void ResultTable::solve()
{
    // Для разноцветности клеток
    QVector<QColor> colors;
    colors << QColor(200, 243, 252, 150)
           << QColor(185, 211, 255, 150)
           << QColor(255, 206, 255, 150)
           << QColor(248, 255, 206, 150)
           << QColor(255, 199, 250, 150)
           << QColor(199, 252, 255, 150)
           << QColor(199, 255, 220, 150);

    // Заполнение таблицы заголовками и приоритетами 3 уровня
    int counter = 0;    // индекс
    QTableWidgetItem    *pLabel;
    QTableWidgetItem    *pCrit;
    for (int i = 0; i < vectorOfTable2Lvl.length(); i++)
        for (int j = 0; j < vectorOfTable2Lvl[0]->labels.length(); j++)
        {

            // Заголовки
            pLabel  = this->item(counter, 0);
            pLabel->setText(vectorOfTable2Lvl[i]->labels[j]);
            pLabel->setBackgroundColor(QColor(160, 180, 190, 100));
            pLabel->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            // Глобальные критерии 3 уровня
            pCrit   = this->item(counter, 1);
            pCrit->setText(QString::number(vectorOfTable2Lvl[i]->getGlobalPriorities3lvl()[j]));
            pCrit->setBackgroundColor(colors[i]);
            pCrit->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            counter++;
        }

    // Заполнение локальными приоритетами 3 уровня
    QTableWidgetItem    *pPrior;
    for (int i = 0; i < vectorOfTable3Lvl.length(); i++)
        for (int j = 2; j < vectorOfTable3Lvl[i]->labels.length()+2; j++)
        {
            pPrior  = this->item(i, j);
            pPrior->setText(QString::number(vectorOfTable3Lvl[i]->priorities[j-2]));
            pPrior->setBackgroundColor(colors[(i+5)%colors.length()]);
            pPrior->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        }

    // Заполнение глобальными приоритетами критериев
    qreal res = 0;
    QTableWidgetItem    *pGlPr;
    for (int i = 2; i < vectorOfTable3Lvl[0]->labels.length()+2; i++)
    {
        for (int j = 0; j < counter; j++)
        {
            res += this->item(j, 1)->text().toDouble() * this->item(j, i)->text().toDouble();
        }

        pGlPr   = this->item(this->rowCount()-1, i);
        pGlPr->setText(QString::number(res));
        pGlPr->setTextColor(QColor(255, 252, 132));
        pGlPr->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        res = 0;
    }
}

void ResultTable::clear()
{
    vectorOfTable2Lvl.clear();
    vectorOfTable3Lvl.clear();
    for (int i = this->columnCount(); i >= 0; i--)
        this->removeColumn(i);
    for (int i = this->rowCount(); i >= 0; i--)
        this->removeRow(i);
}
