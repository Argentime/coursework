#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QResizeEvent>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QResizeEvent>
#include <QRegion>
#include <QPainter>
#include <qpainterpath.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include "ui_SecondWindow.h"
#include "functions.h"

class MainWindow;

class SecondWindow : public QMainWindow
{
	Q_OBJECT

public:

	SecondWindow(MainWindow* menu, QWidget* parent);
	~SecondWindow();
	Ui::SecondWindowClass ui;

	void setImage(const QPixmap& pixmap);

	void startGame();

	int getActiveButton();
	void defaultLoad();
	void userLoad();

private:
	
	QPixmap originalPixmap;
	MainWindow* mainMenu;
	Hero* hero;
	int activeButton;
	bool isBookPickUp = false;
	bool spellChoose = false;
	
	QString heroStatus();
	void connectSlots();
	void applyRoundedMask(QLabel* label, const QPixmap& originalPixmap);

	void on_menuButton_clicked();
	
	void resizeEvent(QResizeEvent* event) override;

	void showEvent(QShowEvent* event) override;

	void handleButton1();
	void handleButton2();
	void handleButton3();
	void handleButton4();
	void handleButton5();
	void handleButton6();
	void handleButton7();
	void handleButton8();
	void handleButton9();
	void handleButton10();
	void handleButton11();
	void processActiveButton();
	void makeAllButtonsInactive();
};

