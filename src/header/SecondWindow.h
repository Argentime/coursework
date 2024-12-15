#pragma once

#include <QtWidgets/QMainWindow>
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
#include "SaveWindow.h"

class MainWindow;
class Game;

class SecondWindow : public QMainWindow
{
	Q_OBJECT

public:

	SecondWindow(MainWindow* menu, QWidget* parent);
	~SecondWindow();
	

	void setImage(const QPixmap& pixmap);

	void startGame(std::string path);

	QString heroStatus();
	

private:
	
	SaveWindow *SW;
	QPixmap originalPixmap;
	MainWindow* mainMenu;
	friend class Game;
	friend class Battle;
	friend class SaveWindow;
	Game* game;
	Ui::SecondWindowClass ui;
	
	bool isBookPickUp = false;
	bool spellChoose = false;
	std::vector<std::unique_ptr<QPushButton>> questButtons;

	void connectSlots(); 
	void applyRoundedMask(QLabel* label, const QPixmap& originalPixmap);

	void on_menuButton_clicked();
	
	void resizeEvent(QResizeEvent* event) override;

	void showEvent(QShowEvent* event) override;
	void processQuestButton(int activeButton);
	void updateButtons(const std::vector<std::pair<QString, std::function<void()>>>& actions);
	void makeAllButtonsInactive();
	void on_saveButton_clicked();
};

