#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>

// Player class inherits from QObject and QGraphicsPixmapItem to support signals/slots and graphics item.
class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    // Constructor: optional score display and parent GraphicsItem
    Player(QGraphicsTextItem *score = nullptr, QGraphicsItem *parent = nullptr);

    // Public state variables
    qreal velocityX;
    qreal velocityY;
    const qreal moveSpeed = 10.0;
    bool isJumping;
    const qreal gravity = 1.0;
    const qreal jumpStrength = -14.0;  // Retained jump strength from main branch
    bool movingLeft = false;
    bool movingRight = false;
    bool rightside = true;
    bool isDying;
    int standingheight = 100;  // Added standing height
    int crouchingheight = 55;  // Added crouching height
    bool isCrouching = false;
    QTimer * movementTimer;
    QPixmap standingPixmap;
    QPixmap crouchingPixmap;
    QPixmap attackingPixmap;
    QGraphicsRectItem * healthBar;
    int health = 100;
    void updateHealth(int damage);
    bool isattacking = false;

private:
    QTimer *movementTimer;
    int jumpnum;

protected:
    // Override event handlers
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void physics();
<<<<<<< HEAD
=======
signals:
    void playerDied();
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)
};

#endif // PLAYER_H
