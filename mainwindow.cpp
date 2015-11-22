#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_system.h"
#include <iostream>
#include <QDebug>
using namespace std;

vfs_t vfs;
QString selected_path;

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
    if((ui->addFileLineEdit->text() != NULL) &
            !(selected_widget->text(0).contains("txt")))
    {
        for (int i = 0; i < selected_widget->childCount(); ++i)
        {
            if(selected_widget->child(i)->text(0) == ui->addFileLineEdit->text()+".txt")
                return;
        }
        vnode_t v_obj;

        v_obj.n_inode.n_type = file;
        v_obj.n_inode.n_name = ui->addFileLineEdit->text();
        v_obj.n_inode.n_extension = "txt";
        v_obj.n_inode.n_data = selected_path+v_obj.n_inode.n_name+".txt contents";
        v_obj.n_item = ui->vfsTreeWidget->currentItem();

        QString file_display;
        file_display = v_obj.n_inode.n_name+"."+v_obj.n_inode.n_extension;

        vfs.a_drive.append(v_obj);

        MainWindow::addTreeChild(selected_widget,
                                 file_display,
                                 v_obj.n_inode.n_data);
        MainWindow::addTreeChild(drive_item,
                                 file_display,
                                 v_obj.n_inode.n_data);
    }
}

void MainWindow::on_deletePushButton_clicked()
{
    if(ui->vfsTreeWidget->currentItem()->text(0).contains("txt"))
        delete ui->vfsTreeWidget->currentItem();
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    treeItem->setText(0, name);
    treeItem->setText(1, description);
    QIcon icon;
    icon.addFile(QStringLiteral(":/resources/text.png"), QSize(), QIcon::Normal, QIcon::Off);
    treeItem->setIcon(0, icon);

    parent->addChild(treeItem);
}

void MainWindow::on_printPushButton_clicked()
{
    for (int i = 0; i < vfs.a_drive.size(); ++i)
    {
        if (vfs.a_drive.at(i).n_inode.n_name+".txt" == ui->vfsTreeWidget->currentItem()->text(0))
        {
            ui->lineEditPrint->setText(vfs.a_drive.at(i).n_inode.n_data);
        }
    }

}

void MainWindow::on_vfsTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString path;
    QList<QTreeWidgetItem*> drive_ptr;
    ui->deleteFileLineEdit->setText(item->text(column));
    ui->printFileLineEdit->setText(item->text(column));
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
    selected_path = "/"+path+"/";
}

void MainWindow::on_vfsTreeWidget_itemChanged(QTreeWidgetItem *item, int column)
{

}
