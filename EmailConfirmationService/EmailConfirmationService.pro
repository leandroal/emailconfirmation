APP_NAME = EmailConfirmationService

CONFIG += qt warn_on

include(config.pri)

LIBS += -lbb -lbbsystem -lbbplatform

QT += core
LIBS += -lbbpim
QT += network
