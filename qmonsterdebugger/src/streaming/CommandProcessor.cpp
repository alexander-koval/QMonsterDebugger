#include "CommandProcessor.h"
#include <string>
#include <sstream>
#include <QBuffer>
#include <QDataStream>
#include <QJsonDocument>
#include <QDomDocument>
#include "streaming/constants.h"
#include <iostream>

namespace monster {

void CommandProcessor::policyRequest(QByteArray* bytes) {
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

void CommandProcessor::hello(QByteArray* bytes) {
    std::stringstream stream;
    stream << "{\"command\":\"" << COMMAND_HELLO << "\"}";
    std::string data = stream.str();
    QByteArray msg = QString(data.c_str()).toUtf8();
    encode(msg, *bytes);
}

void CommandProcessor::encode(QByteArray& msg, QByteArray& bytes) {
    QByteArray bufferID;
    QByteArray bufferMsg;
    QByteArray id = QString(LOGGER_ID).toUtf8();
    QDataStream dataStream(&bytes, QIODevice::WriteOnly);

    QDataStream streamID(&bufferID, QIODevice::WriteOnly);
    QDataStream streamMsg(&bufferMsg, QIODevice::WriteOnly);
    streamID << static_cast<quint16>(id.size());
    streamID.writeRawData(id, static_cast<uint16_t>(id.size()));
    streamMsg << static_cast<quint16>(msg.size());
    streamMsg.writeRawData(msg, static_cast<uint16_t>(msg.size()));
    dataStream << bufferID << bufferMsg;
}

void CommandProcessor::decode(QString& id, QJsonDocument& data,
                              QByteArray &bytes) {
    QDataStream buffer(&bytes, QIODevice::ReadOnly);
    quint32 packSize;
    quint16 dataSize;

    buffer >> packSize;
    buffer >> dataSize;
    char* bufID = new char[dataSize];
    buffer.readRawData(bufID, dataSize);
    id = QString::fromUtf8(bufID);
    id.truncate(dataSize);

    buffer >> packSize;
    buffer >> dataSize;
    char* bufMsg = new char[dataSize];
    buffer.readRawData(bufMsg, dataSize);
    data = QJsonDocument::fromJson(
                QByteArray::fromRawData(bufMsg, dataSize));

    delete[] bufID;
    delete[] bufMsg;
}


}
