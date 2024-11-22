#include "header/SaveWindow.h"
#include "header/SaveSlot.h"

SaveWindow::SaveWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QWidget* container = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout(container);
    saveCount = 5;
    sv = new SaveSlot * [saveCount];
    for (int i = 0; i <= saveCount; i++) {
        sv[i] = new SaveSlot();
        layout->addWidget(sv[i]);
    }
    ui.scrollArea->setWidget(container);
}

SaveWindow::~SaveWindow()
{}
