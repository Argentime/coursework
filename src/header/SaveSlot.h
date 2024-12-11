#pragma once

#include <QWidget>
#include "ui_SaveSlot.h"
#include <qpushbutton.h>

class SaveSlot : public QWidget
{
	Q_OBJECT

public:
	SaveSlot(QWidget *parent = nullptr);
	SaveSlot(const SaveSlot& other);
	~SaveSlot();
	bool isButtonActive=false;
	QPushButton* floatingButton;
	QPixmap originalPixmap;
	void setUi(Ui::SaveSlotClass ui);
	SaveSlot& operator=(const SaveSlot& other);
	void setActive(bool isActive);
	

private:
	Ui::SaveSlotClass ui;
	void on_pushButton_clicked();
	void resizeEvent(QResizeEvent* event) override;

};
