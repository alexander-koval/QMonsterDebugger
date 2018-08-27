#include "session.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTime>
#include <QJsonDocument>
#include <QDomDocument>
#include "streaming/constants.h"
#include <sstream>
#include <string>

namespace monster {

class CommandProcessor {
public:
    void policyRequest(QByteArray* bytes) {
        char zero = 0x00;
        QDataStream streamXML(bytes, QIODevice::WriteOnly);
        QString crossdomain("<?xml version=\"1.0\"?>"
                            "<!DOCTYPE cross-domain-policy SYSTEM \"http://www.adobe.com/xml/dtds/cross-domain-policy.dtd\">"
                            "<cross-domain-policy xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.adobe.com/xml/schemas/PolicyFile.xsd\">"
                            "<site-control permitted-cross-domain-policies=\"master-only\"/>"
                            "<allow-access-from domain=\"*\" to-ports=\"*\" secure=\"false\"/>"
                            "<allow-http-request-headers-from domain=\"*\" headers=\"*\" secure=\"false\"/>"
                            "</cross-domain-policy>");
        (*bytes) = crossdomain.toUtf8();
        streamXML.writeRawData(bytes->data(), bytes->size());
        streamXML.writeRawData(&zero, 1);
    }

    void hello(QByteArray* bytes) {
        QByteArray bufferID;
        QByteArray bufferMsg;
        std::stringstream stream;
        stream << "{\"command\":\"" << COMMAND_HELLO << "\"}";
        std::string data = stream.str();

        QDataStream dataStream(bytes, QIODevice::WriteOnly);
        QByteArray id = QString(ID).toUtf8();
        QByteArray msg = QString(data.c_str()).toUtf8();

        QDataStream streamID(&bufferID, QIODevice::WriteOnly);
        QDataStream streamMsg(&bufferMsg, QIODevice::WriteOnly);
        streamID.writeRawData(QByteArray::number(id.size()), sizeof(uint16_t));
        streamID.writeBytes(id, id.size() + 2);
        streamMsg.writeRawData(QByteArray::number(msg.size()), sizeof(uint16_t));
        streamMsg.writeBytes(msg, msg.size() + 2);
//        streamID << QByteArray::number(static_cast<uint16_t>(id.size()));// << id;
//        streamMsg << QByteArray::number(static_cast<uint16_t>(msg.size()));// << msg;
//        streamID.writeRawData(QByteArray::number(id.size()), sizeof(uint16_t));
//        streamID.writeRawData(id, id.size());
//        streamMsg.writeRawData(QByteArray::number(msg.size()), sizeof(uint16_t));
//        streamMsg.writeRawData(msg, msg.size());

        dataStream << bufferID;
//        dataStream.writeRawData(QByteArray::number(streamID.size()),
//                                sizeof(uint16_t) + 2);
        dataStream << bufferMsg;
//        dataStream.writeRawData(QByteArray::number(msg.size()),
//                                sizeof(uint16_t) + 2);
//        qDebug() << "ID: " << bytesId << " SIZE:" << bytesId.size();
//        qDebug() << "DATA: " << bytesData << "SIZE: " << bytesData.size();

//        dataStream.writeRawData(QByteArray::number(bytesId.size()), sizeof(uint32_t));
//        dataStream.writeRawData(bytesId.data(), bytesId.size());
//        dataStream.writeRawData(QByteArray::number(bytesData.size()), sizeof(uint32_t));
//        dataStream.writeRawData(bytesData, bytesData.size());

//        dataStream.writeBytes(bytesId, static_cast<uint>(bytesId.size()));
//        dataStream.writeBytes(bytesData, static_cast<uint>(bytesId.size()));

//        dataStream << bytesId << bytesData;
    }
};

static CommandProcessor s_processor;

Session::Session(TcpSocketPtr socket)
    : QObject(), m_size(), m_bytes(), m_package(), m_socket(socket), m_blockSize() {

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
        QByteArray package;
        m_bytes.read(reinterpret_cast<char*>(&m_size), sizeof(uint32_t));
        QString command = m_bytes.buffer();
        if (command == "<policy-file-request/>") {
            QByteArray xml;
            s_processor.policyRequest(&xml);
            qDebug() << "LENGTH: " << xml.length();
            m_socket->write(xml);
            m_socket->flush();
        } else if (command == ID) {
            QByteArray bytes;
            s_processor.hello(&bytes);
            qDebug() << "BYTES: " << bytes;
            qDebug() << "LENGHT: " << bytes.size();
            QDataStream bytesStream(&package, QIODevice::WriteOnly);

            bytesStream << bytes;
            qDebug() << "PAC: " << package.size();
//            bytesStream.writeBytes(bytes, static_cast<uint>(bytes.size()));
            int result = write(package);
            qDebug() << "RESULT: " << result;
        }
        qDebug() << "COMMAND: " << command;
    }
    qDebug() << m_size;
}

}
