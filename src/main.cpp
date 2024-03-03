#include <QApplication>
#include "TrackpadWidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  TrackpadWidget widget;
  widget.setWindowTitle("Trackpad Serial Control");
  widget.show();

  return app.exec();
}
