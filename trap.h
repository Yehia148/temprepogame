// trap.h
#ifndef TRAP_H
#define TRAP_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Trap : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Trap(const QString &imagePath,
                  QGraphicsItem *parent = nullptr)
        : QObject(), QGraphicsPixmapItem(parent)
    {
        setPixmap(QPixmap(imagePath));
    }
    // … add signals, slots, properties here …
};

#endif // TRAP_H
