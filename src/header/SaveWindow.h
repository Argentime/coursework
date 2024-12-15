#pragma once

#include <QDialog>
#include <QObject>
#include "ui_SaveWindow.h"
#include "SaveSlot.h"

class MainWindow;

class SaveWindow : public QDialog
{
	Q_OBJECT

public:
	SaveWindow(QWidget* parent, MainWindow* menu, const int heroMoney, const std::string pixmapPath, const std::string saveFilePath);
	~SaveWindow();

private:
	Ui::SaveWindowClass ui;
	std::vector<std::unique_ptr<SaveSlot>> sv; 
	std::unique_ptr<SaveSlot> tsv;
	std::string pixmapPath;
	std::string saveFilePath;
	MainWindow* menu;
	int heroMoney;
	int saveSlotCount[2] = {-1, -1};
	void connectSlots();
	void reconnectSlots();
	void on_slot_clicked(int numb);
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void saveSlotsToJson(const std::string& filename);
	void loadSaveSlotsFromJson(const std::string& filename);
	void makeButtonsActive();
	void makeButtonsInactive();
};
