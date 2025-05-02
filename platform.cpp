#include "platform.h"
#include <QBrush>
#include <QPen>
// Constructor implementation
Platform::Platform(qreal x, qreal y, qreal width, qreal height)
    // Call the base class (QGraphicsRectItem) constructor with the rectangle parameters
    : QGraphicsRectItem(x, y, width, height)
{
    setBrush(Qt::darkGreen);
    setPen(Qt::NoPen); // Optional: Remove the outline
}

// Destructor implementation
Platform::~Platform()
 {
}
