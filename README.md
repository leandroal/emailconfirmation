# Email Confirmation Sample

The purpose of this sample application is to simulate an automatic confirmation of a user account when a user signs up in a given online service.

Motivation: it is boring to the users when they sign up to an online service and they have to click on a web link available inside an e-mail message received in their inboxes just to confirm that they have typed an valid e-mail address while filling out the form. What about if users fill the sign up fields of the form, submit their data to a server and the application automatically keeps tracking of the confirmation e-mail? This is what we want with this sample.

When the e-mail confirmation is received in a user e-mail inbox, the application grabs the confirmation URL and automatically confirms the user account without any user interaction. In this example, such scenario is simulated as following.

When the user opens the app, (s)he can see the account status. If there no account, the sample application will show the message "Click in the add account button to simulate a new account with automatic e-mail conformation.", as shown below.

![](http://i.imgur.com/gMKhc32.png)

As suggested, to simulate a new user sign up, just click on the add account button and fill out the following form:

![](http://i.imgur.com/GZOOtk9.png)
![](http://i.imgur.com/URzWq3u.png)

After that, the application will monitor incoming e-mail messages and, when the proper confirmation message arrives in the user e-mail inbox, it automatically confirms the account by sending an HTTP request to the corresponding web link. If a proper response is returned, the status will be updated to "Account confirmed", as depicted below.

![](http://i.imgur.com/Isaa8ku.png)

Diving into the source code
---------------------------

The application is split in two parts: a headless service and a UI application that shows information to the user.

The UI basically just sends a POST request to the server with the informations needed (email and name -- for simplicity, the password is just ignored):

```cpp
void NetworkManager::submit(QString name, QString email, QString password) {
    bool connected = connect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(connected);
    QNetworkRequest request(ACCOUNT_URL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrl parameters;
    parameters.addQueryItem("name", name);
    parameters.addQueryItem("email", email);
    m_netManager.post(request, parameters.encodedQuery());
}
```

The server is supposed to return a confirmation message that the email was sent, so it checks for that:

```cpp
void NetworkManager::onFinished(QNetworkReply* reply) {
    using namespace bb::data;
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    if (reply->error() == QNetworkReply::NoError) {
        JsonDataAccess json;
        QString contentString = reply->readAll();
        qDebug() << "POST reply:" << contentString;
        QVariantMap content = json.loadFromBuffer(contentString).toMap();
        bool ok;
        int replyCode = content["id"].toInt(&ok);
        if (!ok) replyCode = -1;
        if (replyCode == 0) {
            emit emailSent();
        }
    }
    reply->deleteLater();
}
```

After that, the service will catch any incoming messages and check for the sender address. When the right email comes, it will trigger a notification and try to confirm:

```cpp
void MessageHandler::onBodyDownloaded(bb::pim::account::AccountKey accountId, bb::pim::message::MessageKey messageKey)
{
    if (!m_currentAccount.isValid()) {
        return;
    }
    Message msg = m_messageService->message(accountId, messageKey);
    if (msg.isInbound()) {
        if (msg.sender().address() == DEFAULT_EMAIL) {
            QString emailContent = msg.body(MessageBody::PlainText).plainText();
            if (emailContent.isEmpty()) {
                emailContent = msg.body(MessageBody::Html).plainText();
            }
            m_notification.setBody("A new confirmation email just arrived");
            m_notification.notify();

            confirmAccount(emailContent);
        }
    }
}
```

The confirmAccount function parses the URL in the email body and tries to request it. If the result has the right message, it means the email was confirmed.

```cpp
void NetworkManager::onFinished(QNetworkReply* reply) {
    using namespace bb::data;
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    if (reply->error() == QNetworkReply::NoError) {
        JsonDataAccess json;
        QString contentString = reply->readAll();
        QVariantMap content = json.loadFromBuffer(contentString).toMap();
        bool ok;
        int replyCode = content["id"].toInt(&ok);
        if (!ok) replyCode = -1;
        emit confirmationCode(replyCode);
    }
    reply->deleteLater();
```

Applies to
----------

[BlackBerry Native SDK](http://developer.blackberry.com/native/)

Authors
-------

* [Dielson Sales](https://github.com/dielsonsales)
* [Leandro Sales](https://github.com/leandroal)
* [Durval Pereira](https://github.com/DurvalPCN)

Dependencies
------------

1. Minimal requrement BlackBerry 10 Device Software **10.3**
2. Minimal requrement BlackBerry 10 Native SDK **10.3**

How to build EmailConfirmation
------------------------------

Simply Import the project into a workspace in Momentics IDE.

But I don't want to build it myself!
------------------------------------

If you don't want to build this sample application yourself we've included a pre-built and signed BAR file. You can find it in the folder "installable-bar-files" as follows:

* **AudioAccessory-1_0_0_2.bar** - Signed BAR file for Version 1.0 (V1.0) of the application (minimal requirement BlackBerry 10 Software 10.3)

Known issues
------------

* **None**

Disclaimer
----------

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
