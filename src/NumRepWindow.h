#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <QWidget>
#include <QFormLayout>

#include "data_modle/DataModel.h"
#include "edit_fields/DecEditor.h"
#include "edit_fields/HexEditor.h"


class NumRepWindow : public QWidget {

private:
    DataModel *_dataModel;

    QWidget *mainPanel;

    DecEditor *decEdit;

    HexEditor *hexEdit;


public:
    explicit NumRepWindow() : mainPanel{nullptr}, decEdit{nullptr},
                              hexEdit{nullptr} {
        _dataModel = new DataModel();
    }

    ~NumRepWindow() override {
        delete mainPanel;
        delete _dataModel;
    }

    void buildGui(QWidget *main_panel);

};


#endif
