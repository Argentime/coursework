#pragma once

#include <QDialog>
#include "ui_SaveWindow.h"
#include "SaveSlot.h"


class SaveWindow : public QDialog
{
	Q_OBJECT

public:
	SaveWindow(QWidget *parent = nullptr);
	~SaveWindow();


private:
	Ui::SaveWindowClass ui;
	SaveSlot** sv=nullptr;
	SaveSlot* tsv = nullptr;
	void connectSlots();
	void on_slot_clicked(int numb);
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();

	int saveSlotCount[2];
};
