#pragma once

#include <QWidget>
#include "ui_SaveSlot.h"
#include <qpushbutton.h>

class SaveSlot : public QWidget
{
	Q_OBJECT

public:
	SaveSlot(QWidget *parent = nullptr);
	~SaveSlot();
	bool isButtonActive=false;
	

private:
	Ui::SaveSlotClass ui;
	QPushButton* floatingButton;
	void on_pushButton_clicked();
	void resizeEvent(QResizeEvent* event) override;

};
