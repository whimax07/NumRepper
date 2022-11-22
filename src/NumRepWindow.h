#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <QWidget>
#include <QFormLayout>

#include "binary_rep/BitButtons.h"
#include "data_modle/DataModel.h"
#include "edit_fields/EditFields.h"
#include "edit_fields/GenericEditField.h"



class NumRepWindow : public QWidget {

private:
    DataModel *_dataModel = new DataModel();

    QWidget *_mainPanel;

    GenericEditField *_sDecEdit;

    GenericEditField *_uDecEdit;

    GenericEditField *_hexEdit;

    GenericEditField *_binEdit;

    GenericEditField *_floatEdit;

    BitButtons *_bitButtons;


public:
    explicit NumRepWindow() :
            _mainPanel{nullptr}, _sDecEdit{nullptr}, _uDecEdit{nullptr},
            _hexEdit{nullptr}, _binEdit{nullptr}, _floatEdit{nullptr},
            _bitButtons{nullptr} {
    }

    ~NumRepWindow() override {
        delete _mainPanel;
        delete _dataModel;
    }

    void buildGui(QWidget *main_panel);

};


#endif
