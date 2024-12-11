#include "header/SecondWindow.h"
#include "header/MainWindow.h"
#include "header/functions.h"
#include <random>

using namespace std;
using json = nlohmann::json;

SecondWindow::SecondWindow(MainWindow* menu, QWidget* parent)
	: QMainWindow(parent), mainMenu(menu)
{
    hero = new Hero("", 0, 0, 0);
    game = new Game(this);
    ui.setupUi(this);
	connectSlots();
    Qt::Window;
}

SecondWindow::~SecondWindow()
{
    saveHeroToJson(*hero, "resources/Save.json");
    delete hero;
}

void SecondWindow::setImage(const QPixmap& pixmap) {
    try {
        originalPixmap = pixmap;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting image: " << e.what() << std::endl;
    }
}

int SecondWindow::getActiveButton() {
	return activeButton;
}

void SecondWindow::connectSlots() {
    for (int i = 1; i <= 11; i++) {
        connect(ui.pushButton, &QPushButton::clicked, this, [this, i]() {processQuestButton(i); });
    }
    connect(ui.pushButton_7, &QPushButton::clicked, this, &SecondWindow::on_menuButton_clicked);
}

void SecondWindow::applyRoundedMask(QLabel* label, const QPixmap& pixmap)
{
    if (!label) {
        qDebug() << "Label is null!";
        return;
    }

    int width = label->width();
    int height = label->height();
    int cornerRadius = 80;

    QPixmap scaledPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap roundedPixmap(width, height);
    roundedPixmap.fill(Qt::transparent);

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    int xOffset = (width - scaledPixmap.width()) / 2;

    QPainterPath path;
    path.moveTo(cornerRadius, 0);
    path.lineTo(width,0);
    path.lineTo(width, height - cornerRadius);
    path.quadTo(width, height, width-cornerRadius, height);
    path.lineTo(0, height);
    path.lineTo(0, cornerRadius);
    path.quadTo(0,0,cornerRadius,0);

    painter.setClipPath(path);
    painter.drawPixmap(xOffset, 0, scaledPixmap);
    painter.end();

    label->setPixmap(roundedPixmap);
    label->setScaledContents(true);

}
void SecondWindow::resizeEvent(QResizeEvent* event) {

    applyRoundedMask(ui.label_2, originalPixmap);

    int width = event->size().width();
    int newSize = max(8, width / 150);
    QFont font = ui.label->font();
    font.setPointSize(newSize);
    ui.label->setFont(font);
    newSize = max(8, width / 200);
    font = ui.label_3->font();
    font.setPointSize(newSize);
    ui.label_3->setFont(font);

}
void SecondWindow::showEvent(QShowEvent* event) {
    applyRoundedMask(ui.label_2, originalPixmap);
}
void SecondWindow::on_menuButton_clicked(){
    hide();
    mainMenu->show();
}
void SecondWindow::startGame(){

    game->startNewGame();
    game->start();
    printMenu(1, this->ui.label);
    makeAllButtonsInactive();
    ui.pushButton->setText("Осмотреться");
    activeButtonCSS(ui.pushButton);
    ui.label_3->setText(heroStatus());

}

void SecondWindow::defaultLoad() {
    loadHeroFromJson(*hero, "resources/DefaultSave.json");
    startGame();
}

void SecondWindow::userLoad() {
    loadHeroFromJson(*hero, "resources/wsSave.json");
    startGame();
}

QString SecondWindow::heroStatus() {
    using enum Element;
    const Character* characterPtr = hero;

    QString status = QString("Имя: %1\n").arg(QString::fromStdString(hero->getName()));
    status += QString("%1\n").arg(QString::fromStdString(characterPtr->status()));
    status += QString("Сосредоточенность: %1\n").arg(hero->getFocus());
    status += "Мана:\n";
    status += QString("Огонь: %1\n").arg(hero->getMana(Fire));
    status += QString("Земля: %1\n").arg(hero->getMana(Earth));
    status += QString("Вода: %1\n").arg(hero->getMana(Water));
    status += QString("Воздух: %1\n").arg(hero->getMana(Air));
    status += QString("Дух: %1\n").arg(hero->getMana(Spirit));

    return status;
}

void SecondWindow::processQuestButton() {
    
    

    ui.label_3->setText(heroStatus());
    
}

void  SecondWindow::makeAllButtonsInactive() {
    inactiveButtonCSS(ui.pushButton);
	inactiveButtonCSS(ui.pushButton_2);
	inactiveButtonCSS(ui.pushButton_3);
	inactiveButtonCSS(ui.pushButton_4);
	inactiveButtonCSS(ui.pushButton_5);
	inactiveButtonCSS(ui.pushButton_6);
    inactiveButtonCSS(ui.pushButton_9);
    inactiveButtonCSS(ui.pushButton_10);
    inactiveButtonCSS(ui.pushButton_11);
    inactiveButtonCSS(ui.pushButton_12);
    inactiveButtonCSS(ui.pushButton_13);

}
void SecondWindow::handleButton1() {
    activeButton = 1;
    processActiveButton();
}
void SecondWindow::handleButton2() {
    activeButton = 2;
    processActiveButton();
}
void SecondWindow::handleButton3() {
    activeButton = 3;
    processActiveButton();
}
void SecondWindow::handleButton4() {
    activeButton = 4;
    processActiveButton();
}
void SecondWindow::handleButton5() {
    activeButton = 5;
    processActiveButton();
}
void SecondWindow::handleButton6() {
    activeButton = 6;
    processActiveButton();
}
void SecondWindow::handleButton7() {
    activeButton = 7;
    processActiveButton();
}
void SecondWindow::handleButton8() {
    activeButton = 8;
    processActiveButton();
}
void SecondWindow::handleButton9() {
    activeButton = 9;
    processActiveButton();
}
void SecondWindow::handleButton10() {
    activeButton = 10;
    processActiveButton();
}
void SecondWindow::handleButton11() {
    activeButton = 11;
    processActiveButton();
}
