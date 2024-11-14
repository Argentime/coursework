#pragma once

#include <QWidget>
#include <qpushbutton.h>
#include "ui_SaveSlot.h"

class SaveSlot : public QWidget
{
	Q_OBJECT

public:
	SaveSlot(QWidget *parent = nullptr);
	~SaveSlot();
	

private:
	Ui::SaveSlotClass ui;
	QPushButton* button;
	static QPushButton* activeButton;

	void connectSlots();
	void onButtonClicked();
};
