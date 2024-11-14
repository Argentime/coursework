#include "header/SaveSlot.h"

SaveSlot::SaveSlot(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    button = new QPushButton(this);
    //button->setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");

    // Устанавливаем область нажатия (например, весь виджет)
    QRegion region(rect());
    button->setMask(region);

    // Подключаем сигнал clicked() к слоту
}

void SaveSlot::connectSlots() {
    connect(button, &QPushButton::clicked, this, &SaveSlot::onButtonClicked);
}

void SaveSlot::onButtonClicked() {
    

    // Делаем текущую кнопку видимой и запоминаем ее
    button->setVisible(true);
}

SaveSlot::~SaveSlot()
{}
