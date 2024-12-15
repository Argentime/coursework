#include "header/MainWindow.h"
#include <QMessageBox>
#include <QDebug>
#include "header/functions.h"
#include "header/SaveWindow.h"
#include "header/SaveSlot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connectSlots();
}

MainWindow::~MainWindow()
{
    delete gWindow;
}

void MainWindow::connectSlots() {
    connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
}

void MainWindow::on_pushButton_clicked()
{

    QMessageBox::StandardButton reply = QMessageBox::information(this, "Выход", "Вы точно хотите выйти из игры?", QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
        qDebug() << "Выход из игры";
    }
}

void MainWindow::on_pushButton_4_clicked() {
    
    sWindow = new SaveWindow(this,this, -1, "", "");
    sWindow->show();
}

void MainWindow::openSecondWindow() {
    gWindow = new SecondWindow(this, nullptr);
    QPixmap originalPixmap(":/rec/resources/background_images/Racer.png");
    gWindow->setImage(originalPixmap);
    gWindow->setStyleSheet(
        "QMainWindow {"
        "background-image: url(:/rec/resources/background_images/2BG.png);"
        "background - position: center;"
        "background - repeat: no - repeat; "
        "}"
    );
    hide();
    gWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    openSecondWindow();
    gWindow->startGame("");
}

