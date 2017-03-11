#include "pairwisecomp.h"

PairwiseComp::PairwiseComp(ComparisionTableData data, QString name, QWidget *parent)
{
    lblName     = new QLabel(this);
    lblName->setText("<font color=blue>"+name+"</font>");

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

void PairwiseComp::setGlobalPriorities3lvl(const QVector<qreal> &pr)
{
    globPr3lvl.clear();
    globPr3lvl = pr;
}

void PairwiseComp::layoutWidgets()
{
    QVBoxLayout *pVBox  = new QVBoxLayout();
    pVBox->addWidget(lblIS, 0, Qt::AlignTop);
    pVBox->addWidget(lblOS, 0, Qt::AlignTop);

    QVBoxLayout *pVBox2 = new QVBoxLayout();
    pVBox2->addWidget(lblName);
    pVBox2->addWidget(pTable);

    QHBoxLayout *pHBox  = new QHBoxLayout(this);
    pHBox->addLayout(pVBox2);
    pHBox->addLayout(pVBox);

    this->setLayout(pHBox);
    this->resize(450, 180);
}
