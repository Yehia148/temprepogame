#include "player.h"
#include "trap.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
<<<<<<< HEAD

=======
#include <QMessageBox>
#include "maingamewindow.h"
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)
Player::Player(QGraphicsTextItem * inScore)
    : velocityX(0), velocityY(0), isJumping(false), isCrouching(false)
{
    healthBar = new QGraphicsRectItem(0, 0, 100, 10, this);
    healthBar->setBrush(Qt::green);
    healthBar->setPos(0, -20);

    standingPixmap = QPixmap(":/images/images/PRINCE_OF_PERSIA_MAIN_CHARACTER-removebg-preview.png")
    .scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    attackingPixmap = QPixmap("C:/CS2CourseProject/codework/images/images/Prince_of_persia_character_attacking-removebg-preview.png")
                          .scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    crouchingPixmap = standingPixmap.scaled(100, crouchingheight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(standingPixmap);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Player::physics);
    movementTimer->start(16);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Left:
        movingLeft = true;
        velocityX = -moveSpeed;
        if (rightside) {
            QTransform transform;
            transform.scale(-1, 1);
            setTransform(transform);
            rightside = false;
        }
<<<<<<< HEAD
        break;
    case Qt::Key_Right:
        movingRight = true;
        velocityX = moveSpeed;
=======
        if(x() <= 150){
            QMessageBox::information(nullptr, "Congratulations", "Level 1 Complete!");
        }
    }
    else if (event->key() == Qt::Key_Right && !isJumping)
    {
        setPos(x() + moveSpeed, y());
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)
        if (!rightside) {
            setTransform(QTransform());
            rightside = true;
        }
<<<<<<< HEAD
        break;
    case Qt::Key_Up:
        if (!isJumping && !isCrouching) {
=======
        if(x() <= 150){
            QMessageBox::information(nullptr, "Congratulations", "Level 1 Complete!");
        }
    }
    else if (event->key() == Qt::Key_Up && !isCrouching)
    {
        if (jumpnum < 2)
        {
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)
            velocityY = jumpStrength;
            isJumping = true;
        }
        break;
    case Qt::Key_Down:
        if (!isJumping && !isCrouching) {
            isCrouching = true;
            setPixmap(crouchingPixmap);
            setPos(x(), y() + (standingheight - crouchingheight));
        }
<<<<<<< HEAD
        break;
    case Qt::Key_Space:
        if (!isattacking) {
            setPixmap(attackingPixmap);
=======
        if(x() <= 150){
             QMessageBox::information(nullptr, "Congratulations", "Level 1 Complete!");
        }
    }
    else if (event->key() == Qt::Key_Right && isJumping && !isCrouching)
    {
        setPos(x() + moveSpeed + 60, y());
        if (!rightside) {
            QTransform transform;
            setTransform(transform);
            rightside = true;
        }
        if(x() <= 150){
            QMessageBox::information(nullptr, "Congratulations", "Level 1 Complete!");
        }
    }
    else if (event->key() == Qt::Key_Down && !isJumping && !isCrouching)
    {
        isCrouching = true;
        setPixmap(crouchingPixmap);

        setPos(x(), y() + (standingheight - crouchingheight));
        }
    else if (event->key() == Qt::Key_Space && !isattacking)
    {
        setPixmap(attackingPixmap);
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)
            isattacking = true;
        } else {
            setPixmap(standingPixmap);
            isattacking = false;
        }
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
    }
    else if (event->key() == Qt::Key_Right) {
        movingRight = false;
        if (!movingLeft) velocityX = 0;
    }
    else {
        QGraphicsPixmapItem::keyReleaseEvent(event);
    }
}

void Player::physics()
{
    // Apply gravity
    velocityY += gravity;

    // Potential positions
    qreal nextX = x() + velocityX;
    qreal nextY = y() + velocityY;

<<<<<<< HEAD
    // Move and handle floor collision
    setPos(nextX, nextY);
    if (y() >= 450) {
        setPos(nextX, 450);
=======
    if (y() >= 300)
    {
        setPos(x(), 300);
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)
        velocityY = 0;
        isJumping = false;
        jumpnum = 0;
    }

    // Collision with Traps
    QList<QGraphicsItem *> colliding = collidingItems();
    for (QGraphicsItem *item : colliding) {
        Trap *trap = dynamic_cast<Trap *>(item);
        if (trap) {
            isDying = true;
            updateHealth(25);
            qDebug() << "Player hit a trap!";
            return;
        }
    }
}

void Player::updateHealth(int damage)
{
    health = health - damage;
    if (health < 0) health = 0;

    healthBar->setRect(0, 0, health, 10);

    if (health == 0)
    {

        QMessageBox::information(nullptr, "Game Over", "You Died!");
         emit playerDied();
}
}
