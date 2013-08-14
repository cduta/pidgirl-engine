#include "SendToServerEndTurn.h"

SendToServerEndTurn::SendToServerEndTurn(QObject *parent)
    : ClientCommand(parent)
{
    this->setObjectName("SendToServerNextTurn");
}

bool SendToServerEndTurn::execute()
{
    this->networkModel->sendData(FROM_CLIENT_NEXT_TURN);

    return true;
}
