#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphwidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SelectFileButton_clicked();
    void setupUi();

private:
    GraphWidget* graphWidget;
};
#endif // MAINWINDOW_H
