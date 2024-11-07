#pragma once

#include <QWidget>
#include "ui_SaveSlot.h"

class SaveSlot : public QWidget
{
	Q_OBJECT

public:
	SaveSlot(QWidget *parent = nullptr);
	~SaveSlot();
	

private:
	Ui::SaveSlotClass ui;
};
