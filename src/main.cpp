#include <QApplication>
#include <QPushButton>

#include "NumRepWindow.h"



int main(int argc, char **argv) {
    QApplication app (argc, argv);

    QWidget window;
    window.resize(320, 420);

    auto *window_maker = new NumRepWindow();
    window_maker->buildGui(&window);

    window.show();
    return app.exec();
}
