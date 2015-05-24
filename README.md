# EmailConfirmation

The purpose of this aplplication is to sumulate a sign-up confirmation. You can fill a simple form, submit to a server and then listen to a specific email with a confirmation link. When received, the application will automatically try to confirm and if everything goes right, update the account status to confirmed.

When you open the app you can see the account status. If no account has been added, it will show the message "No account"

![](http://i.imgur.com/gMKhc32.png)

You can simulate a registration by entering some data in the forms:

![](http://i.imgur.com/GZOOtk9.png)
![](http://i.imgur.com/URzWq3u.png)

After that, the application will monitor for incoming messages and, when the right message arrives, it will automatically confirm request the link in the message. If a proper response is returned, the status will be updated to "Account confirmed".

![](http://i.imgur.com/Isaa8ku.png)

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

* **AudioAccessory-1_0_0_1.bar** - Signed BAR file for Version 1.0 (V1.0) of the application (minimal requirement BlackBerry 10 Software 10.3)

Known issues
------------

* **None**

Disclaimer
----------

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
