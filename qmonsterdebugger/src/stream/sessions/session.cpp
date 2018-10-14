#include "session.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTime>
#include <QJsonDocument>
#include <QDomDocument>
#include "stream/constants.h"
#include "stream/MessagePack.h"
#include "stream/CommandProcessor.h"
#include <sstream>
#include <string>
#include <QJsonObject>
#include "amf/amf.hpp"
#include "amf/types/amfobject.hpp"
#include "amf/types/amfstring.hpp"
#include "amf/types/amfbool.hpp"
#include "amf/types/amfbytearray.hpp"
#include "amf/types/amfdate.hpp"
#include "amf/types/amfdictionary.hpp"
#include "amf/types/amfdouble.hpp"
#include "amf/types/amfinteger.hpp"
#include "amf/types/amfitem.hpp"
#include "amf/types/amfnull.hpp"
#include "amf/types/amfundefined.hpp"
#include "amf/types/amfvector.hpp"
#include "amf/types/amfxml.hpp"
#include "amf/types/amfxmldocument.hpp"
#include "amf/types/amfarray.hpp"

namespace monster {

Session::Session()
    : QObject(), m_socket(),
      m_playerType(), m_playerVersion(), m_isDebugger(), m_isFlex(),
      m_fileTitle(), m_fileLocation() {

}

Session::Session(TcpSocketPtr socket)
    : QObject(), m_socket(socket),
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
    qDebug() << "READY READ ";
    QBuffer buffer;
    QByteArray bytes = m_socket->readAll();
    qDebug() << "BUFFER: " << bytes.size();
    buffer.open(QIODevice::ReadWrite);
    buffer.write(bytes);
    buffer.seek(0);
    decode(buffer, 0);
    buffer.close();
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

void Session::socket(TcpSocketPtr socket) {
    if (socket) {
        m_socket = socket;
    }
}

void Session::decode(QBuffer& bytes, int32_t size) {
    QByteArray package;
    if (bytes.bytesAvailable() == 0) return;
    if (size == 0) {
        QByteArray s = bytes.read(sizeof(uint32_t));
        QDataStream dataStream(&s, QIODevice::ReadOnly);
        dataStream >> size;
        package.clear();
    }

    if (package.size() < size && bytes.bytesAvailable() > 0) {
        qint64 l = bytes.bytesAvailable();
        if (l > size - package.size()) {
            l = size - package.size();
        }
        package = bytes.read(l);
    }
    if (size != 0 && package.size() == size) {
        MessagePack pack = MessagePack::read(package);
        const std::string& id = pack.getID().as<amf::AmfString>().value;
        if (!id.empty() && id == LOGGER_ID) {
            process(pack);
        }
        size = 0;
        package.clear();
    }

    if (size == 0 && bytes.bytesAvailable() > 0) {
        decode(bytes, size);
    }
    qDebug() << size << " " << package.size();
}

void Session::process(MessagePack& pack) {
    amf::AmfObject& item = pack.getData().as<amf::AmfObject>();
    const amf::AmfString& cmd = item.getDynamicProperty<amf::AmfString>("command");
    if (cmd.value != COMMAND_INFO) {
        emit inboundMessage(pack);
    } else {
        m_playerType = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("playerType").value);
        m_playerVersion = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("playerVersion").value);
        m_isDebugger = item.getDynamicProperty<amf::AmfBool>("isDebugger").value;
        m_isFlex = item.getDynamicProperty<amf::AmfBool>("isFlex").value;
        m_fileLocation = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("fileLocation").value);;
        m_fileTitle = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("fileTitle").value);;

        QByteArray bytes;
        QByteArray package;
        CommandProcessor::base(&bytes);
        QDataStream bytesStream(&package, QIODevice::WriteOnly);
        bytesStream << bytes;
        write(package);

        emit initialized();
    }
}


}
