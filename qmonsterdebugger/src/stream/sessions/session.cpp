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
        const std::string& id = pack.getID().as<amf::AmfString>().value;
        if (!id.empty() && id == LOGGER_ID) {
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
    amf::AmfObject& item = pack.getData().as<amf::AmfObject>();
    const amf::AmfString& cmd = item.getDynamicProperty<amf::AmfString>("command");
    if (cmd.value == COMMAND_INFO) {
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
    }
}


}
