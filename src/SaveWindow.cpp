#include "header/SaveWindow.h"
#include "header/SaveSlot.h"
#include "header/functions.h"
#include "header/MainWindow.h"
#include <iostream>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>
#include <filesystem>

SaveWindow::SaveWindow(QWidget* parent, MainWindow* menu, const int heroMoney, const std::string pixmapPath, const std::string saveFilePath)
	: QDialog(parent), menu(menu), heroMoney(heroMoney), pixmapPath(pixmapPath), saveFilePath(saveFilePath)
{
    ui.setupUi(this);
    loadSaveSlotsFromJson("saves/save_slots.json");
    connectSlots();
    makeButtonsInactive();
    ui.label->setPixmap(QPixmap(":/rec/resources/background_images/NA.png"));
    if (heroMoney == -1) {
        delete ui.pushButton_5;
    }
}

void SaveWindow::loadSaveSlotsFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        qDebug() << "Ошибка: Не удалось открыть файл слотов сохранения.";
        return;
    }

    try {
        json saveSlotsJson;
        file >> saveSlotsJson;
        file.close();

        int slotCount = saveSlotsJson["slot_count"];
        saveSlotCount[0] = slotCount;
        saveSlotCount[1] = -1;
        sv.clear();
        for (int i = 0; i < slotCount; i++) {
            auto slotInfo = saveSlotsJson["slots"][i];
            auto slot = std::make_unique<SaveSlot>();
            std::string pathToPixmap = slotInfo["pathToPixmap"].get<std::string>();
            slot->updateSlot(QString::fromStdString(slotInfo["name"].get<std::string>()),pathToPixmap, slotInfo["path"].get<std::string>(), slotInfo["money"].get<int>());
            slot->ui.label_2->setText(QString::fromStdString(slotInfo["time"].get<std::string>()));
            sv.push_back(std::move(slot));
            ui.scrollAreaWidgetContents->layout()->addWidget(sv.back().get());
        }
        ui.scrollAreaWidgetContents->layout()->removeWidget(ui.pushButton_5);
        ui.scrollAreaWidgetContents->layout()->addWidget(ui.pushButton_5);
        ui.scrollAreaWidgetContents->layout()->removeItem(ui.verticalSpacer);
        ui.scrollAreaWidgetContents->layout()->addItem(ui.verticalSpacer);
        qDebug() << "Слоты успешно загружены из файла.";

    }
    catch (const std::exception& e) {
        qDebug() << "Ошибка загрузки слотов: " << e.what();
        saveSlotCount[0] = 0;
        saveSlotCount[1] = -1;
    }
}

void SaveWindow::saveSlotsToJson(const std::string& filename) {
    if (heroMoney != -1 && saveSlotCount[1] != -1) {
        std::ifstream sourceFile(saveFilePath);
        if (!sourceFile.is_open()) {
            throw std::runtime_error("Ошибка: не удалось открыть исходный файл.");
        }

        json jsonData;
        sourceFile >> jsonData;
        sourceFile.close();

        std::ofstream destinationFile(filename + std::to_string(saveSlotCount[1]) + ".json");
        if (!destinationFile.is_open()) {
            throw std::runtime_error("Ошибка: не удалось открыть файл для записи.");
        }

        destinationFile << jsonData.dump(4);
        sv[saveSlotCount[1]]->setPath(filename + std::to_string(saveSlotCount[1]) + ".json");
        sv[saveSlotCount[1]]->pixmapPath = pixmapPath;
        destinationFile.close();
    }
        std::ofstream file(filename + ".json");
        if (!file.is_open()) {
            qDebug() << "Ошибка: Не удалось открыть файл для записи слотов.";
            return;
        }
    
    try {
        json saveSlotsJson;
        saveSlotsJson["slot_count"] = sv.size();
        for (int i = 0; i < sv.size(); i++) {
            json slotInfo;
            slotInfo["name"] = sv[i]->getUiLabel();
            slotInfo["path"] = sv[i]->getPath();
            slotInfo["pathToPixmap"] = sv[i]->pixmapPath;
            slotInfo["money"] = sv[i]->ui.label_3->text().toInt();
            slotInfo["time"] = sv[i]->ui.label_2->text().toStdString();
            saveSlotsJson["slots"].push_back(slotInfo);
        }

        file << saveSlotsJson.dump(4);
        file.close();
        qDebug() << "Слоты успешно сохранены.";
    }
    catch (const std::exception& e) {
        qDebug() << "Ошибка сохранения слотов: " << e.what();
    }
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
    makeButtonsActive();
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
    ui.label->setPixmap(QPixmap(QString::fromStdString(sv[numb]->pixmapPath)));

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
    oldSlot->ui.label_2->setText(QDateTime::currentDateTime().toString("MM.dd HH:mm"));
    oldSlot->ui.label_3->setText(QString::number(heroMoney));
    tsv.reset();
    connect(oldSlot->floatingButton, &QPushButton::clicked, this, [this, newSaveCount] { on_slot_clicked(newSaveCount); });
    sv[newSaveCount].get()->show();
    makeButtonsActive();
    if (newSaveCount == saveSlotCount[0]) {
        saveSlotCount[0]++;
    }
    saveSlotsToJson("saves/save_slots");
    qDebug() << "Сохранения обновлены.";
}
void SaveWindow::on_pushButton_2_clicked() {
    hide();
    if (menu->gWindow != nullptr) menu->gWindow->hide();
    menu->openSecondWindow();
    menu->gWindow->startGame(sv[saveSlotCount[1]]->getPath());
    
}
void SaveWindow::on_pushButton_3_clicked() {
    
    sv.erase(sv.begin() + saveSlotCount[1]);
    if (std::filesystem::remove("saves/save_slots" + std::to_string(saveSlotCount[1]) + ".json")) {
        std::cout << "Файл успешно удален" << std::endl;
    }
    else {
        std::cerr << "Ошибка удаления файла" << std::endl;
    }
    saveSlotCount[0]--;
    reconnectSlots();
    saveSlotCount[1] = -1;
    tsv.reset();
    makeButtonsInactive();
    saveSlotsToJson("saves/save_slots");
    
}
void SaveWindow::on_pushButton_4_clicked() {
    saveSlotsToJson("saves/save_slots");
    hide();
    menu->gWindow->setEnabled(true);
}
void SaveWindow::on_pushButton_5_clicked() {
    if (sv.size() > saveSlotCount[0]) sv.pop_back();
    sv.emplace_back(std::make_unique<SaveSlot>());
    ui.label->setPixmap(QPixmap());
    on_slot_clicked(saveSlotCount[0]);
    ui.pushButton_5->setEnabled(false);
    ui.scrollAreaWidgetContents->layout()->addWidget(sv[saveSlotCount[0]].get());
    sv[saveSlotCount[0]].get()->hide();
    ui.scrollAreaWidgetContents->layout()->removeWidget(ui.pushButton_5);
    ui.scrollAreaWidgetContents->layout()->addWidget(ui.pushButton_5);
    ui.scrollAreaWidgetContents->layout()->removeItem(ui.verticalSpacer);
    ui.scrollAreaWidgetContents->layout()->addItem(ui.verticalSpacer);
}

void SaveWindow::makeButtonsActive() {
    if (heroMoney != -1) {
        ui.pushButton_5->setEnabled(true);
        ui.pushButton->setEnabled(true);
    }
    ui.pushButton_2->setEnabled(true);
    ui.pushButton_3->setEnabled(true);
}

void SaveWindow::makeButtonsInactive() {
    ui.pushButton->setEnabled(false);
    ui.pushButton_2->setEnabled(false);
    ui.pushButton_3->setEnabled(false);
}
