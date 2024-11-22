#include "header/SaveWindow.h"
#include "header/SaveSlot.h"
#include "header/functions.h"
#include <iostream>

SaveWindow::SaveWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QWidget* container = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout(container);
    saveCount = 7;
    sv = new SaveSlot * [saveCount];
    for (int i = 0; i < saveCount; i++) {
        sv[i] = new SaveSlot();
        layout->addWidget(sv[i]);
    }
    ui.scrollArea->setWidget(container);
    connectSlots();
}

SaveWindow::~SaveWindow()
{}

void SaveWindow::connectSlots() {
    connect(sv[1]->floatingButton, &QPushButton::clicked, this, [this] { on_slot_clicked(1); });
    connect(ui.pushButton, &QPushButton::clicked, this, &SaveWindow::on_pushButton_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &SaveWindow::on_pushButton_2_clicked);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &SaveWindow::on_pushButton_3_clicked);
}
void SaveWindow::on_slot_clicked(int numb) {
    tsv = new SaveSlot;
    tsv = sv[numb];
    tsv->floatingButton->setDisabled(true);
    ui.verticalLayoutWidget->layout()->addWidget(tsv);
    qDebug() << "slot " << numb << " clicked";
}
void SaveWindow::on_pushButton_clicked() {

}
void SaveWindow::on_pushButton_2_clicked() {

}
void SaveWindow::on_pushButton_3_clicked() {

}
