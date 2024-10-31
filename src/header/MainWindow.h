#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "SecondWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_pushButton_clicked();
    
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindowClass ui;
    SecondWindow* window;

    void openSecondWindow();
    void connectSlots();
};
