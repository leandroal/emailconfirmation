#include <src/Lista.hpp>

Lista* Lista::m_list = NULL;

Lista::Lista() : QObject()
{
    qRegisterMetaType<GroupDataModel *>("GroupDataModel *");
        m_model = new GroupDataModel();
        m_model->setSortedAscending(false);
        m_model->setGrouping(bb::cascades::ItemGrouping::None);
}

GroupDataModel * Lista::model() {   // Retorna a lista.
    emit emptyChanged();
    QSettings settings("EmailConfirmation","listItem");
//    settings.value("emailList").toList();

    m_model->clear();
    qDebug() << settings.value("emailList");


       if (settings.value("emailList").canConvert(QVariant::List)) {
           m_model->insertList(settings.value("emailList").toList());
       } else {
           if(!settings.value("emailList").toMap().isEmpty()){
           m_model->insert(settings.value("emailList").toMap());
           }
       }
    return m_model;
}

Lista::~Lista()
{
    // TODO Auto-generated destructor stub
}

void Lista::addList(QString Email, QString Description){
    QVariantMap map;
        map["Email"] = Email;
        map["Description"] = Description;
        m_model->insert(map);
        emit onModelChanged();
}

Lista* Lista::getInstance()
{
    if (m_list == NULL) {
        m_list = new Lista;
    }
    return m_list;
}

void Lista::modelChanged(){
    emit onModelChanged();
}

bool Lista::getEmpty(){
    return m_model->isEmpty();
}

