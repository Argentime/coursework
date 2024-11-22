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

	int saveCount;
};
