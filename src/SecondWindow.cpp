#include "header/SecondWindow.h"
#include "header/MainWindow.h"
#include "header/functions.h"
#include "header/SaveWindow.h"
#include <random>

using namespace std;
using json = nlohmann::json;

SecondWindow::SecondWindow(MainWindow* menu, QWidget* parent)
	: QMainWindow(parent), mainMenu(menu)
{
    game = new Game(this);
    ui.setupUi(this);
    Qt::Window;
    QString buttonStyle = R"(
            QPushButton {
                background-color: rgba(122, 122, 122, 0);
                border: none;
                border-radius: 3px;  
                padding: 4px;
                font-weight: 600;
                text-align: left;
                color: white;
            }
            QPushButton:hover {
                background-color: rgba(161, 161, 161, 20);
            }
            QPushButton:pressed {
                background-color: rgba(161, 161, 161, 10);
            }
            QPushButton:disabled {
		        background-color: rgba(122, 122, 122, 0);
                border: none;
                border-radius: 3px;
                padding: 4px;
                font-weight: 600;
                text-align: left;
                color: white;
            }
        )";

    for (int i = 0; i < 11; ++i) {
        questButtons.emplace_back(make_unique<QPushButton>(QString::number(i), this));
        questButtons[i].get()->setStyleSheet(buttonStyle);
        questButtons[i].get()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        questButtons[i].get()->setMinimumHeight(1);
        questButtons[i].get()->setIcon(QIcon(":/rec/resources/background_images/pimp.png"));
        ui.verticalLayout->insertWidget(i,questButtons[i].get());
    }
    connectSlots();
}

SecondWindow::~SecondWindow() {
    questButtons.clear();
}


void SecondWindow::setImage(QString Path) {
    try {
        currentPath = Path;
        originalPixmap = QPixmap(currentPath);
        applyRoundedMask(ui.label_2, originalPixmap);
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting image: " << e.what() << std::endl;
    }
}

void SecondWindow::connectSlots() {
    connect(ui.pushButton_7, &QPushButton::clicked, this, &SecondWindow::on_menuButton_clicked);
    connect(ui.pushButton_8, &QPushButton::clicked, this, &SecondWindow::on_saveButton_clicked);
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

    

    int width = event->size().width();
    int newSize = max(7.5, width / 150);
    QFont font = ui.label->font();
    font.setPointSize(newSize);
    ui.label->setFont(font);
    newSize = max(7.5, width / 200);
    font = ui.label_3->font();
    font.setPointSize(newSize);
    ui.label_3->setFont(font);
    for (int i = 0; i < 11; ++i) {
        questButtons[i]->setFont(font);
    }
    applyRoundedMask(ui.label_2, originalPixmap);

}
void SecondWindow::showEvent(QShowEvent* event) {
    applyRoundedMask(ui.label_2, originalPixmap);
}
void SecondWindow::on_menuButton_clicked(){
    game->saveGame("saves/autoSave.json");
    hide();
    mainMenu->show();
}
void SecondWindow::startGame(std::string path){

    makeAllButtonsInactive();
    questButtons[0].get()->setText("Осмотреться");
    activeButtonCSS(questButtons[0].get());
    questButtons[1].get()->setText("Вернуться назад");
    activeButtonCSS(questButtons[1].get());
    game->startNewGame();
    game->start();
    if (path != "") {
        game->loadGame(path);
    }
    ui.label_3->setText(heroStatus());
    applyRoundedMask(ui.label_2, originalPixmap);
}

QString SecondWindow::heroStatus() {
    using enum Element;
    const Character* characterPtr = game->hero.get();

    QString status = QString("Имя: %1\n").arg(QString::fromStdString(game->hero->getName()));
    status += QString("%1\n").arg(QString::fromStdString(characterPtr->status()));
    status += QString("Сосредоточенность: %1\n").arg(game->hero->getFocus());
    status += QString("Баланс: %1\n").arg(game->hero->getMoney());
    status += "Мана:\n";
    status += QString("Огонь: %1\n").arg(game->hero->getMana(Fire));
    status += QString("Земля: %1\n").arg(game->hero->getMana(Earth));
    status += QString("Вода: %1\n").arg(game->hero->getMana(Water));
    status += QString("Воздух: %1\n").arg(game->hero->getMana(Air));
    status += QString("Дух: %1\n").arg(game->hero->getMana(Spirit));

    return status;
}

void SecondWindow::processQuestButton(int activeButton) {
    
    qDebug() << "slot " << activeButton << " clicked";
    game->start();
    ui.label_3->setText(heroStatus());
}

void SecondWindow::updateButtons(const std::vector<std::pair<QString, std::function<void()>>>& actions) {

    makeAllButtonsInactive();

    for (auto& button : questButtons) {
        button->hide();
        disconnect(button.get(), nullptr, this, nullptr);
        connect(button.get(), &QPushButton::clicked, this, [this] { ui.label_3->setText(heroStatus()); });
    }


    for (size_t i = 0; i < actions.size() && i < questButtons.size(); ++i) {
        questButtons[i]->setText(actions[i].first);
        connect(questButtons[i].get(), &QPushButton::clicked, this, actions[i].second);
        questButtons[i]->show();
        activeButtonCSS(questButtons[i].get());
    }
    
    qDebug() << "Actions updated. Total:" << actions.size();
    for (const auto& action : actions) {
        qDebug() << "Action:" << action.first;
    }
}

void  SecondWindow::makeAllButtonsInactive() {
    for (int i = 0; i < 11; i++) {
        inactiveButtonCSS(questButtons[i].get());
    }
}

void SecondWindow::on_saveButton_clicked() {
    game->saveGame("saves/autoSave.json");
    SW = new SaveWindow(this,this->mainMenu, game->hero->getMoney(), currentPath.toStdString(), "saves/autoSave.json");
    SW->show();
}