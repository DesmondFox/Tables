#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pDataProccess   = new DataProcessing(this);

    // Удалить начальные вкладки
    ui->tab2Lvl->removeTab(0);
    ui->tab2Lvl->removeTab(0);
    ui->tab3Lvl->removeTab(0);
    ui->tab3Lvl->removeTab(0);

    // Кнопка "Закрыть" будет неактивна, пока ничего не загружено
    ui->acClose->setEnabled(false);

    connect(pDataProccess,  SIGNAL(error(int)),      SLOT(slotError(int)));
    connect(ui->acExit,     SIGNAL(triggered(bool)), SLOT(close()));
    connect(ui->acLoad,     SIGNAL(triggered(bool)), SLOT(slotLoad()));
    connect(ui->acAddTab,   SIGNAL(triggered(bool)), SLOT(slotDbg()));
    connect(ui->acClose,    SIGNAL(triggered(bool)), SLOT(slotClose()));
    connect(ui->acSave,     SIGNAL(triggered(bool)), SLOT(slotSave()));
    connect(ui->acSaveAs,   SIGNAL(triggered(bool)), SLOT(slotSaveAs()));
    connect(ui->acNew,      SIGNAL(triggered(bool)), SLOT(slotNew()));

}

MainWindow::~MainWindow()
{
    delete pDataProccess;
    delete ui;
}

void MainWindow::loadTables2Lvl(const QVector<Data> dataVector)
{

    // Загрузка данных в таблицы и добавление в вектор из указателей на эти таблицы
    PairwiseComp *pTable = NULL;
    for (int i = 0; i < dataVector.length(); i++)
    {
        pTable  = new PairwiseComp(this);
        pTable->setData(dataVector[i]);
        pTable->setName(ui->CompTable1Lvl->labels[i]);

        vecOfTables2Lvl.append(pTable);
    }

    // Добавление вкладок с таблицами
    for (int i = 0; i < vecOfTables2Lvl.length(); i++)
        ui->tab2Lvl->addTab(vecOfTables2Lvl[i], vecOfTables2Lvl[i]->getName());

    // connect
    for (int i = 0; i < vecOfTables2Lvl.length(); i++)
        connect(vecOfTables2Lvl[i], SIGNAL(sigResolve()), SLOT(slotResolve()));
}

void MainWindow::loadTables3Lvl(const QVector<Data> dataVector)
{
    // Загрузка заголовков таблиц 2 уровня
    getLabels2Lvl();

    // Загрузка данных в таблицы и добавление в вектор из указателей на эти таблицы
    PairwiseComp *pTable = NULL;
    for (int i = 0; i < dataVector.length(); i++)
    {
        pTable  = new PairwiseComp(this);
        pTable->setData(dataVector[i]);
        pTable->setName(labels2LvlList[i]);

        vecOfTables3Lvl.append(pTable);
    }

    // Добавление вкладок с таблицами
    for (int i = 0; i < vecOfTables3Lvl.length(); i++)
        ui->tab3Lvl->addTab(vecOfTables3Lvl[i], vecOfTables3Lvl[i]->getName());

    // connect
    for (int i = 0; i < vecOfTables3Lvl.length(); i++)
        connect(vecOfTables3Lvl[i], SIGNAL(sigResolve()), SLOT(slotResolve()));
}

void MainWindow::getLabels2Lvl()
{
    // Загрузка заголовков таблиц 2 уровня.
    // Нужно для создания таблиц 3 уровня
    for (int i = 0; i < vecOfTables2Lvl.length(); i++)
        labels2LvlList.append(vecOfTables2Lvl[i]->labels);
}

DataBlock MainWindow::getData()
{
    // Метод для возвращения блока данных. Для сохранения в файл

    DataBlock block;
    block.MainTable = ui->CompTable1Lvl->getData();

    for (int i = 0; i < vecOfTables2Lvl.length(); i++)
        block.cmp2 << vecOfTables2Lvl[i]->getData();

    for (int i = 0; i < vecOfTables3Lvl.length(); i++)
        block.cmp3 << vecOfTables3Lvl[i]->getData();

    return block;
}

void MainWindow::loadDataFromBlock(DataBlock block)
{

}

void MainWindow::slotLoad()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open file"), tr(""), tr("Eps File (*.eps)"));

    DataBlock       block;

    // Загрузка файла и заполнение таблиц
    if (pDataProccess->loadFile(filePath))
    {
        // Получение блока и заполнение таблицы 1 уровня
        block = pDataProccess->getData();
        ui->CompTable1Lvl->setData(block.MainTable);

        // Загрузка данных для таблиц 2 и 3 уровня
        loadTables2Lvl(block.cmp2);
        loadTables3Lvl(block.cmp3);

        // Заполним таблицу глобальных критериев
        ui->glCriteriesTable->setData(ui->CompTable1Lvl, vecOfTables2Lvl);

        // Заполним таблицу результатов
        ui->resTable->setData(vecOfTables2Lvl, vecOfTables3Lvl);

        block.cmp2.clear();
        block.cmp3.clear();

        // Активируем кнопку "Закрыть"
        ui->acClose->setEnabled(true);
    }
}

void MainWindow::slotError(int errCode)
{
    if (errCode == 1) // not found
        QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно открыть файл\nСкорее всего, он занят или недоступен."));
    if (errCode == 2) // file corrumpted
        QMessageBox::critical(this, tr("Ошибка"), tr("Файл поврежден или другого формата.\nУбедитесь, что открываете именно файл данной программы."));
    if (errCode == 3) // write error
        QMessageBox::critical(this, tr("Ошибка"), tr("Неопознанная ошибка записи данных."));
}

void MainWindow::slotResolve()
{
    // Перерешать таблицы приоритетов и финальной таблицы
    ui->glCriteriesTable->solve();
    ui->resTable->solve();
}

void MainWindow::slotClose()
{
    // Слот закрытия проекта. очищение таблиц

    vecOfTables2Lvl.clear();
    vecOfTables3Lvl.clear();
    labels2LvlList.clear();

    ui->CompTable1Lvl->clear();
    for (int i = ui->tab2Lvl->count(); i >= 0; i--)
        ui->tab2Lvl->removeTab(i);
    for (int i = ui->tab3Lvl->count(); i >= 0; i--)
        ui->tab3Lvl->removeTab(i);
    ui->glCriteriesTable->clear();
    ui->resTable->clear();
    pDataProccess->clear();

    // Кнопка "закрыть" будет неактивна
    ui->acClose->setEnabled(false);
}

void MainWindow::slotSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save file"), tr(""), tr("Eps File (*.eps)"));
    pDataProccess->saveFile(path, this->getData());

}

void MainWindow::slotSave()
{
    if (filePath.isEmpty())
        slotSaveAs();
    else
    {
        pDataProccess->saveFile(filePath, this->getData());
    }
}

void MainWindow::slotNew()
{
    NewFileDialog dlg;

    if (dlg.exec() == NewFileDialog::Accepted)
    {
        DataBlock block = dlg.getBlock();
        ui->CompTable1Lvl->setData(block.MainTable);

        // Загрузка данных для таблиц 2 и 3 уровня
        loadTables2Lvl(block.cmp2);
        loadTables3Lvl(block.cmp3);

        // Заполним таблицу глобальных критериев
        ui->glCriteriesTable->setData(ui->CompTable1Lvl, vecOfTables2Lvl);

        // Заполним таблицу результатов
        ui->resTable->setData(vecOfTables2Lvl, vecOfTables3Lvl);

        block.cmp2.clear();
        block.cmp3.clear();

        // Активируем кнопку "Закрыть"
        ui->acClose->setEnabled(true);

    }

}

void MainWindow::slotDbg()
{
    PairwiseComp *p = new PairwiseComp(this);
    p->setName("wow");
    ui->tab2Lvl->addTab(p, "text");
    delete p;
}

