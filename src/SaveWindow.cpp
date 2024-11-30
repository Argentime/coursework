#include "header/SaveWindow.h"
#include "header/SaveSlot.h"
#include "header/functions.h"
#include <iostream>

SaveWindow::SaveWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
    saveSlotCount[0] = 7;
    saveSlotCount[1] = -1;
    for (int i = 0; i < saveSlotCount[0]; i++) {
        sv.emplace_back(std::make_unique<SaveSlot>());
        ui.scrollAreaWidgetContents->layout()->addWidget(sv[i].get());
        
    }
    ui.scrollAreaWidgetContents->layout()->removeWidget(ui.pushButton_5);
    ui.scrollAreaWidgetContents->layout()->addWidget(ui.pushButton_5);
    ui.pushButton->setEnabled(false);
    ui.pushButton_3->setEnabled(false);
    ui.pushButton_2->setEnabled(false);
    connectSlots();
}

SaveWindow::~SaveWindow() = default;

void SaveWindow::connectSlots() {
    for (int i = 0; i < saveSlotCount[0]; i++) {
        connect(sv[i]->floatingButton, &QPushButton::clicked, this, [this,i] { on_slot_clicked(i); });
    }
    connect(ui.pushButton, &QPushButton::clicked, this, &SaveWindow::on_pushButton_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &SaveWindow::on_pushButton_2_clicked);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &SaveWindow::on_pushButton_3_clicked);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &SaveWindow::on_pushButton_4_clicked);
    connect(ui.pushButton_5, &QPushButton::clicked, this, &SaveWindow::on_pushButton_5_clicked);
}
void SaveWindow::reconnectSlots() {
    for (int i = 0; i < saveSlotCount[0]; i++) {
        disconnect(sv[i]->floatingButton, &QPushButton::clicked, this, nullptr);
        connect(sv[i]->floatingButton, &QPushButton::clicked, this, [this, i] { on_slot_clicked(i); });
    }
}
void SaveWindow::on_slot_clicked(int numb) {
    sv[numb]->floatingButton->setEnabled(false);
    sv[numb].get()->setActive(false);
    ui.pushButton_5->setEnabled(true);
    ui.pushButton_3->setEnabled(true);
    ui.pushButton->setEnabled(true);
    if (!ui.verticalLayoutWidget->layout()->isEmpty()) {
        ui.verticalLayoutWidget->layout()->removeWidget(tsv.get());
        tsv->hide();
        if (saveSlotCount[1] != -1) {
            auto& oldSlot = sv[saveSlotCount[1]];
            *oldSlot = *tsv;
            oldSlot->floatingButton->raise();
            oldSlot->floatingButton->setEnabled(true);
            oldSlot->setActive(false);

            tsv.reset();
        }
    }
    tsv = std::make_unique<SaveSlot>(*sv[numb]);

    tsv->floatingButton->setEnabled(true);
    tsv->floatingButton->lower();
    tsv->setActive(true);

    ui.verticalLayoutWidget->layout()->addWidget(tsv.get());

    saveSlotCount[1] = numb;
    qDebug() << "slot " << numb << " clicked";
}
void SaveWindow::on_pushButton_clicked() {
    int newSaveCount = saveSlotCount[1];
    auto& oldSlot = sv[newSaveCount];
    *oldSlot = *tsv;
    oldSlot->floatingButton->raise();
    oldSlot->floatingButton->setEnabled(true);
    oldSlot->setActive(false);
    tsv.reset();
    connect(oldSlot->floatingButton, &QPushButton::clicked, this, [this, newSaveCount] { on_slot_clicked(newSaveCount); });
    sv[newSaveCount].get()->show();
    ui.pushButton_5->setEnabled(true);
    ui.pushButton->setEnabled(false);
    if (newSaveCount == saveSlotCount[0]) {
        saveSlotCount[0]++;
    }
}
void SaveWindow::on_pushButton_2_clicked() {
    
}
void SaveWindow::on_pushButton_3_clicked() {
    
    sv.erase(sv.begin() + saveSlotCount[1]);
    saveSlotCount[0]--;
    reconnectSlots();
    saveSlotCount[1] = -1;
    tsv.reset();
}
void SaveWindow::on_pushButton_4_clicked() {
    hide();
}
void SaveWindow::on_pushButton_5_clicked() {
    if (sv.size() > saveSlotCount[0]) sv.pop_back();
    sv.emplace_back(std::make_unique<SaveSlot>());
    on_slot_clicked(saveSlotCount[0]);
    ui.scrollAreaWidgetContents->layout()->addWidget(sv[saveSlotCount[0]].get());
    sv[saveSlotCount[0]].get()->hide();
    ui.scrollAreaWidgetContents->layout()->removeWidget(ui.pushButton_5);
    ui.scrollAreaWidgetContents->layout()->addWidget(ui.pushButton_5);
    ui.pushButton_5->setEnabled(false);
    ui.pushButton_3->setEnabled(false);
}
