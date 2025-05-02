#include "player.h"
#include "trap.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QMessageBox>
#include "maingamewindow.h"

Player::Player(QGraphicsTextItem *score, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent),
    velocityX(0), velocityY(0),
    isJumping(false), isCrouching(false),
    movingLeft(false), movingRight(false),
    rightside(true), isattacking(false),
    jumpnum(0),
    movementTimer(new QTimer(this)),
    healthBar(new QGraphicsRectItem(0, 0, 100, 10, this)),
    health(100),
    moveSpeed(5.0), gravity(0.5), jumpStrength(-12.0),
    scoreText(score)
{
    // Initialize health bar
    healthBar->setBrush(Qt::green);
    healthBar->setPos(0, -20);

    // Load and scale pixmaps
    standingPixmap = QPixmap(":/images/images/PRINCE_OF_PERSIA_MAIN_CHARACTER-removebg-preview.png")
                         .scaled(standingHeight, standingHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    attackingPixmap = QPixmap("C:/CS2CourseProject/codework/images/images/Prince_of_persia_character_attacking-removebg-preview.png")
                          .scaled(standingHeight, standingHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    crouchingPixmap = standingPixmap.scaled(standingPixmap.width(), crouchingHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(standingPixmap);

    // Start movement timer
    connect(movementTimer, &QTimer::timeout, this, &Player::physics);
    movementTimer->start(16);

    // Enable keyboard input
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        movingLeft = true;
        velocityX = -moveSpeed;
        if (rightside) {
            QTransform t;
            t.scale(-1, 1);
            setTransform(t);
            rightside = false;

            if (x()<=100) {
                QMessageBox::information(nullptr, "Congratulations!", "Level 1 Complete!");
            }
        }
        break;

    case Qt::Key_Right:
        movingRight = true;
        velocityX = moveSpeed;
        if (!rightside) {
            setTransform(QTransform());
            rightside = true;

            if (x()<=100) {
                QMessageBox::information(nullptr, "Congratulations!", "Level 1 Complete!");
            }
        }
        break;

    case Qt::Key_Up:
        if (!isJumping && jumpnum < 2) {
            velocityY = jumpStrength;
            isJumping = true;
            ++jumpnum;
        }
        break;

    case Qt::Key_Down:
        if (!isJumping && !isCrouching) {
            isCrouching = true;
            setPixmap(crouchingPixmap);
            setPos(x(), y() + (standingHeight - crouchingHeight));
        }
        break;

    case Qt::Key_Space:
        isattacking = !isattacking;
        setPixmap(isattacking ? attackingPixmap : standingPixmap);
        break;

    default:
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        movingLeft = false;
        if (!movingRight) velocityX = 0;
    } else if (event->key() == Qt::Key_Right) {
        movingRight = false;
        if (!movingLeft) velocityX = 0;
    } else {
        QGraphicsPixmapItem::keyReleaseEvent(event);
    }
}

void Player::physics()
{
    // Apply gravity
    velocityY += gravity;

    // Next position
    qreal nx = x() + velocityX;
    qreal ny = y() + velocityY;

    // Simple ground collision
    if (ny >= 315) {
        ny = 315;
        velocityY = 0;
        isJumping = false;
        jumpnum = 0;
    }
    setPos(nx, ny);

    // Collision with traps
    for (QGraphicsItem *item : collidingItems()) {
        if (Trap *trap = dynamic_cast<Trap *>(item)) {
            updateHealth(25);
            qDebug() << "Player hit a trap!";
            return;
        }
    }
}

void Player::updateHealth(int damage)
{
    health = qMax(0, health - damage);
    healthBar->setRect(0, 0, health, 10);
    if (health == 0) {
        QMessageBox::information(nullptr, "Game Over", "You Died!");
        emit playerDied();
    }
}
