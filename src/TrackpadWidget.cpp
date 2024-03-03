#include "TrackpadWidget.h"
#include <QVBoxLayout>
#include <QDebug>

TrackpadWidget::TrackpadWidget(QWidget *parent) : QWidget(parent), serialPortHandler(new SerialPortHandler(this)) {
  setupUI();
}

void TrackpadWidget::setupUI() {
  auto layout = new QVBoxLayout(this);
  portComboBox = new QComboBox(this);
  openPortButton = new QPushButton("Open Port", this);

  portComboBox->addItems(serialPortHandler->availablePorts());
  layout->addWidget(portComboBox);
  layout->addWidget(openPortButton);

  connect(openPortButton, &QPushButton::clicked, this, &TrackpadWidget::attemptOpenSerialPort);
  connect(serialPortHandler, &SerialPortHandler::portOpened, this, &TrackpadWidget::handlePortOpened);
}

void TrackpadWidget::attemptOpenSerialPort() {
  QString selectedPortName = portComboBox->currentText();
  serialPortHandler->openSerialPort(selectedPortName);
}

void TrackpadWidget::handlePortOpened(bool success) {
  if (success) {
    qDebug() << "Serial port opened successfully.";
    setupTrackpadUI();
  } else {
    qDebug() << "Failed to open serial port.";
  }
}

void TrackpadWidget::setupTrackpadUI() {
  trackpadArea = new TrackpadArea(this);
  // TODO resize according to the window size
  trackpadArea->setFixedSize(400, 400);
  trackpadArea->setStyleSheet("QLabel { background-color: lightgrey; }");
  layout()->addWidget(trackpadArea);

  QLabel *label = new QLabel("Sensitivity", this);
  label->setAlignment(Qt::AlignLeft);
  label->setFixedSize(400, 20);
  layout()->addWidget(label);

  sensitivitySlider = new QSlider(Qt::Horizontal, this);
  sensitivitySlider->setFixedSize(400, 40);
  sensitivitySlider->setRange(1, 10);
  sensitivitySlider->setValue(1);
  layout()->addWidget(sensitivitySlider);

  connect(sensitivitySlider, &QSlider::valueChanged, this, &TrackpadWidget::onSensitivityChanged);
  connect(trackpadArea, &TrackpadArea::mousePressed, this, &TrackpadWidget::onMousePressed);
  connect(trackpadArea, &TrackpadArea::mouseReleased, this, &TrackpadWidget::onMouseReleased);
  connect(trackpadArea, &TrackpadArea::mouseMoved, this, &TrackpadWidget::onMouseMoved);
}

void TrackpadWidget::onSensitivityChanged(int value) {
  trackpadArea->onSensitivityChanged(value);
}

void TrackpadWidget::onMousePressed(const QPoint &pos) {
  QString message = QString("CLK %1,%2\n").arg(pos.x()).arg(pos.y());
  serialPortHandler->writeData(message.toLocal8Bit());
}

void TrackpadWidget::onMouseReleased(const QPoint &pos) {
  QString message = QString("CLKR %1,%2\n").arg(pos.x()).arg(pos.y());
  serialPortHandler->writeData(message.toLocal8Bit());
}

void TrackpadWidget::onMouseMoved(const QPoint &pos) {
  QString message = QString("MOV %1,%2\n").arg(pos.x()).arg(pos.y());
  serialPortHandler->writeData(message.toLocal8Bit());
}
