#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_system.h"
#include<iostream>
using namespace std;

QList<vnode_t> block_a;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPushButton_clicked()
{
    if(ui->lineEdit->text() != NULL)
    {
        vnode v_obj;

        v_obj.n_inode.n_type = file;
        v_obj.n_inode.n_name = ui->lineEdit->text();
        v_obj.n_inode.n_data = ui->lineEditContents->text();

        block_a.append(v_obj);

        QListWidgetItem file_list;;
        file_list.setText(v_obj.n_inode.n_name);

        ui->listWidget->addItem(file_list.text());
        ui->comboBoxDelete->addItem(file_list.text());
        ui->comboBoxPrint->addItem(file_list.text());
        MainWindow::addTreeRoot(file_list.text(), file_list.text());
    }
}

void MainWindow::on_deletePushButton_clicked()
{
    if(ui->comboBoxDelete->currentText() != NULL)
    {
        for (int i = 0; i < block_a.size(); ++i)
        {
            if (block_a.at(i).n_inode.n_name == (ui->comboBoxDelete->currentText()))
            {
                cout << "Found file at position " << i << endl;
                block_a.removeAt(i);
            }
        }
        for (int i = 0; i < ui->listWidget->count(); ++i)
        {
            if (ui->listWidget->item(i)->text() == (ui->comboBoxDelete->currentText()))
            {
                delete ui->listWidget->item(i);
            }
        }
        for (int i = 0; i < ui->comboBoxPrint->count(); ++i)
        {
            if (ui->comboBoxPrint->currentText() == (ui->comboBoxDelete->currentText()))
            {
                ui->comboBoxPrint->removeItem(i);
            }
        }
        ui->comboBoxDelete->removeItem(ui->comboBoxDelete->currentIndex());
    }
}

void MainWindow::addTreeRoot(QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget_2);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    addTreeChild(treeItem, name + "A", "Child_first");
    addTreeChild(treeItem, name + "B", "Child_second");
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
    treeItem->setText(2, "test");
    parent->child(0)->addChild(treeItem);
}

void MainWindow::on_printPushButton_clicked()
{
    for (int i = 0; i < block_a.size(); ++i)
    {
        if (block_a.at(i).n_inode.n_name == (ui->comboBoxPrint->currentText()))
        {
            ui->lineEditPrint->setText(block_a.at(i).n_inode.n_data);
        }
    }

}
