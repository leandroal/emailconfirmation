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
    virtual ~Lista();
    Q_INVOKABLE GroupDataModel * model();
    Q_INVOKABLE bool getEmpty();
    Q_INVOKABLE void addList(QString Email, QString Description );
    void modelChanged();
    static Lista * getInstance();
signals:
    void emptyChanged();
    void onModelChanged();
private:
    Lista();
    GroupDataModel * m_model;
    static Lista * m_list;
};


#endif /* LISTA_HPP_ */
