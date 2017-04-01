#ifndef COMPARISIONTABLE_H
#define COMPARISIONTABLE_H

#include <QWidget>
#include <QtWidgets>

typedef struct ComparisionTableData
{
    QStringList     labels;
    int             count;
    QVector<qreal>  data;

} Data;

class ComparisionTable : public QWidget
{
    Q_OBJECT
public:
    explicit ComparisionTable(QWidget *parent = 0);
    ~ComparisionTable();

    QStringList     labels;
    QVector<qreal>  b_i;
    QVector<qreal>  priorities;
    QVector<qreal>  A_j;
    QVector<qreal>  vertSums;
    qreal           IS;
    qreal           OS;
    qreal           sumA_j;

    void setData(ComparisionTableData data);
    void clear();

    Data    getData();

protected:
    QTableWidget    *pTable;
    QLabel          *lblIS;
    QLabel          *lblOS;

    virtual void layoutWidgets();

    void    loadData(QVector<qreal> values);

    void    solveInverseProportion();
    void    solveVerticalSum();
    void    solveB_i();
    void    solvePriorities();
    void    solveA_j();
    void    solveIS();
    void    solveOS();
    void    solveALL();
    int     elementCount;
    qreal   n_rand;
    QVBoxLayout *pLay;

signals:
    void sigResolve();

public slots:

private slots:
    void resolve();
};

#endif // COMPARISIONTABLE_H
