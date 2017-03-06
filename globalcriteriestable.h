#ifndef GLOBALCRITERIESTABLE_H
#define GLOBALCRITERIESTABLE_H

#include <QWidget>

#include "comparisiontable.h"
#include "pairwisecomp.h"

class GlobalCriteriesTable : public QWidget
{
    Q_OBJECT
public:
    explicit GlobalCriteriesTable(QWidget *parent = 0);

private:
    QTableWidget *pTableWgt;

signals:

public slots:
};

#endif // GLOBALCRITERIESTABLE_H
