#include "session.h"
#include <QTcpSocket>
#include <QHostAddress>

Session::Session(QTcpSocket *socket) : m_socket(socket) {

}

bool Session::connected() const {
    return m_socket && m_socket->isOpen();
}

bool Session::write(const QByteArray &msg) {
    return m_socket->write(msg) == msg.size();
}

void Session::close() {
    m_socket->close();
}

std::string Session::getAddress() const {
    QString string = m_socket->localAddress().toString();
    return string.toUtf8().constData();
}

qintptr Session::getId() const {
    return m_socket->socketDescriptor();
}



