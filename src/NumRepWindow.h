#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <QWidget>
#include <QFormLayout>

#include "data_modle/DataModel.h"
#include "edit_fields/DecEditor.h"
#include "edit_fields/HexEditor.h"
#include "edit_fields/FloatEdit.h"


class NumRepWindow : public QWidget {

private:
    DataModel *_dataModel;

    QWidget *_mainPanel;

    DecEditor *_decEdit;

    HexEditor *_hexEdit;

    FloatEdit *_floatEdit;


public:
    explicit NumRepWindow() : _mainPanel{nullptr}, _decEdit{nullptr},
                              _hexEdit{nullptr}, _floatEdit{nullptr} {
        _dataModel = new DataModel();
    }

    ~NumRepWindow() override {
        delete _mainPanel;
        delete _dataModel;
    }

    void buildGui(QWidget *main_panel);

};


#endif
