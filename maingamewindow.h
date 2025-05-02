#ifndef GAMEWINDOW_H // This is a header guard to prevent multiple inclusions of this header file.
#define GAMEWINDOW_H // If GAMEWINDOW_H is not defined, define it.

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QMouseEvent>

class GameWindow : public QWidget // Declare the GameWindow class, inheriting from QWidget.
{
    Q_OBJECT // This macro enables QT's meta-object system.

public:
    GameWindow(QWidget *parent = nullptr); // Constructor declaration.
    ~GameWindow(); // Destructor declaration.
    void restartWindow();
private:
    QGraphicsScene *scene; // Pointer to the QGraphicsScene.
    QGraphicsView *view; // Pointer to the QGraphicsView.
    QGraphicsTextItem *startMessage; // Pointer to the start message text item.

    bool gameStarted; // Flag to track if the game has started.

protected:
    // Override the base class's mousePressEvent to handle mouse clicks.
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void startGame();
    void setupLevel1();
};


#endif // GAMEWINDOW_H // End of the header guard.
