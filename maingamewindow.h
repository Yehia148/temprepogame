#ifndef GAMEWINDOW_H // Header guard to prevent multiple inclusions.
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsPixmapItem> // Include for background image

// Declare the GameWindow class, inheriting from QWidget.
class GameWindow : public QWidget
{
    Q_OBJECT // Enables QT's meta-object system for signals/slots, etc.

public:
    // Constructor declaration. Takes an optional parent QWidget.
    GameWindow(QWidget *parent = nullptr);
    // Destructor declaration.
    ~GameWindow();

    // Function to restart the game window (e.g., after player death).
    void restartWindow();

private:
    QGraphicsScene *scene; // Pointer to the QGraphicsScene (the canvas).
    QGraphicsView *view; // Pointer to the QGraphicsView (the widget displaying the scene).
    QGraphicsTextItem *startMessage; // Pointer to the start message text item.
    QGraphicsPixmapItem *backgroundItem; // Pointer to the background image item.

    bool gameStarted; // Flag to track if the game has started.

protected:
    // Override the base class's mousePressEvent to handle mouse clicks on the window.
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    // Slot function to transition from the start screen to the game.
    void startGame();
    // Slot function to set up the elements of Level 1.
    void setupLevel1();
};


#endif // GAMEWINDOW_H // End of header guard.
