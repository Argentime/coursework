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
	void updateSlot(const QString& lineEditText, const QPixmap& pixmap, const std::string& path, int money);
	~SaveSlot();
	bool isButtonActive=false;
	QPushButton* floatingButton;
	QPixmap originalPixmap;
	void setUi(Ui::SaveSlotClass ui);
	SaveSlot& operator=(const SaveSlot& other);
	void setActive(bool isActive);

	void setUiLabel(const std::string& label);
	std::string getUiLabel() const;
	void setPath(const std::string& path);
	std::string getPath();
	

private:
	Ui::SaveSlotClass ui;
	void resizeEvent(QResizeEvent* event) override;
	std::string path;
	friend class SaveWindow;

};
