#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_system.h"
#include <iostream>
#include <QDebug>
using namespace std;

vfs_t vfs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTreeWidgetItem *item = new QTreeWidgetItem();
    selected_widget = item;

    QTreeWidgetItem *d_item = new QTreeWidgetItem();
    drive_item = d_item;
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

        vfs.a_drive.append(v_obj);

        ui->comboBoxDelete->addItem(ui->addFileLineEdit->text());
        ui->comboBoxPrint->addItem(ui->addFileLineEdit->text());
        MainWindow::addTreeChild(selected_widget, ui->addFileLineEdit->text(), ui->contentsLineEdit->text());
        MainWindow::addTreeChild(drive_item, ui->addFileLineEdit->text(), ui->contentsLineEdit->text());
    }
}

void MainWindow::on_deletePushButton_clicked()
{
    if(ui->comboBoxDelete->currentText() != NULL)
    {
        for (int i = 0; i < vfs.a_drive.size(); ++i)
        {
            if (vfs.a_drive.at(i).n_inode.n_name == (ui->comboBoxDelete->currentText()))
            {
                cout << "Found file at position " << i << endl;
                vfs.a_drive.removeAt(i);
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
//    treeItem->setText(0, name);
//    treeItem->setText(1, description);

    addTreeChild(selected_widget, name, "file");
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

}

void MainWindow::on_printPushButton_clicked()
{
    for (int i = 0; i < vfs.a_drive.size(); ++i)
    {
        if (vfs.a_drive.at(i).n_inode.n_name == (ui->comboBoxPrint->currentText()))
        {
            ui->lineEditPrint->setText(vfs.a_drive.at(i).n_inode.n_data);
        }
    }

}

void MainWindow::on_vfsTreeWidget_activated(const QModelIndex &index)
{

}

void MainWindow::on_vfsTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString path;
    QList<QTreeWidgetItem*> drive_ptr;
    ui->vfsTreeWidget->findItems(item->text(column),0,0);
    drive_ptr = ui->driveATreeWidget->findItems(item->text(column),Qt::MatchContains | Qt::MatchRecursive,0);
    if (drive_ptr.isEmpty() == 0)
    {
        drive_ptr.at(0)->setSelected(true);
        drive_item = drive_ptr.at(0);
    }
    else
    {
        drive_ptr = ui->driveBTreeWidget->findItems(item->text(column),Qt::MatchContains | Qt::MatchRecursive,0);
        if (drive_ptr.isEmpty() == 0)
        {
            drive_ptr.at(0)->setSelected(true);
            drive_item = drive_ptr.at(0);
        }
        else
        {
            drive_ptr = ui->driveCTreeWidget->findItems(item->text(column),Qt::MatchContains | Qt::MatchRecursive,0);
            if (drive_ptr.isEmpty() == 0)
            {
                drive_ptr.at(0)->setSelected(true);
                drive_item = drive_ptr.at(0);
            }
        }
    }
    selected_widget = item;
    path.append(item->text(column));
    while(item->parent())
    {
        item = item->parent();
        path.prepend(item->text(0)+"/");
    }
    ui->pathLineEdit->setText("/"+path+"/");
}
