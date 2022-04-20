#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>

class NumRepWindow : public QWidget {

private:
    QWidget *_window;

    QLabel *_test_label;

    QLineEdit *_test_edit;



public:
    explicit NumRepWindow() : _window{nullptr}, _test_label{nullptr},
    _test_edit{nullptr} { }

    ~NumRepWindow() override {
        delete _window;
    }

    void build_gui(QWidget *window);

};

#endif
