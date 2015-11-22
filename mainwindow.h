#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addPushButton_clicked();

    void on_deletePushButton_clicked();

    void on_printPushButton_clicked();

    void on_vfsTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_vfsTreeWidget_itemChanged(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QTreeWidgetItem *selected_widget, *drive_item;

    void addTreeChild(QTreeWidgetItem *parent,
                      QString name, QString description);
};

#endif // MAINWINDOW_H
