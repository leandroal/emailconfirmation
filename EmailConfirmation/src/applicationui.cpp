/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/DropDown>
#include <bb/cascades/Option>
#include <bb/cascades/WebView>
#include <QFile>
#include <QTextStream>
#include <QNetworkReply>
#include "Lista.hpp"
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>

using namespace bb::cascades;
QSettings settings("EmailConfirmation","listItem");

ApplicationUI::ApplicationUI() :
        QObject()
{
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    Q_ASSERT(res);
    Q_UNUSED(res);
    onSystemLanguageChanged();
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);
    qml->setContextProperty("_appUI", this);
    qml->setContextProperty("_list",Lista::getInstance());
    settingsWatcherInfo.addPath(settings.fileName());

    if(!(settings.contains("emailList"))){
        qDebug() << "emailList settings doesn't exist. Creating...";
        settings.setValue("emailList", "-1"); // If doesn't exist, creates an empty variant
        settings.sync();
    }

    bb::system::InvokeRequest request;
    request.setTarget("com.example.EmailConfirmationService");
    request.setAction("teste");
    m_invokeManager.invoke(request);

    settingsWatcherInfo.addPath(settings.fileName());

    connect(&settingsWatcherInfo,SIGNAL(fileChanged(QString)),this,SLOT(onItemListAdded()));
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);

    QString locale_string = QLocale().name();
    QString file_name = QString("teste_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::replyFinished(QNetworkReply* m_reply)
{

    if (m_reply->error()) {
        qDebug() << "ERROR!";
        qDebug() << m_reply->errorString();
        if (m_reply->isRunning()) {
            qDebug() << "Redirecionando..";
        }
        qDebug() << m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    } else {
        if (m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 302) {
            qDebug() << "302";
            QUrl replyRedirect =
                    m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
            manager->get(QNetworkRequest(replyRedirect));
        }
    }
    m_reply->deleteLater();

}

void ApplicationUI::onLoadChanged(bb::cascades::WebLoadRequest* reply){
    reply->deleteLater();
}

void ApplicationUI::onItemListAdded(){
  // qDebug() << settings.value("emailList").toList();
    Lista::getInstance()->modelChanged();
}
void ApplicationUI::addElementsDropDown(QObject* element){
    DropDown* dropDown = qobject_cast<DropDown*>(element);


   QStringList listAccounts =  settings.value("accounts").toStringList();
   for(int i = 0; i < listAccounts.size(); i++){
       dropDown->add(Option::create().text(listAccounts.at(i)));
   }
}

