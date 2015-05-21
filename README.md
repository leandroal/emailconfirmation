# EmailConfirmation


The app automatically see your emails looking for Email Confirmations. After this the app will autmatically try to activate.


When you open the app you can see the Email Auto Confirmeds.
![alt tag](https://raw.githubusercontent.com/leandroal/emailconfirmation/master/EmailConfirmation/assets/images/IMG_20150502_201042.png)


In MessageHandler class you will see this : 

void MessageHandler::activateAccount(QVariantMap mailInformation){
/*
 * Put here your code to automatically activate the email
 *
 *  With the variable mailInformation you can get all information from your email confirmation (mailInformation.id,mailInformation.subject,mailInformation.body(MessageBody::PlainText).plainText())
 *
 *  With QNetworkAccessManager for example, you can do a POST to your web server and auto activate the account of the new user.
 *
 *
 */
}

The idea: When the BlackBerry 10 receive the email confirmation of your app you can put in these lines for example, a http request using QNetworkAccessManager to active the account of the user in your server).

You can set your own filter criteria, in this samples we use this email: automailconfirmationblackberry@gmail.com

 filter.addSearchCriteria(SearchFilterCriteria::FromAddress,
            "automailconfirmationblackberry@gmail.com");

You can test to send here: http://emailconfirmation-feetfit.rhcloud.com/




