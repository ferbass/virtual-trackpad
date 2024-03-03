#include "SerialPortHandler.h"
#include <QDebug>

SerialPortHandler::SerialPortHandler(QObject *parent) : QObject(parent), serialPort(new QSerialPort(this)) {
  connect(serialPort, &QSerialPort::errorOccurred, [this](QSerialPort::SerialPortError error) {
      if (error == QSerialPort::NoError) return;
      emit errorOccurred(serialPort->errorString());
      });
}

SerialPortHandler::~SerialPortHandler() {
  closeSerialPort();
}

void SerialPortHandler::openSerialPort(const QString& portName, qint32 baudRate) {
  if (serialPort->isOpen()) closeSerialPort();

  serialPort->setPortName(portName);
  serialPort->setBaudRate(baudRate);
  bool success = serialPort->open(QIODevice::ReadWrite);
  emit portOpened(success);
  if (!success) {
    qDebug() << "Failed to open port" << portName << ": " << serialPort->errorString();
  }
}

void SerialPortHandler::closeSerialPort() {
  if (serialPort->isOpen()) serialPort->close();
}

QStringList SerialPortHandler::availablePorts() const {
  QStringList ports;
  const auto infos = QSerialPortInfo::availablePorts();
  for (const QSerialPortInfo &info : infos) {
    ports.append(info.portName());
  }
  return ports;
}

void SerialPortHandler::writeData(const QByteArray &data) {
  if (serialPort->isOpen()) {
    serialPort->write(data);
  }
}

