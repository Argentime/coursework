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
    }
}

void MainWindow::on_pushButton_4_clicked() {
    QWidget* container = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(container);
    sWindow = new SaveWindow(this);
    SaveSlot *sv = new SaveSlot();
    layout->addWidget(sv);
    SaveSlot* sv1 = new SaveSlot();
    layout->addWidget(sv1);
    SaveSlot* sv2 = new SaveSlot();
    layout->addWidget(sv2);
    SaveSlot* sv3 = new SaveSlot();
    layout->addWidget(sv3);
    SaveSlot* sv4 = new SaveSlot();
    layout->addWidget(sv4);
    SaveSlot* sv5 = new SaveSlot();
    layout->addWidget(sv5);
    sWindow->ui.scrollArea->setWidget(container);
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
    gWindow->defaultLoad();
}

