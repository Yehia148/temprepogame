#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsRectItem>

// Platform class inherits from QGraphicsRectItem
class Platform : public QGraphicsRectItem
{
public:
    // Constructor that takes the rectangle parameters (x, y, width, height)
    Platform(qreal x, qreal y, qreal width, qreal height);

    ~Platform();
};

#endif
