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
    saveSlotCount[0] = 7;
    saveSlotCount[1] = -1;
    sv = new SaveSlot * [saveSlotCount[0]];
    for (int i = 0; i < saveSlotCount[0]; i++) {
        sv[i] = new SaveSlot();
        layout->addWidget(sv[i]);
    }
    ui.scrollArea->setWidget(container);
    connectSlots();
}

SaveWindow::~SaveWindow()
{}

void SaveWindow::connectSlots() {
    for (int i = 0; i < saveSlotCount[0]; i++) {
        connect(sv[i]->floatingButton, &QPushButton::clicked, this, [this,i] { on_slot_clicked(i); });
    }
    connect(ui.pushButton, &QPushButton::clicked, this, &SaveWindow::on_pushButton_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &SaveWindow::on_pushButton_2_clicked);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &SaveWindow::on_pushButton_3_clicked);
}
void SaveWindow::on_slot_clicked(int numb) {
    sv[numb]->floatingButton->setDisabled(true);
    sv[numb]->floatingButton->lower();
    if (saveSlotCount[1] != -1) {
        sv[saveSlotCount[1]] = tsv;
        sv[saveSlotCount[1]]->floatingButton->raise();
        sv[saveSlotCount[1]]->floatingButton->setEnabled(true);
        sv[saveSlotCount[1]]->floatingButton->setDisabled(false);
        delete tsv;
    }
    
    tsv = new SaveSlot(sv[numb]);
    //tsv->floatingButton->lower();
    ui.verticalLayoutWidget->layout()->addWidget(tsv);
    qDebug() << "slot " << numb << " clicked";
    saveSlotCount[1] = numb;
}
void SaveWindow::on_pushButton_clicked() {

}
void SaveWindow::on_pushButton_2_clicked() {

}
void SaveWindow::on_pushButton_3_clicked() {

}
