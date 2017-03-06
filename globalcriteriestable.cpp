#include "globalcriteriestable.h"

GlobalCriteriesTable::GlobalCriteriesTable(QWidget *parent)
    : QWidget(parent)
{
    pTableWgt   = new QTableWidget(0, 4, this);

    // Заголовки столбцов
    QStringList headerLabels;
    headerLabels << "КР 3Р"
                 << "ЛОК КР"
                 << "ГЛ КР 2Р"
                 << "ГЛ КР 3Р";


    QHBoxLayout *pHBox  = new QHBoxLayout();
    pHBox->addWidget(pTableWgt);
    this->setLayout(pHBox);
}
