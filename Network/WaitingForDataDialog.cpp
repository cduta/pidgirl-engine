#include "WaitingForDataDialog.h"

WaitingForDataDialog::WaitingForDataDialog(NetworkModel *networkModel, QObject *parent)
    : QObject(parent),
      messageBox(QMessageBox::Information,
                 tr("Receving data from Server..."),
                 tr("Waiting for data from the server...\nPress cancel to stop waiting..."),
                 QMessageBox::Cancel)
{
    this->networkModel = networkModel;
    this->messageBox.setModal(true);
    this->messageBox.setCursor(Qt::BusyCursor);
}

WaitingForDataDialog::WaitingForDataDialog(NetworkModel *networkModel, const QString &title, const QString &text, QObject *parent)
    : QObject(parent),
      messageBox(QMessageBox::Information,
                 title,
                 text,
                 QMessageBox::Cancel)
{
    this->networkModel = networkModel;
    this->messageBox.setModal(true);
    this->messageBox.setCursor(Qt::BusyCursor);
}

bool WaitingForDataDialog::waitFor(FromClient fromClient)
{
    if(!this->networkModel || this->networkModel->isClient())
    {
        return false;
    }

    this->fromClient = fromClient;
    this->hasBeenReceived = false;

    connect(networkModel, SIGNAL(allDataReceived(FromClient)), this, SLOT(dataReceived(FromClient)));

    this->messageBox.exec();

    if(!this->hasBeenReceived)
    {
        qDebug("Canceled the waiting dialog.");
    }

    return this->hasBeenReceived;
}

bool WaitingForDataDialog::waitFor(FromServer fromServer)
{
    if(!this->networkModel || this->networkModel->isServer())
    {
        return false;
    }

    this->fromServer = fromServer;
    this->hasBeenReceived = false;

    connect(networkModel, SIGNAL(allDataReceivedFromServer(FromServer)), this, SLOT(dataReceived(FromServer)));

    this->messageBox.exec();

    if(!this->hasBeenReceived)
    {
        qDebug("Canceled the waiting dialog.");
    }

    return this->hasBeenReceived;
}


void WaitingForDataDialog::dataReceived(FromClient fromClient)
{
    this->hasBeenReceived = this->fromClient == fromClient;

    if(this->hasBeenReceived)
    {
        this->messageBox.accept();
    }

    return;
}

void WaitingForDataDialog::dataReceived(FromServer fromServer)
{
    this->hasBeenReceived = this->fromServer == fromServer;

    if(this->hasBeenReceived)
    {
        this->messageBox.accept();
    }

    return;
}

