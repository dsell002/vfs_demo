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

private:
    Ui::MainWindow *ui;

    void addTreeRoot(QString name, QString description);
    void addTreeChild(QTreeWidgetItem *parent,
                      QString name, QString description);
};

#endif // MAINWINDOW_H
