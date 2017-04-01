#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    curr1lvl    = -1;
    curr2lvl    = -1;
    curr3lvl    = -1;
}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}

DataBlock NewFileDialog::getBlock()
{
    DataBlock data;


    // Первый уровень
    for (int i = 0; i < items1_2lvl.length(); i++)
        data.MainTable.labels << items1_2lvl[i].ItemName;
    data.MainTable.count = items1_2lvl.length();

    for (int i = 0; i < data.MainTable.count; i++)
        for (int j = 0; j < data.MainTable.count; j++)
            if (i == j)
                data.MainTable.data << 1;
            else
                data.MainTable.data << -1;

    // Второй уровень
    int counterFor3lvl = 0;
    for (int i = 0; i < items1_2lvl.length(); i++)
    {
        Data dt;
        int c = 0;
        for (int j = 0; j < items1_2lvl[i].items.length(); j++)
        {
            dt.labels << items1_2lvl[i].items[j].ItemName;
            counterFor3lvl++;
            c++;
            qDebug() << dt.labels;
        }
        dt.count = c;
        data.cmp2 << dt;
    }
    for (int k = 0; k < data.cmp2.length(); k++)
    {
        for (int i = 0; i < data.cmp2[k].labels.length(); i++)
            for (int j = 0; j < data.cmp2[k].labels.length(); j++)
                if (i == j)
                    data.cmp2[k].data << 1;
                else
                    data.cmp2[k].data << -1;
    }

    qDebug() << data.cmp2[0].data;

    // Третий уровень
    // Вытянем заголовки из списка
    QStringList labelList;
    for (int i = 0; i < ui->list3lvl->count(); i++)
        labelList << ui->list3lvl->item(i)->text();

    qDebug() << labelList;
    for (int k = 0; k < counterFor3lvl; k++)
    {
        Data dt;
        dt.labels   = labelList;
        dt.count    = labelList.length();

        for (int i = 0; i < dt.count; i++)
            for (int j = 0; j < dt.count; j++)
                if (i == j)
                    dt.data << 1;
                else
                    dt.data << -1;

        data.cmp3 << dt;
    }

    qDebug() << data.cmp3[0].labels << data.cmp3[0].data;

    return data;
}

void NewFileDialog::on_pushAdd1_clicked()
{
    QString item = QInputDialog::getText(this, "Enter text", "Enter: ");
    Item it;

    // Обновляем список и комбобоксы
    if (!item.isEmpty())
    {
        it.ItemName = item;
        items1_2lvl << it;


        int cbInd = ui->cbCrit1lvl->currentIndex();
        ui->list1lvl->clear();
        ui->cbCrit1lvl->clear();

        for (int i = 0; i < items1_2lvl.length(); i++)
        {
            ui->list1lvl->addItem(items1_2lvl[i].ItemName);
            ui->cbCrit1lvl->addItem(items1_2lvl[i].ItemName);
        }
        if (cbInd != -1)
            ui->cbCrit1lvl->setCurrentIndex(cbInd);
    }
}

void NewFileDialog::on_pushRemove1_clicked()
{
    if (ui->list1lvl->currentIndex().row() != -1)
    {
        items1_2lvl.remove(ui->list1lvl->currentIndex().row());

        // Перезагрузим значения
        ui->list1lvl->clear();
        ui->cbCrit1lvl->clear();

        for (int i = 0; i < items1_2lvl.length(); i++)
        {
            ui->list1lvl->addItem(items1_2lvl[i].ItemName);
            ui->cbCrit1lvl->addItem(items1_2lvl[i].ItemName);
        }
        // Очистка и заполнение заново списка критериев 2 уровня
        ui->listCr2Lvl->clear();
        for (int i = 0; i < items1_2lvl[ui->cbCrit1lvl->currentIndex()].items.length(); i++)
        {
            ui->listCr2Lvl->addItem(items1_2lvl[ui->cbCrit1lvl->currentIndex()].items[i].ItemName);
        }
    }
}

void NewFileDialog::on_cbCrit1lvl_activated(int index)
{

    ui->listCr2Lvl->clear();
    for (int i = 0; i < items1_2lvl[ui->cbCrit1lvl->currentIndex()].items.length(); i++)
    {
        ui->listCr2Lvl->addItem(items1_2lvl[index].items[i].ItemName);
    }
}

void NewFileDialog::on_pushAdd2_clicked()
{
    QString item = QInputDialog::getText(this, "Enter text", "Enter: ");
    Item it;

    // Обновляем список и комбобоксы
    if (!item.isEmpty())
    {
        it.ItemName = item;
        items1_2lvl[ui->cbCrit1lvl->currentIndex()].items.append(it);

        ui->listCr2Lvl->clear();
        for (int i = 0; i < items1_2lvl[ui->cbCrit1lvl->currentIndex()].items.length(); i++)
        {
            ui->listCr2Lvl->addItem(items1_2lvl[ui->cbCrit1lvl->currentIndex()].items[i].ItemName);
        }
    }
}

void NewFileDialog::on_pushRemove2_clicked()
{
    if (ui->listCr2Lvl->currentIndex().row() != -1)
    {
        items1_2lvl[ui->cbCrit1lvl->currentIndex()].items.remove(ui->listCr2Lvl->currentRow());


        ui->listCr2Lvl->clear();
        for (int i = 0; i < items1_2lvl[ui->cbCrit1lvl->currentIndex()].items.length(); i++)
        {
            ui->listCr2Lvl->addItem(items1_2lvl[ui->cbCrit1lvl->currentIndex()].items[i].ItemName);
        }
    }

}

void NewFileDialog::on_pushAdd3_clicked()
{
    QString item = QInputDialog::getText(this, "Enter text", "Enter: ");
    Item it;

    if (!item.isEmpty())
    {
        it.ItemName = item;
        items3lvl.append(it);

        ui->list3lvl->clear();
        for (int i = 0; i < items3lvl.length(); i++)
            ui->list3lvl->addItem(items3lvl[i].ItemName);
    }
}

void NewFileDialog::on_pushRemove3_clicked()
{
    if (ui->list3lvl->currentIndex().row() != -1)
    {
        items3lvl.remove(ui->list3lvl->currentRow());

        ui->list3lvl->clear();
        for (int i = 0; i < items3lvl.length(); i++)
        {
            ui->list3lvl->addItem(items3lvl[i].ItemName);
        }
    }
}

