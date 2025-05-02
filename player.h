#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTransform>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Player(QGraphicsTextItem *score = nullptr, QGraphicsItem *parent = nullptr);
    ~Player() override = default;

    void updateHealth(int damage);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void physics();

signals:
    void playerDied();

private:
    // Movement and state
    qreal velocityX;
    qreal velocityY;
    bool isJumping;
    bool isCrouching;
    bool movingLeft;
    bool movingRight;
    bool rightside;
    bool isattacking;
    int jumpnum;

    // Appearance
    QPixmap standingPixmap;
    QPixmap attackingPixmap;
    QPixmap crouchingPixmap;
    static constexpr int standingHeight = 100;
    static constexpr int crouchingHeight = 50;

    // Gameplay
    QTimer *movementTimer;
    QGraphicsRectItem *healthBar;
    int health;
    qreal moveSpeed;
    qreal gravity;
    qreal jumpStrength;

    // Optional UI
    QGraphicsTextItem *scoreText;
};

#endif // PLAYER_H
