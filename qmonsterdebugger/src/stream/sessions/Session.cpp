#include "Session.h"
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
#include "amf/types/amfnumber.hpp"
#include "amf/types/amfitem.hpp"
#include "amf/types/amfnull.hpp"
#include "amf/types/amfundefined.hpp"
#include "amf/types/amfvector.hpp"
#include "amf/types/amfxml.hpp"
#include "amf/types/amfxmldocument.hpp"
#include "amf/types/amfarray.hpp"

#include "utils/LoggerUtils.h"
#include "models/TraceModel.h"
#include "models/MonitorModel.h"
#include <QFile>

namespace monster {

Session::Session()
    : QObject(), m_size(), m_socket()
    , m_playerType(), m_playerVersion(), m_isDebugger(), m_isFlex()
    , m_fileTitle(), m_fileLocation()
    , m_traces(TraceModelPtr::create())
    , m_monitors(MonitorModelPtr::create()) {

}

Session::Session(TcpSocketPtr socket)
    : QObject(), m_size(), m_socket(socket)
    , m_playerType(), m_playerVersion(), m_isDebugger(), m_isFlex()
    , m_fileTitle(), m_fileLocation()
    , m_traces(TraceModelPtr::create())
    , m_monitors(MonitorModelPtr::create()) {

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
//    qDebug() << "READY READ " << m_socket->bytesAvailable();
    QBuffer buffer;
    if (m_size == 0) {
        m_socket->read(reinterpret_cast<char*>(&m_size),
                       sizeof(uint32_t));
        m_size = (((m_size & 0xFF) << 24) | ((m_size & 0xFF00) << 8) |
                  ((m_size & 0xFF0000) >> 8) | ((m_size & 0xFF000000) >> 24));
    }
    if (m_size < m_socket->bytesAvailable()) {
        decode(m_socket->read(m_size), static_cast<int32_t>(m_size));
        m_size = 0;
    }
    if (m_size == 0 && m_socket->bytesAvailable() > 0) {
        onReadyRead();
    }
}

void Session::onDisconnected() {
    qDebug("DISCONNECTED");
}

void Session::onSocketError(QAbstractSocket::SocketError error) {
    qWarning() << error;
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

QObject *Session::traces() const {
    return m_traces.data();
}

QObject *Session::monitors() const {
    return m_monitors.data();
}

void Session::decode(const QByteArray& bytes, int32_t size) {
    QByteArray package;
    if (bytes.size() == 0 || size == 0) return;
    if (package.size() < size && bytes.size() > 0) {
        int l = bytes.size();
        if (l > size - package.size()) {
            l = size - package.size();
        }
        package = QByteArray(bytes.begin(), l);
    }
    qDebug() << size << " " << package.size() << " " << bytes.size();
    if (size != 0 && package.size() == size) {
        MessagePack pack = MessagePack::read(package);
        const std::string& id = pack.getID().as<amf::AmfString>().value;
        if (!id.empty() && id == LOGGER_ID) {
            process(pack);
        }
    }
}

void Session::process(MessagePack& pack) {
    amf::AmfObject& item = pack.getData().as<amf::AmfObject>();
    const amf::AmfString& cmd = item.getDynamicProperty<amf::AmfString>("command");
    emit inboundMessage(pack);
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
        emit initialized();
    } else if (cmd.value == COMMAND_TRACE) {
        int col = 0;
        int row = m_traces->rowCount();
        QDomDocument doc;
        m_traces->insertRow(row);
        long long time = item.getDynamicProperty<amf::AmfDate>("date").value;
        double mem = item.getDynamicProperty<amf::AmfNumber>("memory").operator double();
        QString memory = QString::number(mem / 1024) + "kb";
        QString target = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("target").value);
#if defined (Q_OS_WIN)
//        QString message = QString::fromStdString(item.getDynamicProperty<amf::AmfXml>("xml").value);
#else
        QString message = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("xml").value);
#endif
        message.remove(QRegExp("[\\n\\t\\r]"));
        doc.setContent(message);
        const QDomNode& root = doc.documentElement().firstChild();
        int nodes_size = root.childNodes().count();
        const QDomNamedNodeMap& map = doc.firstChild().attributes();
        if (nodes_size > 1 && nodes_size <= 3) {
            if (map.namedItem("type").nodeValue() == "String") {
                QString value = root.firstChild().firstChild()
                        .attributes().namedItem("value").nodeValue();
                message = logutils::stripBreaks(logutils::htmlUnescape(value));
            } else {
                const QDomNode& label = root.firstChild().attributes().namedItem("value");
                QString value = label.nodeValue();
                message = logutils::stripBreaks(logutils::htmlUnescape(value));
            }
        } else {
            const QDomNode& label = root.firstChild().attributes().namedItem("value");
            QString value = label.nodeValue();
            message = logutils::stripBreaks(logutils::htmlUnescape(value));
        }
        m_traces->setData(m_traces->index(row, col), row + 1, TraceItem::Line);
        m_traces->setData(m_traces->index(row, ++col), time, TraceItem::Time);
        m_traces->setData(m_traces->index(row, ++col), memory, TraceItem::Memory);
        m_traces->setData(m_traces->index(row, ++col), target, TraceItem::Target);
        m_traces->setData(m_traces->index(row, ++col), message, TraceItem::Message);
    } else if (cmd.value == COMMAND_MONITOR) {
        int col = 0;
        int row = m_monitors->rowCount();
        qlonglong memory = static_cast<qlonglong>(
                    item.getDynamicProperty<amf::AmfNumber>("memory").operator double());
        qint32 fps = item.getDynamicProperty<amf::AmfNumber>("fps").operator int();
        qint32 fpsMovie = 0;
        std::map<std::string, amf::AmfItemPtr>::iterator it = item.dynamicProperties.find("fpsMovie");
        if (it != item.dynamicProperties.end()) {
            fpsMovie = it->second.as<amf::AmfNumber>().operator int();
        }
        m_monitors->insertRow(row);
        m_monitors->setData(m_monitors->index(row, col), memory, MonitorItem::MEMORY);
        m_monitors->setData(m_monitors->index(row, ++col), fps, MonitorItem::FPS);
        m_monitors->setData(m_monitors->index(row, ++col), fpsMovie, MonitorItem::FPS_MOVIE);
    }
//    if (cmd.value != COMMAND_INFO) {
//        emit inboundMessage(pack);
//    } else {
//        m_playerType = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("playerType").value);
//        m_playerVersion = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("playerVersion").value);
//        m_isDebugger = item.getDynamicProperty<amf::AmfBool>("isDebugger").value;
//        m_isFlex = item.getDynamicProperty<amf::AmfBool>("isFlex").value;
//        m_fileLocation = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("fileLocation").value);;
//        m_fileTitle = QString::fromStdString(item.getDynamicProperty<amf::AmfString>("fileTitle").value);;

//        QByteArray bytes;
//        QByteArray package;
//        CommandProcessor::base(&bytes);
//        QDataStream bytesStream(&package, QIODevice::WriteOnly);
//        bytesStream << bytes;
//        write(package);

//        emit initialized();
//    }
}


}
