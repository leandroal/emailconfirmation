/*
 * Lista.hpp
 *
 *  Created on: 27/02/2015
 *      Author: Felipe
 */

#ifndef LISTA_HPP_
#define LISTA_HPP_

#include <QObject>
#include <bb/cascades/GroupDataModel>

using namespace bb::cascades;

class Lista : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GroupDataModel * model READ model NOTIFY onModelChanged);
    Q_PROPERTY(bool isEmpty READ getEmpty NOTIFY emptyChanged);
public:
    Q_INVOKABLE
        GroupDataModel * model();
    Q_INVOKABLE
        bool getEmpty();


    virtual ~Lista();

    Q_INVOKABLE void addList(QString Email, QString Description );
    void modelChanged();

    static Lista * getInstance();
private:
    Lista();
GroupDataModel * m_model;
static Lista * m_list;
signals:
void emptyChanged();
void onModelChanged();

};


#endif /* LISTA_HPP_ */
