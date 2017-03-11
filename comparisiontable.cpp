#include "comparisiontable.h"

ComparisionTable::ComparisionTable(ComparisionTableData data, QWidget *parent) : QWidget(parent)
{
    pTable      = new QTableWidget(data.count+1, data.count /* столбцы */, this);
    lblIS       = new QLabel("ИС: -");
    lblOS       = new QLabel("ОС: -");
    n_rand      = 0.58; // число случайной согласованности. ТАБЛИЦА
    labels      = data.labels;

    // Добавляем строку "Сумма"
    QStringList horLabels = data.labels;
    horLabels.append("Сумма");

    QStringList vertLabels = data.labels;
    vertLabels.append("b_i");
    vertLabels.append("Приор.");
    vertLabels.append("A_j*x_j");
    pTable->insertColumn(data.count);
    pTable->insertColumn(data.count);
    pTable->insertColumn(data.count);

    pTable->setHorizontalHeaderLabels(vertLabels);
    pTable->setVerticalHeaderLabels(horLabels);

    elementCount = data.count;
    loadData(data.data);

    // Отрегулируем ширину столбцов
    for (int col = 0; col < pTable->columnCount(); col++)
        pTable->setColumnWidth(col, 50);

    solveALL();
    layoutWidgets();

    connect(pTable, SIGNAL(pressed(QModelIndex)), SLOT(resolve()));
}

ComparisionTable::ComparisionTable(QWidget *parent)
    : QWidget(parent)
{
    pTable      = new QTableWidget(0, 0, this);
    lblIS       = new QLabel("ИС: -");
    lblOS       = new QLabel("ОС: -");

    layoutWidgets();
}

void ComparisionTable::setData(ComparisionTableData data)
{
    n_rand      = 0.58; // число случайной согласованности. ТАБЛИЦА
    labels      = data.labels;

    // Добавляем строку "Сумма"
    QStringList horLabels = data.labels;
    horLabels.append("Сумма");

    QStringList vertLabels = data.labels;
    vertLabels.append("b_i");
    vertLabels.append("Приор.");
    vertLabels.append("A_j*x_j");
    pTable->insertColumn(data.count);
    pTable->insertColumn(data.count);
    pTable->insertColumn(data.count);

    pTable->setHorizontalHeaderLabels(vertLabels);
    pTable->setVerticalHeaderLabels(horLabels);

    elementCount = data.count;
    loadData(data.data);

    // Отрегулируем ширину столбцов
    for (int col = 0; col < pTable->columnCount(); col++)
        pTable->setColumnWidth(col, 50);

    solveALL();
}

Data ComparisionTable::getData()
{
    //
    // Возвращение структуры с данными
    //

    Data ret;
    ret.count   = elementCount;

    QVector<qreal> r;
    for (int i = 0; i < elementCount; i++)
    {
        for (int j = 0; j < elementCount; j++)
        {
            r << pTable->item(i, j)->text().toDouble();
        }
    }
    ret.data    = r;
    ret.labels  = labels;
    return ret;
}

void ComparisionTable::loadData(QVector<qreal> values)
{
    // Тотальный быдлокод.
    // В идеале бы использовать модель, но в QTableWidget нельзя их использовать
    // А мне нужно редактирование ячеек
    QTableWidgetItem *itm = NULL;
    for (int i = 0; i < elementCount; i++)
    {
        for (int j = 0; j < elementCount; j++)
        {
            itm = new QTableWidgetItem(QString::number(values[i*elementCount+j]));

            // Диагональные элементы должны быть нетронутыми
            // По умолчанию там 1 стоят
            if (i == j)
            {
                itm->setFlags(Qt::ItemIsSelectable);
                itm->setBackgroundColor(QColor(150, 150, 150, 100));
            }

            pTable->setItem(i, j, itm);
        }
    }
}

void ComparisionTable::layoutWidgets()
{
    QVBoxLayout *pVBox  = new QVBoxLayout();
    pVBox->addWidget(lblIS, 0, Qt::AlignTop);
    pVBox->addWidget(lblOS, 0, Qt::AlignTop);
    QHBoxLayout *pHBox  = new QHBoxLayout();
    pHBox->addWidget(pTable);
    pHBox->addLayout(pVBox);
    this->setLayout(pHBox);
    this->resize(450, 180);
}

void ComparisionTable::solveVerticalSum()
{
    // Высчитываем суммы и перекидываем их в вектор
    for (int col = 0; col < elementCount; col++)
    {
        double sumInColumn = 0;
        for (int row = 0; row < pTable->rowCount()-1; row++) // -1 с учетом того, что мы будем часто сумму пересчитывать
            sumInColumn += pTable->item(row, col)->text().toDouble();
        vertSums << sumInColumn;
    }

    // Закидываем в таблицу
    QTableWidgetItem *itm = NULL;
    for (int col = 0; col < vertSums.size(); col++)
    {
        itm = new QTableWidgetItem();
        itm->setText(QString::number(vertSums[col]));
        itm->setBackgroundColor(QColor(50, 50, 255, 70));
        pTable->setItem(pTable->rowCount()-1, col, itm);
        itm->setFlags(Qt::ItemIsSelectable);
    }

}

void ComparisionTable::solveB_i()
{
    // Высчитываем произведения
    for (int row = 0; row < elementCount; row++)
    {
        double mult = 1;
        for (int col = 0; col < elementCount; col++)
            mult *= pTable->item(row, col)->text().toDouble();
        mult = pow(mult, ((double) 1/elementCount));
        b_i << mult;
    }

    // Закидываем в таблицу
    QTableWidgetItem *itm = NULL;
    for (int row = 0; row < b_i.size(); row++)
    {
        itm = new QTableWidgetItem();
        itm->setText(QString::number(b_i[row]));
        itm->setBackgroundColor(QColor(50, 255, 50, 50));
        itm->setFlags(Qt::ItemIsSelectable);
        pTable->setItem(row, elementCount, itm);
    }
}

void ComparisionTable::solvePriorities()
{
    double sum = 0;
    for (int i = 0; i < b_i.size(); i++)
        sum += b_i[i];

    double pr = 0;
    for (int i = 0; i < b_i.size(); i++)
    {
        pr = b_i[i]/sum;
        priorities << pr;
    }

    // Закидываем в таблицу
    QTableWidgetItem *itm = NULL;
    for (int row = 0; row < priorities.size(); row++)
    {
        itm = new QTableWidgetItem();
        itm->setText(QString::number(priorities[row]));
        itm->setBackgroundColor(QColor(150, 255, 150, 65));
        itm->setFlags(Qt::ItemIsSelectable);
        pTable->setItem(row, elementCount+1, itm);
    }


}

void ComparisionTable::solveA_j()
{
    // Вычисляем A_j, т.е произведение суммы на приоритет строки
    double mult = 0;
    for (int i = 0; i < elementCount; i++)
    {
        mult = vertSums[i]*priorities[i];
        A_j << mult;
    }

    // Закидываем в таблицу
    QTableWidgetItem *itm = NULL;
    for (int row = 0; row < A_j.size(); row++)
    {
        itm = new QTableWidgetItem();
        itm->setText(QString::number(A_j[row]));
        itm->setBackgroundColor(QColor(70, 255, 255, 80));
        itm->setFlags(Qt::ItemIsSelectable);
        pTable->setItem(row, elementCount+2, itm);
    }

    // Вычислим сумму и добавим последним элементом в таблицу
    double sum = 0;
    for (int i = 0; i < A_j.size(); i++)
        sum += A_j[i];
    sumA_j = sum;
    QTableWidgetItem *pSum = new QTableWidgetItem();
    pSum->setText(QString::number(sum));
    pSum->setBackgroundColor(QColor(50, 50, 255, 70));
    pSum->setFlags(Qt::ItemIsSelectable);
    pTable->setItem(elementCount, elementCount+2, pSum);
}

void ComparisionTable::solveIS()
{
    IS = (sumA_j - elementCount)/(elementCount - 1);
    lblIS->setText(QString("ИС: %1").arg(IS));
}

void ComparisionTable::solveOS()
{
    OS = IS/n_rand;
    lblOS->setText(QString("ОС: %1").arg(OS));
}

void ComparisionTable::solveALL()
{
    vertSums.clear();
    b_i.clear();
    priorities.clear();
    A_j.clear();

    solveVerticalSum();
    solveB_i();
    solvePriorities();
    solveA_j();
    solveIS();
    solveOS();
}

void ComparisionTable::resolve()
{
    qDebug() << "Note:\t    Resolve";
    solveALL();
}

