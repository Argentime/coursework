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
		"QPushButton:pressed{"
		"background-color:rgba(128,128,128,150)"
		"}"
	);
	connect(floatingButton, &QPushButton::clicked, this, &SaveSlot::on_pushButton_clicked);
}
SaveSlot::SaveSlot(const SaveSlot& other)
	{
	floatingButton = new QPushButton(other.floatingButton);
	setUi(other.ui);
}
void SaveSlot::setUi(Ui::SaveSlotClass ui) {
	this->ui = ui;
}

SaveSlot& SaveSlot::operator=(const SaveSlot& other) {
	if (this != &other) {
		floatingButton = new QPushButton(other.floatingButton);
		setUi(other.ui);
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
