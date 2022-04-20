#include <QApplication>
#include <QPushButton>



void make_gui(QWidget *window) {
    // QLabel hex_label = 
}



int main(int argc, char **argv) {
    QApplication app (argc, argv);

    QWidget window;
    window.resize(320, 420);

    make_gui(&window);

    window.show();
    return app.exec();
}
