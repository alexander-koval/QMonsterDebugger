#include "session.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTime>
#include <QJsonDocument>
#include <QDomDocument>
#include "streaming/constants.h"
#include "streaming/MessagePack.h"
#include "streaming/CommandProcessor.h"
#include <sstream>
#include <string>
#include <QJsonObject>

namespace monster {

//class CommandProcessor {
//public:
//    void policyRequest(QByteArray* bytes) {
//        char zero = 0x00;
//        QDataStream streamXML(bytes, QIODevice::WriteOnly);
//        QString crossdomain("<?xml version=\"1.0\"?>"
//                            "<!DOCTYPE cross-domain-policy SYSTEM \"http://www.adobe.com/xml/dtds/cross-domain-policy.dtd\">"
//                            "<cross-domain-policy xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.adobe.com/xml/schemas/PolicyFile.xsd\">"
//                            "<site-control permitted-cross-domain-policies=\"master-only\"/>"
//                            "<allow-access-from domain=\"*\" to-ports=\"*\" secure=\"false\"/>"
//                            "<allow-http-request-headers-from domain=\"*\" headers=\"*\" secure=\"false\"/>"
//                            "</cross-domain-policy>");
//        (*bytes) = crossdomain.toUtf8();
//        streamXML.writeRawData(bytes->data(), bytes->size());
//        streamXML.writeRawData(&zero, 1);
//    }

//    void hello(QByteArray* bytes) {
//        std::stringstream stream;
//        stream << "{\"command\":\"" << COMMAND_HELLO << "\"}";
//        std::string data = stream.str();
//        QByteArray msg = QString(data.c_str()).toUtf8();
//        package(msg, *bytes);
//    }

//    void base(QByteArray* bytes) {
//        std::stringstream stream;
//        stream << "{\"command|\":\"" << COMMAND_BASE << "\"}";
//        std::string data = stream.str();
//        QByteArray msg = QString(data.c_str()).toUtf8();
//        package(msg, *bytes);
//    }

//    void package(QByteArray& msg, QByteArray& bytes) {
//        QByteArray bufferID;
//        QByteArray bufferMsg;
//        QByteArray id = QString(LOGGER_ID).toUtf8();
//        QDataStream dataStream(&bytes, QIODevice::WriteOnly);

//        QDataStream streamID(&bufferID, QIODevice::WriteOnly);
//        QDataStream streamMsg(&bufferMsg, QIODevice::WriteOnly);
//        streamID << static_cast<quint16>(id.size());
//        streamID.writeRawData(id, static_cast<uint16_t>(id.size()));
//        streamMsg << static_cast<quint16>(msg.size());
//        streamMsg.writeRawData(msg, static_cast<uint16_t>(msg.size()));
//        dataStream << bufferID << bufferMsg;
//    }
//};

Session::Session(TcpSocketPtr socket)
    : QObject(), m_size(), m_bytes(), m_package(), m_socket(socket),
      m_playerType(), m_playerVersion(), m_isDebugger(), m_isFlex(),
      m_fileTitle(), m_fileLocation() {

}

void Session::init() {
    connect(m_socket, SIGNAL(readyRead()),    this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
                SLOT(onSocketError(QAbstractSocket::SocketError)));
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
        bool result = socket->write(msg) == msg.size();
        socket->flush();
        return result;
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
    decode();
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

void Session::decode() {
    QByteArray package;
    if (m_bytes.bytesAvailable() == 0) return;
    if (m_size == 0) {
        QByteArray s = m_bytes.read(sizeof(uint32_t));
        QDataStream dataStream(&s, QIODevice::ReadOnly);
        dataStream >> m_size;
        package.clear();
    }
    if (package.size() < m_size && m_bytes.bytesAvailable() > 0) {
        qint64 l = m_bytes.bytesAvailable();
        if (l > m_size - package.size()) {
            l = m_size - package.size();
        }
        package = m_bytes.read(l);
    }
    if (m_size != 0 && package.size() == m_size) {
        MessagePack pack = MessagePack::read(package);
        if (!pack.getID().isEmpty() && pack.getID() == LOGGER_ID) {
            process(pack);
        }
        m_size = 0;
        package.clear();
    }

    if (m_size == 0 && m_bytes.bytesAvailable() > 0) {
        decode();
    }
    qDebug() << m_size;
}

void Session::process(MessagePack& pack) {

    QJsonObject item;
    const QJsonDocument& doc = pack.getData();
    QString strJson(doc.toJson(QJsonDocument::Compact));
    qDebug() << strJson;
    if (!doc.isNull()) {
        item = doc.object();
        if (item["command"] == COMMAND_INFO) {
            m_playerType = item["playerType"].toString();
            m_playerVersion = item["playerVersion"].toString();
            m_isDebugger = item["isDebugger"].toString();
            m_isFlex = item["isFlex"].toString();
            m_fileLocation = item["fileLocation"].toString();
            m_fileTitle = item["tileTitle"].toString();

            QByteArray bytes;
            QByteArray package;
            CommandProcessor::base(&bytes);
            QDataStream bytesStream(&package, QIODevice::WriteOnly);
            bytesStream << bytes;
            write(package);
        }
    }

}


}
