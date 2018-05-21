#include "session.h"
#include <QTcpSocket>
#include <QHostAddress>

namespace monster {
Session::Session(TcpSocketPtr socket)
    : QObject(), m_size(), m_bytes(), m_package(), m_socket(socket) {

}

void Session::init() {
    connect(m_socket, SIGNAL(readyRead()),    this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
}

bool Session::connected() const {
    TcpSocketPtr socket = m_socket;
    if (socket) {
        return socket->isOpen();
    }
    return false;
}

bool Session::write(const QByteArray &msg) {
    TcpSocketPtr socket = m_socket;
    if (socket) {
        return socket->write(msg) == msg.size();
    }
    return false;
}

void Session::close() {
    TcpSocketPtr socket = m_socket;
    if (socket) {
        socket->close();
    }
}

QString Session::address() const {
    TcpSocketPtr socket = m_socket;
    if (socket) {
        return socket->localAddress().toString();
    }
    return QString();
}

void Session::onReadyRead() {
    qDebug("READY_READ");
    QByteArray bytes = m_socket->readAll();
    m_bytes.open(QIODevice::ReadWrite);
    m_bytes.write(bytes);
    m_bytes.seek(0);
    encode();
}

void Session::onDisconnected() {
    qDebug("DISCONNECTED");
}

qintptr Session::socketDescriptor() const {
    TcpSocketPtr socket = m_socket;
    if (socket) {
        return socket->socketDescriptor();
    }
    return -1;
}

const QTcpSocket* Session::socket() const {
    return m_socket;
}

void Session::encode() {
    if (m_bytes.bytesAvailable() == 0) return;
    if (m_size == 0) {
        m_bytes.read(reinterpret_cast<char*>(&m_size), sizeof(uint32_t));
    }
    qDebug() << m_size;
}

}
