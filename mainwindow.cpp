#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_system.h"
#include <iostream>
#include <QDebug>
using namespace std;

QList<vnode_t> block_a;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTreeWidgetItem *item = new QTreeWidgetItem();
    selected_widget = item;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPushButton_clicked()
{
    if(ui->addFileLineEdit->text() != NULL)
    {
        vnode v_obj;

        v_obj.n_inode.n_type = file;
        v_obj.n_inode.n_name = ui->addFileLineEdit->text();
        v_obj.n_inode.n_data = ui->contentsLineEdit->text();

        block_a.append(v_obj);

        ui->comboBoxDelete->addItem(ui->addFileLineEdit->text());
        ui->comboBoxPrint->addItem(ui->addFileLineEdit->text());
        MainWindow::addTreeRoot(ui->addFileLineEdit->text(), ui->contentsLineEdit->text());
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
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->vfsTreeWidget);

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

void MainWindow::on_vfsTreeWidget_activated(const QModelIndex &index)
{

}

void MainWindow::on_vfsTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    qDebug() << "test" << item->text(column);
    ui->driveATreeWidget->findItems(item->text(column),0,0);
    selected_widget = item;
    qDebug() << selected_widget->text(column);
}
