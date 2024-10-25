#include "header/functions.h"
#include "header/Hero.h"
#include "header/MainWindow.h"
#include <QWidget>
#include <QApplication>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    QApplication a(argc, argv);
    

    MainWindow w;
    w.setStyleSheet(
        "QMainWindow {"
        " background-color: #262626;"
        "border: 2px solid #00ccff;"
        "border - radius: 10px;"
        "width: 500px;"
        "padding: 20px;"
        "box - shadow: 0 4px 10px rgba(0, 0, 0, 0.5);"
        "}"
    );
    w.show();

    return a.exec();
}
