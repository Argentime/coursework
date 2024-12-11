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
	originalPixmap = QPixmap(":/rec/resources/background_images/Racer.png");
	connect(floatingButton, &QPushButton::clicked, this, &SaveSlot::on_pushButton_clicked);
}
SaveSlot::SaveSlot(const SaveSlot& other):QWidget(nullptr)
	{
	ui.setupUi(this);
	floatingButton = new QPushButton("", this);
	floatingButton->move(0, 0);
	floatingButton->raise();
	floatingButton->setStyleSheet("");
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

void SaveSlot::on_pushButton_clicked() {
	isButtonActive = true;
}
void SaveSlot::resizeEvent(QResizeEvent* event) {
	floatingButton->setGeometry(0, 0, width(), height());
}
SaveSlot::~SaveSlot()
{}
void SaveSlot::setActive(bool isActive) {
	ui.lineEdit->setReadOnly(!isActive);
}
