//
// Created by max on 24/05/22.
//

#ifndef NUMREPRESENTATION_DATAMODEL_H
#define NUMREPRESENTATION_DATAMODEL_H


#include <cstdint>
#include <iostream>

#include <QtCore>


class DataModel : public QObject {
Q_OBJECT



private:
    uint64_t _dataField;



public:
    DataModel() : _dataField{0} {};



public slots:
    void setModelData(uint64_t data) {
        _dataField = data;
        std::cout << "New _dataField value is: " << data <<std::endl;
    }

};


#endif //NUMREPRESENTATION_DATAMODEL_H
