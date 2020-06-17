#pragma once

/**
 * @file drag_windget.h
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief
 * @version 0.1
 * @date 2020-06-17
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include <QFrame>

class DraggableWidget : public QFrame {
  Q_OBJECT
public:
  explicit DraggableWidget(QWidget* parent = nullptr);

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
};