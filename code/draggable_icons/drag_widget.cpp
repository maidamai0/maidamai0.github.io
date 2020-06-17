#include "drag_widget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QFrame>
#include <QLabel>
#include <QMimeData>
#include <QPainter>
#include <QPixmap>

DraggableWidget::DraggableWidget(QWidget* parent) : QFrame(parent) {
  setMinimumSize(200, 200);
  setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
  setAcceptDrops(true);

  auto* boat_icon = new QLabel(this);
  boat_icon->setPixmap(QPixmap(":/boat.png"));
  boat_icon->move(10, 10);
  boat_icon->show();
  boat_icon->setAttribute(Qt::WA_DeleteOnClose);

  auto* car_icon = new QLabel(this);
  car_icon->setPixmap(QPixmap(":/car.png"));
  car_icon->move(100, 10);
  car_icon->show();
  car_icon->setAttribute(Qt::WA_DeleteOnClose);

  auto* house_icon = new QLabel(this);
  house_icon->setPixmap(QPixmap(":/house.png"));
  house_icon->move(10, 80);
  house_icon->show();
  house_icon->setAttribute(Qt::WA_DeleteOnClose);
}

void DraggableWidget::dragEnterEvent(QDragEnterEvent* event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void DraggableWidget::dragMoveEvent(QDragMoveEvent* event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void DraggableWidget::dropEvent(QDropEvent* event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    auto* newIcon = new QLabel(this);
    newIcon->setPixmap(pixmap);
    newIcon->move(event->pos() - offset);
    newIcon->show();
    newIcon->setAttribute(Qt::WA_DeleteOnClose);

    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void DraggableWidget::mousePressEvent(QMouseEvent* event) {
  QLabel* child = static_cast<QLabel*>(childAt(event->pos()));
  if (child == nullptr)
    return;

  QPixmap pixmap = *child->pixmap();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(event->pos() - child->pos());

  auto* mimeData = new QMimeData;
  mimeData->setData("application/x-dnditemdata", itemData);

  auto* drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(event->pos() - child->pos());

  QPixmap& tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  child->setPixmap(tempPixmap);

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
    child->close();
  } else {
    child->show();
    child->setPixmap(pixmap);
  }
}