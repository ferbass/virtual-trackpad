#ifndef TRACKPADAREA_H
#define TRACKPADAREA_H

#include <QLabel>
#include <QMouseEvent>

class TrackpadArea : public QLabel {
  Q_OBJECT

  public:
    explicit TrackpadArea(QWidget *parent = nullptr);

signals:
    void mousePressed(const QPoint &pos);
    void mouseReleased(const QPoint &pos);
    void mouseMoved(const QPoint &pos);

  protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // TRACKPADAREA_H

