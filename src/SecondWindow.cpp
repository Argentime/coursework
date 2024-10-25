#include "header/SecondWindow.h"
#include "header/MainWindow.h"
#include "header/functions.h"
#include <random>

using namespace std;
using json = nlohmann::json;

SecondWindow::SecondWindow(MainWindow* menu, QWidget* parent)
	: mainMenu(menu), QMainWindow(parent)
{
    hero = new Hero("", 0, 0, 0);
    ui.setupUi(this);
	connectSlots();
    startGame();
    Qt::Window;
}

SecondWindow::~SecondWindow()
{}

void SecondWindow::setImage(const QPixmap& pixmap) {
    originalPixmap = pixmap;
}

int SecondWindow::getActiveButton() {
	return activeButton;
}

void SecondWindow::connectSlots() {
    connect(ui.pushButton, &QPushButton::clicked, this, &SecondWindow::handleButton1);
    connect(ui.pushButton_6, &QPushButton::clicked, this, &SecondWindow::handleButton2);
    connect(ui.pushButton_5, &QPushButton::clicked, this, &SecondWindow::handleButton3);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &SecondWindow::handleButton4);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &SecondWindow::handleButton5);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &SecondWindow::handleButton6);
    connect(ui.pushButton_9, &QPushButton::clicked, this, &SecondWindow::handleButton7);
    connect(ui.pushButton_10, &QPushButton::clicked, this, &SecondWindow::handleButton8);
    connect(ui.pushButton_11, &QPushButton::clicked, this, &SecondWindow::handleButton9);
    connect(ui.pushButton_12, &QPushButton::clicked, this, &SecondWindow::handleButton10);
    connect(ui.pushButton_13, &QPushButton::clicked, this, &SecondWindow::handleButton11);
    connect(ui.pushButton_7, &QPushButton::clicked, this, &SecondWindow::on_menuButton_clicked);
}

void SecondWindow::applyRoundedMask(QLabel* label, const QPixmap& originalPixmap)
{
    // Проверка на существование label
    if (!label) {
        qDebug() << "Label is null!";
        return;
    }

    int width = label->width();
    int height = label->height();
    int cornerRadius = 80;

    QPixmap scaledPixmap = originalPixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap roundedPixmap(width, height);
    roundedPixmap.fill(Qt::transparent);

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    int xOffset = (width - scaledPixmap.width()) / 2;
    int yOffset = (height - scaledPixmap.height()) / 2;

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


    label->setPixmap(roundedPixmap);;
    
    //label->setScaledContents(true);

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

    loadHeroFromJson(*hero, "resources/DefaultSave.json");
    printMenu(1, this->ui.label);
    makeAllButtonsInactive();
    ui.pushButton->setText("Осмотреться");
    activeButtonCSS(ui.pushButton);
    ui.label_3->setText(heroStatus(*hero));

}

QString SecondWindow::heroStatus(const Hero& hero) {
    using enum Element;
    const Character* characterPtr = &hero;

    QString status = QString("Имя: %1\n").arg(QString::fromStdString(hero.getName()));
    status += QString("%1\n").arg(QString::fromStdString(characterPtr->status()));
    status += QString("Сосредоточенность: %1\n").arg(hero.getFocus());
    status += "Мана:\n";
    status += QString("Огонь: %1\n").arg(hero.getMana(Fire));
    status += QString("Земля: %1\n").arg(hero.getMana(Earth));
    status += QString("Вода: %1\n").arg(hero.getMana(Water));
    status += QString("Воздух: %1\n").arg(hero.getMana(Air));
    status += QString("Дух: %1\n").arg(hero.getMana(Spirit));

    return status;
}

void SecondWindow::processActiveButton() {
    
    QString str;
    QString spellName;
    QString element1;
    QString element2;

    ui.label_3->setText(heroStatus(*hero));

    if (spellChoose) {
        hero->attack(*hero, *hero->getSpellBook().getSpells()[activeButton - 1]);
        hero->getSpellBook().getSpells()[activeButton - 1]->useSpell();
        spellChoose = false;
        makeAllButtonsInactive();
        ui.pushButton->setText("Отойти от стола");
        activeButtonCSS(ui.pushButton);
    }
    else {
        switch (activeButton) {
        case 1: {
            printMenu(2, this->ui.label);
            makeAllButtonsInactive();
            if (!isBookPickUp) {
                ui.pushButton_6->setText("Подобрать книгу");
                activeButtonCSS(ui.pushButton_6);
            }
            ui.pushButton_5->setText("Подойти к зеркалу");
            activeButtonCSS(ui.pushButton_5);
            break;
        }
        case 2: {
            printMenu(3, this->ui.label);
            makeAllButtonsInactive();
            ui.pushButton->setText("Отойти от стола");
            activeButtonCSS(ui.pushButton);
            isBookPickUp = true;
            break;
        }
        case 3: {
            if (isBookPickUp) {
                printMenu(5, this->ui.label);
                makeAllButtonsInactive();
                ui.pushButton_4->setText("Открыть книгу");
                activeButtonCSS(ui.pushButton_4);
            }
            else {
                printMenu(4, this->ui.label);
            }
            break;
        }
        case 4: {
            makeAllButtonsInactive();
            str = "<body style='line-height: 1.2;'> Вы открываете книгу заклинаний и видите перед собой следующие заклинания :";
            for (int i = 0; i < hero->getSpellBook().getSpellCount(); i++)
            {
                spellName = QString::fromStdString(hero->getSpellBook().getSpells()[i]->name);
                element1 = QString::fromStdString(elementToString(hero->getSpellBook().getSpells()[i]->element1));
                element2 = QString::fromStdString(elementToString(hero->getSpellBook().getSpells()[i]->element2));
                int damage = hero->getSpellBook().getSpells()[i]->damage;

                str += "<li style='line-height: 0.7;'>"
                    "<strong> </strong> <span style='color: #3498db;'>" + spellName + "</span> "
                    "<strong> : </strong>" + element1 + " "
                    "<strong> </strong>" + element2 + " "
                    "<strong>Урон: </strong>" + QString::number(damage) + " ед.<br>"
                    "</li>";
                switch (i) {
                    case 0: {
						ui.pushButton->setText("Использовать "+spellName);
                    break;
					}
					case 1: {
                        ui.pushButton_6->setText("Использовать " + spellName);
                        break;
					}
                    case 2: {
                        ui.pushButton_5->setText("Использовать " + spellName);
                        break;
                    }
                    case 3: {
                        ui.pushButton_4->setText("Использовать " + spellName);
                        break;
                    }
                    case 4: {
                        ui.pushButton_3->setText("Использовать " + spellName);
                        break;
                    }
                    case 5: {
                        ui.pushButton_2->setText("Использовать " + spellName);
                        break;
                    }
                    case 6: {
                        ui.pushButton_9->setText("Использовать " + spellName);
                        break;
                    }
                    case 7: {
                        ui.pushButton_10->setText("Использовать " + spellName);
                        break;
                    }
                    case 8: {
                        ui.pushButton_11->setText("Использовать " + spellName);
                        break;
                    }
                    case 9: {
                        ui.pushButton_12->setText("Использовать " + spellName);
                        break;
                    }
                    case 10: {
                        ui.pushButton_13->setText("Использовать " + spellName);
                        break;
                    }
                }
            }
            ui.label->setText(str);
            activeButtonCSS(ui.pushButton);
            activeButtonCSS(ui.pushButton_2);
            activeButtonCSS(ui.pushButton_3);
            activeButtonCSS(ui.pushButton_4);
            activeButtonCSS(ui.pushButton_5);
            activeButtonCSS(ui.pushButton_6);
            activeButtonCSS(ui.pushButton_9);
            activeButtonCSS(ui.pushButton_10);
            activeButtonCSS(ui.pushButton_11);
            activeButtonCSS(ui.pushButton_12);
            activeButtonCSS(ui.pushButton_13);
            spellChoose = true;
            break;
        }
        case 0: {

            cout << "Выход из программы" << endl;
            return;
        }
        default: {
            cout << "Выберите число от 0 до 4.\n";
        }
        }
    }
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
