#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

class NumRepWindow : public QWidget {

private:
    QWidget *mainPanel;

    QLineEdit *decEdit;

    QLineEdit *hexEdit;

    QLineEdit *binEdit;

    QLineEdit *floatEdit;



public:
    explicit NumRepWindow() : mainPanel{nullptr}, decEdit{nullptr},
                              hexEdit{nullptr}, binEdit{nullptr},
                              floatEdit{nullptr} { }

    ~NumRepWindow() override {
        delete mainPanel;
    }

    void buildGui(QWidget *main_panel);

};

#endif
