#include "maingamewindow.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include "player.h"
#include <QPixmap>
#include <QKeyEvent>
#include <platform.h>

// Constructor for the GameWindow class.
// It takes an optional QWidget pointer 'parent' and initializes member variables.
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), // Call the base class (QWidget) constructor with the parent.
    scene(nullptr), // Initialize the scene pointer to nullptr.
    view(nullptr), // Initialize the view pointer to nullptr.
    startMessage(nullptr), // Initialize the startMessage pointer to nullptr.
    gameStarted(false) // Initialize the gameStarted flag to false.

{
    // Create the QGraphicsScene, which is the canvas for our game items.
    scene = new QGraphicsScene(this); // 'this' sets the GameWindow as the parent, ensuring proper memory management.
    scene->setSceneRect(0, 0, 800, 400); // Set the coordinate system and size of the scene.

    // Create the QGraphicsView, which is a widget that visualizes the scene.
    view = new QGraphicsView(scene, this); // Link the view to the scene and set GameWindow as parent.
    view->setFixedSize(800, 400); // Set a fixed size for the view widget.
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Hide the horizontal scroll bar.
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Hide the vertical scroll bar.

    // --- Setup for the initial start screen ---

    // Create a QGraphicsTextItem to display the start message.
    startMessage = new QGraphicsTextItem("Click to Start Game");
    QFont font("Arial", 30); // Create a QFont object for styling the text.
    startMessage->setFont(font); // Set the font for the start message.
    startMessage->setDefaultTextColor(Qt::white); // Set the text color to white.

    // Calculate the position to center the message in the scene.
    qreal messageX = (scene->width() - startMessage->boundingRect().width()) / 2;
    qreal messageY = (scene->height() - startMessage->boundingRect().height()) / 2;
    startMessage->setPos(messageX, messageY); // Set the position of the start message in the scene.

    // Add the start message item to the scene.
    scene->addItem(startMessage);

    // --- Layout for the GameWindow ---

    // Create a QVBoxLayout to arrange widgets vertically.
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view); // Add the QGraphicsView to the layout.
    setLayout(layout); // Set the layout for the GameWindow widget.

    // Set the title of the GameWindow.
    setWindowTitle("Prince of Persia");

    // The game starts with the start screen displayed.
    // The actual content of Level 1 will be set up later when startGame() is called.
}

// Destructor for the GameWindow class.
GameWindow::~GameWindow()
{
    // Since 'scene' and 'view' were created with 'this' as their parent,
    // QT's object ownership system will automatically delete them when the GameWindow is destroyed.
}

// Override of the mousePressEvent handler to detect clicks on the GameWindow.
void GameWindow::mousePressEvent(QMouseEvent *event)
{
    // Check if the game has not started yet and the left mouse button was pressed.
    if (!gameStarted && event->button() == Qt::LeftButton)
    {
        startGame(); // If true, call the startGame() slot.
    }
    else
    {
        // If the game has already started or it's not a left click,
        // pass the event to the base class's mousePressEvent handler.
        // This is important so that if you add clickable items to the scene later,
        // the event can be processed by the QGraphicsView and delivered to those items.

        QWidget::mousePressEvent(event); // Call the mousePressEvent of the base class (QWidget).
    }
}

// Slot function to transition from the start screen to the game.
void GameWindow::startGame()
{
    // Check if the game hasn't been started already (prevents starting multiple times).
    if (!gameStarted)
    {
        gameStarted = true; // Set the flag to indicate the game has started.

        // Remove and delete the start message item from the scene.
        if (startMessage) { // Check if the start message item exists.
            scene->removeItem(startMessage); // Remove the item from the scene.
            delete startMessage; // Delete the QGraphicsTextItem object from memory.
            startMessage = nullptr; // Set the pointer to nullptr to avoid dangling pointers.
        }

        // Call the function to set up the content of Level 1.
        setupLevel1();
    }
}

// Slot function to set up the elements of Level 1.
void GameWindow::setupLevel1()
{
    // This function is called when the game transitions from the start screen to Level 1.
    // Its responsibility is to populate the scene with all the initial elements for Level 1:
    // platforms, obstacles, enemies, the player, and any level-specific decorations.

    qDebug("Setting up Level 1..."); // Print a debug message to confirm this function is executed.

<<<<<<< HEAD
    Platform *floorPlatform = new Platform(0, scene->height() - 50, scene->width(), 50);
    scene->addItem(floorPlatform); // Add the floor platform item to the QGraphicsScene.
=======
    QPixmap bgPixmap(":/images/images/images.jpg");
    bgPixmap = bgPixmap.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem* bgItem = scene->addPixmap(bgPixmap);
    bgItem->setZValue(-1);  // Ensure background is behind everything else

    // --- Add the Floor ---
    // Add a simple green rectangle at the bottom of the scene to represent the floor.
    // This visually confirms that setupLevel1 has been called.
    // QGraphicsRectItem(x, y, width, height)
    QGraphicsRectItem *floor = new QGraphicsRectItem(0, scene->height() - 50, scene->width(), 50);
    floor->setBrush(Qt::darkGreen); // Set the fill color of the rectangle to dark green.
    scene->addItem(floor); // Add the floor rectangle item to the QGraphicsScene.
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)

    Platform *floatingPlatform = new Platform(200, scene->height() - 150, 100, 20);
    scene->addItem(floatingPlatform); // Add the floating platform item to the scene.

    // ** You will add more platforms and obstacles here based on your Level 1 design. **
    // Examples:

    // Create an instance of our Player class.
    Player * player = new Player();

    QPixmap playerPixmap(":/images/images/PRINCE_OF_PERSIA_MAIN_CHARACTER-removebg-preview.png");

    // Check if the pixmap loaded successfully
    if (playerPixmap.isNull()) {
        qDebug() << "Error loading player image!";
    } else {
        // Scale the pixmap to a suitable size for the player character.
        // You can adjust these dimensions as needed.
        playerPixmap = playerPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

<<<<<<< HEAD
    playerPixmap = playerPixmap.scaledToWidth(50); // Scale the width to 50 pixels.
    playerPixmap = playerPixmap.scaledToHeight(50); // Scale the height to 50 pixels.
=======
    // Set the initial position of the player in the scene.
    // the player is placed just above the floor rectangle we added.
    qreal initialPlayerX = 725; // Starting x-position, adjust as needed.
    qreal initialPlayerY = scene->height() - 50 - player->pixmap().height(); // Position just above the floor.
    player->setPos(initialPlayerX, initialPlayerY); // Set the player's position in the scene.
>>>>>>> 77e3244 (game polished and ending of level 1 implemented)

    // Set the loaded and scaled image as the pixmap for the player item.
    player->setPixmap(playerPixmap);

    player->setPos(50, floorPlatform->y() - player->boundingRect().height() - 1);

    // Add the player item to the QGraphicsScene so it becomes visible.
    scene->addItem(player);

    // For the player's keyPressEvent and keyreleaseEvent to be called,the player item needs to be focusable and have focus.
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    // Set the keyboard input focus to the player item.This ensures that key events go directly to the player.
    player->setFocus();
connect(player, &Player::playerDied, this, &GameWindow::restartWindow);


    // --- Other Level 1 Setup (To be added later) ---
    // This is where you would add instances of your Enemy class, Obstacle class (spikes, fire, etc.),
    // items (coins, power-ups), and potentially background elements specific to Level 1.

}
void GameWindow::restartWindow(){
    this->close();
    GameWindow *newGame = new GameWindow();
    newGame->show();
}
