#include "header/SaveSlot.h"
#include "qpushbutton.h"

SaveSlot::SaveSlot(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	floatingButton = new QPushButton("", this);
	floatingButton->move(0, 0);
	floatingButton->raise();
	floatingButton->setStyleSheet(
		"QPushButton{"
		"background-color:transparent;"
		"border:none;"
		"}"
		"QPushButton:hover{"
		"background-color:rgba(128,128,128,50)"
		"}"
		"QPushButton:disabled {"
		"background-color:rgba(128,128,128,150)"
		"}"
	);
}
SaveSlot::SaveSlot(const SaveSlot& other):QWidget(nullptr)
	{
	ui.setupUi(this);
	floatingButton = new QPushButton("", this);
	floatingButton->move(0, 0);
	floatingButton->raise();
	floatingButton->setStyleSheet(
		"QPushButton{"
		"background-color:transparent;"
		"border:none;"
		"}"
	);
	ui.label->setText(other.ui.label->text());
	ui.label_2->setText(other.ui.label_2->text());
	ui.label_3->setText(other.ui.label_3->text());
	ui.lineEdit->setText(other.ui.lineEdit->text());
}
void SaveSlot::setUi(Ui::SaveSlotClass ui) {
	this->ui = ui;
}

SaveSlot& SaveSlot::operator=(const SaveSlot& other) {
	if (this != &other) {
		ui.label->setText(other.ui.label->text());
		ui.label_2->setText(other.ui.label_2->text());
		ui.label_3->setText(other.ui.label_3->text());
		ui.lineEdit->setText(other.ui.lineEdit->text());
	}
	return *this;
}

void SaveSlot::updateSlot(const QString& lineEditText, const std::string& pixmap, const std::string& path, int money) {
	ui.lineEdit->setText(lineEditText);
	pixmapPath = pixmap;
	this->path = path;
	ui.label_3->setText(QString::number(money));
}
void SaveSlot::resizeEvent(QResizeEvent* event) {
	floatingButton->setGeometry(0, 0, width(), height());
}
SaveSlot::~SaveSlot()
{}
void SaveSlot::setActive(bool isActive) {
	ui.lineEdit->setReadOnly(!isActive);
}

void SaveSlot::setUiLabel(const std::string& label) {
	ui.lineEdit->setText(QString::fromStdString(label));
}

std::string SaveSlot::getUiLabel() const {
	return ui.lineEdit->text().toStdString();
}

void SaveSlot::setPath(const std::string& path) {
	this->path = path;
}

std::string SaveSlot::getPath() {
	return path;
}