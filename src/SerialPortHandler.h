#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPortHandler : public QObject {
  Q_OBJECT

  public:
    explicit SerialPortHandler(QObject *parent = nullptr);
    ~SerialPortHandler();

    void openSerialPort(const QString& portName, qint32 baudRate = QSerialPort::Baud115200);
    void closeSerialPort();
    QStringList availablePorts() const;
    void writeData(const QByteArray &data);

signals:
    void errorOccurred(const QString &error);
    void portOpened(bool success);

  private:
    QSerialPort *serialPort;
};

#endif // SERIALPORTHANDLER_H

