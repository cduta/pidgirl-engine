#ifndef WAITING_FOR_DATA_DIALOG_H
#define WAITING_FOR_DATA_DIALOG_H

#include <QObject>
#include <QMessageBox>

#include "Network/NetworkModel.h"

class WaitingForDataDialog : public QObject
{
    Q_OBJECT

    NetworkModel *  networkModel;

    FromClient      fromClient;         ///< Wait for a specific fromClient enum from the Client.
    FromServer      fromServer;         ///< Wait for a specific fromServer enum from the Server.

    QMessageBox     messageBox;         ///< The message box informing about what to wait for and giving the possibility to cancel the wait.
    bool            hasBeenReceived;    ///< True, if the waited for enum was received.

public:
    WaitingForDataDialog(NetworkModel *networkModel, QObject *parent = 0);
    WaitingForDataDialog(NetworkModel *networkModel, const QString &title, const QString &text, QObject *parent = 0);

    /**
      * @brief Wait for a given fromClient enum to be received.
      * @param fromClient The fromClient enum to be received.
      * @return True, if the waited for fromClient enum was received. Otherwise, false.
      */
    bool waitFor(FromClient fromClient);

    /**
      * @brief Wait for a given fromServer enum to be received.
      * @param fromServer The fromServer enum to be received.
      * @return True, if the waited for fromServer enum was received. Otherwise, false.
      */
    bool waitFor(FromServer fromServer);

private slots:
    void dataReceived(FromClient fromClient);
    void dataReceived(FromServer fromServer);
};

#endif // WAITING_FOR_REPLY_DIALOG_H
