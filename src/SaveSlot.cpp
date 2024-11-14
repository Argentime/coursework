#include "header/SaveSlot.h"

SaveSlot::SaveSlot(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    button = new QPushButton(this);
    //button->setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");

    // ������������� ������� ������� (��������, ���� ������)
    QRegion region(rect());
    button->setMask(region);

    // ���������� ������ clicked() � �����
}

void SaveSlot::connectSlots() {
    connect(button, &QPushButton::clicked, this, &SaveSlot::onButtonClicked);
}

void SaveSlot::onButtonClicked() {
    

    // ������ ������� ������ ������� � ���������� ��
    button->setVisible(true);
}

SaveSlot::~SaveSlot()
{}
