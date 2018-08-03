#include "session.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTime>
#include <QJsonDocument>
#include "streaming/constants.h"
#include <sstream>

namespace monster {
Session::Session(TcpSocketPtr socket)
    : QObject(), m_size(), m_bytes(), m_package(), m_socket(socket), m_blockSize() {

}

void Session::init() {
    connect(m_socket, SIGNAL(readyRead()),    this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
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
    m_bytes.close();
}

void Session::onDisconnected() {
    qDebug("DISCONNECTED");
}

void Session::onSocketError(QAbstractSocket::SocketError error) {
    int kkk = 0;
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
        QString command = m_bytes.buffer();
        if (command == "<hello/>\n") {
            QByteArray item;
            QByteArray bytesId;
            QByteArray bytesData;

            QDataStream streamID(&bytesId, QIODevice::WriteOnly);
            streamID << QString(MONSTER_DEBUGGER_ID).toUtf8();
//            streamID.writeRawData(MONSTER_DEBUGGER_ID, strlen(MONSTER_DEBUGGER_ID));

            QDataStream streamData(&bytesData, QIODevice::WriteOnly);
            std::stringstream stream;
            stream << "{\"command\":\"" << COMMAND_HELLO << "\"}";
            std::string data = stream.str();
            streamData << QString(data.c_str()).toUtf8();
//            streamData.writeRawData(data.c_str(), data.size());

            QDataStream streamItem(&item, QIODevice::WriteOnly);
            qDebug() << "ID: " << bytesId;
            qDebug() << "DATA: " << bytesData;

//            streamItem.writeBytes(bytesId, sizeof(uint32_t));
//            streamItem.writeBytes(bytesData, sizeof(uint32_t));
            streamItem << bytesId << bytesData;
//            streamItem << (uint32_t)bytesId.size() << bytesId <<
//                    (uint32_t)bytesData.size() << bytesData;

            qDebug() << "ITEM: " << item;
            qDebug() << "ITEM: " << item.size();
            int result = write(item);
            qDebug() << "RESULT: " << result;
        }
        qDebug() << "COMMAND: " << command;
    }
    qDebug() << m_size;
}

}
