#include <QApplication>
#include <QPushButton>

#include "NumRepWindow.h"


int main(int argc, char **argv) {
    QApplication  app (argc, argv);

    QWidget window;
//    window.resize(320, 420);
    window.resize(0, 0);

    auto *numRepWindow = new NumRepWindow();
    numRepWindow->buildGui(&window);

    window.show();
    return QApplication::exec();
}
