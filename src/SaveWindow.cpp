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
        saveSlots.addSaveSlot(sv[i]);
        layout->addWidget(saveSlots.getSaveSlot(i));
    }
    ui.scrollArea->setWidget(container);
    connectSlots();
}

SaveWindow::~SaveWindow()
{}

void SaveWindow::connectSlots() {
    for (SaveSlotContainer::iterator it = saveSlots.begin(); it != saveSlots.end(); ++it) {
        SaveSlot* slot = *it;
        connect(slot->floatingButton, &QPushButton::clicked, this, [this, slot] { on_slot_clicked(slot); });
    }
    connect(ui.pushButton, &QPushButton::clicked, this, &SaveWindow::on_pushButton_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &SaveWindow::on_pushButton_2_clicked);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &SaveWindow::on_pushButton_3_clicked);
}
void SaveWindow::on_slot_clicked(SaveSlot* slot) {
    slot->floatingButton->setDisabled(true);
    slot->floatingButton->lower();
    if (saveSlotCount[1] != -1) {
        SaveSlot* oldSlot = saveSlots.getSaveSlot(saveSlotCount[1]);
        oldSlot->floatingButton->raise();
        oldSlot->floatingButton->setEnabled(true);
        oldSlot->floatingButton->setDisabled(false);
        delete tsv;
        tsv = nullptr;
    }

    tsv = new SaveSlot(slot);
    //tsv->floatingButton->lower();
    ui.verticalLayoutWidget->layout()->addWidget(tsv);
    qDebug() << "slot clicked";
    int index = 0;
    for (SaveSlotContainer::iterator it = saveSlots.begin(); it != saveSlots.end(); ++it) {
        if (*it == slot) {
            index = it.index;
            break;
        }
    }
    saveSlotCount[1] = index;
}
void SaveWindow::on_pushButton_clicked() {

}
void SaveWindow::on_pushButton_2_clicked() {

}
void SaveWindow::on_pushButton_3_clicked() {

}
