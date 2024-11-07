#pragma once

#include <QDialog>
#include "ui_SaveWindow.h"

class SaveWindow : public QDialog
{
	Q_OBJECT

public:
	SaveWindow(QWidget *parent = nullptr);
	~SaveWindow();
	Ui::SaveWindowClass ui;

private:
	
};
