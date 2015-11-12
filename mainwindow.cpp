#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_system.h"

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
    vnode v_obj;
    v_obj.n_type = file;
    v_obj.n_inode.n_name = ui->lineEdit->text();

    QListWidgetItem file_list;;
    file_list.setText(v_obj.n_inode.n_name);

    if(file_list.text() != NULL)
    {
        ui->listWidget->addItem(file_list.text());
        ui->comboBoxDelete->addItem(file_list.text());
        ui->comboBoxPrint->addItem(file_list.text());
    }
}

void MainWindow::on_deletePushButton_clicked()
{
    if(ui->comboBoxDelete->currentText() != NULL)
    {
        ui->comboBoxDelete->removeItem(ui->comboBoxDelete->currentIndex());
    }
}
