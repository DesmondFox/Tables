#ifndef FINALTABLE_H
#define FINALTABLE_H

#include <QWidget>
#include "globalcriteriestable.h"

class FinalTable : public QWidget
{
    Q_OBJECT
public:
    explicit FinalTable(QWidget *parent = 0);

private:
    QTableWidget *pTable;

signals:

public slots:
};

#endif // FINALTABLE_H
