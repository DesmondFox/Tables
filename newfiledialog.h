#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QInputDialog>
#include "dataprocessing.h"


namespace Ui {
class NewFileDialog;
}

struct Item
{
    QString ItemName;
    QVector<Item> items;
};

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = 0);
    ~NewFileDialog();
    DataBlock getBlock();

private slots:
    void on_pushAdd1_clicked();

    void on_pushRemove1_clicked();

    void on_cbCrit1lvl_activated(int index);

    void on_pushAdd2_clicked();

    void on_pushRemove2_clicked();

    void on_pushAdd3_clicked();

    void on_pushRemove3_clicked();

private:
    Ui::NewFileDialog *ui;

    QVector<Item>   items1_2lvl;
    QVector<Item>   items3lvl;

    DataBlock       block;

    int curr1lvl;
    int curr2lvl;
    int curr3lvl;
};

#endif // NEWFILEDIALOG_H
