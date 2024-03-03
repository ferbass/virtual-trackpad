#ifndef TRACKPADWIDGET_H
#define TRACKPADWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QSlider>
#include <QPushButton>
#include "SerialPortHandler.h"
#include "TrackpadArea.h"

class TrackpadWidget : public QWidget {
  Q_OBJECT

  public:
    explicit TrackpadWidget(QWidget *parent = nullptr);

    private slots:
      void attemptOpenSerialPort();
    void handlePortOpened(bool success);
    void onMousePressed(const QPoint &pos);
    void onMouseReleased(const QPoint &pos);
    void onMouseMoved(const QPoint &pos);
    void onSensitivityChanged(int value);

  private:
    SerialPortHandler* serialPortHandler;
    QComboBox* portComboBox;
    QPushButton* openPortButton;
    TrackpadArea* trackpadArea;
    QSlider *sensitivitySlider;

    float sensitivity = 1.0;

    void setupUI();
    void setupTrackpadUI();
    void updateSensitivity(int value);
};

#endif // TRACKPADWIDGET_H

