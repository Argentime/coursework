#include "header/MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QDebug>
#include "header/functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connectSlots();
}

MainWindow::~MainWindow()
{}

void MainWindow::connectSlots() {
    connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
}

void MainWindow::on_pushButton_clicked()
{

    QMessageBox::StandardButton reply = QMessageBox::information(this, "Выход", "Вы точно хотите выйти из игры?", QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    window = new SecondWindow(this, nullptr);
    QPixmap originalPixmap(":/rec/resources/background_images/Racer.png");
    window->setImage(originalPixmap);
    window->setStyleSheet(
        "QMainWindow {"
        "background-image: url(:/rec/resources/background_images/2BG.png);"
        "background - position: center;"
        "background - repeat: no - repeat; "
        "}"
    );
    hide();
    window->show();
}

