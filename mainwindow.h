#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "comparisiontable.h"
#include "dataprocessing.h"
#include "globalcriteriestable.h"
#include "pairwisecomp.h"
#include "newfiledialog.h"

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
private:
    Ui::MainWindow *ui;
    DataProcessing *pDataProccess;
    QVector<PairwiseComp*> vecOfTables2Lvl;
    QVector<PairwiseComp*> vecOfTables3Lvl;
    QStringList    labels2LvlList;
    QString        filePath;

    void loadTables2Lvl(const QVector<Data> dataVector);
    void loadTables3Lvl(const QVector<Data> dataVector);
    void getLabels2Lvl();
    DataBlock getData();

private slots:
    void slotLoad();
    void slotError(int errCode);
    void slotResolve();
    void slotClose();
    void slotSaveAs();
    void slotSave();
    void slotNew();

    void slotDbg();
};

#endif // MAINWINDOW_H
