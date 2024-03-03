#include "TrackpadArea.h"

TrackpadArea::TrackpadArea(QWidget *parent) : QLabel(parent) {
  setMouseTracking(true);
  this->setStyleSheet("background-color: lightgrey;");
}

void TrackpadArea::mousePressEvent(QMouseEvent *event) {
  qDebug() << "Mouse Pressed at:" << event->pos();
  if (event->buttons() & Qt::RightButton) { return; }
  emit mousePressed(event->pos());
}

void TrackpadArea::mouseReleaseEvent(QMouseEvent *event) {
  qDebug() << "Mouse Pressed at:" << event->pos();
  if (event->buttons() & Qt::RightButton) { return; }
  emit mouseReleased(event->pos());
}

void TrackpadArea::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::RightButton) {
    static QPoint lastPos = event->pos();
    QPoint currentPos = event->pos();

    // Calculate deltas
    int deltaX = currentPos.x() - lastPos.x();
    int deltaY = currentPos.y() - lastPos.y();

    float adjustedDeltaX = deltaX * sensitivity;
    float adjustedDeltaY = deltaY * sensitivity;

    lastPos = currentPos;

    qDebug() << "Adjusted Movement: " << adjustedDeltaX << "," << adjustedDeltaY;

    emit mouseMoved(QPoint(adjustedDeltaX, adjustedDeltaY));
  }
}

void TrackpadArea::onSensitivityChanged(int value) {
  qDebug() << "Sensitivity changed to: " << value;
  sensitivity = static_cast<float>(value);
}
