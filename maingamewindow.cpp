#include "maingamewindow.h" // Include the header file for our GameWindow class.
#include <QGraphicsRectItem>  // Include for QGraphicsRectItem (used for simple shapes, though Platform is preferred).
#include <QDebug>             // Include for qDebug() for debugging output.
#include "player.h"           // Include the header file for the Player class.
#include <QPixmap>            // Include for QPixmap, used for handling images.
#include <QKeyEvent>          // Include for QKeyEvent (used in player, though included here for context).
#include "platform.h"         // Include the header file for the Platform class.
#include <QGraphicsItem>      // Include for QGraphicsItem base class.

// Constructor for the GameWindow class.
// Initializes member variables and sets up the initial start screen.
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), // Call the base class (QWidget) constructor.
    scene(nullptr), // Initialize scene pointer.
    view(nullptr), // Initialize view pointer.
    startMessage(nullptr), // Initialize startMessage pointer.
    backgroundItem(nullptr), // Initialize backgroundItem pointer.
    gameStarted(false) // Initialize gameStarted flag.
{
    // Create the QGraphicsScene, which acts as the canvas for all game items.
    scene = new QGraphicsScene(this); // 'this' sets GameWindow as parent for memory management.
    scene->setSceneRect(0, 0, 800, 400); // Set the coordinate system and size of the scene (increased height for platforms).

    // Create the QGraphicsView, a widget to display the scene.
    view = new QGraphicsView(scene, this); // Link view to scene and set GameWindow as parent.
    view->setFixedSize(800, 400); // Set a fixed size for the view (matching scene).
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Hide scroll bars.
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // --- Setup for the initial start screen ---

    // Create a QGraphicsTextItem for the start message.
    startMessage = new QGraphicsTextItem("Click to Start Game");
    QFont font("Arial", 30); // Set font style and size.
    startMessage->setFont(font);
    startMessage->setDefaultTextColor(Qt::white); // Set text color.

    // Center the start message in the scene.
    qreal messageX = (scene->width() - startMessage->boundingRect().width()) / 2;
    qreal messageY = (scene->height() - startMessage->boundingRect().height()) / 2;
    startMessage->setPos(messageX, messageY);

    // Add the start message to the scene.
    scene->addItem(startMessage);

    // --- Layout for the GameWindow ---

    // Use a QVBoxLayout to arrange the view vertically.
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view); // Add the QGraphicsView to the layout.
    setLayout(layout); // Set the layout for the GameWindow widget.

    // Set the window title.
    setWindowTitle("Prince of Persia");

    // The game starts with the start screen. setupLevel1() is called when the user clicks.
}

// Destructor for the GameWindow class.
GameWindow::~GameWindow()
{
    // scene, view, startMessage, and backgroundItem are parented to 'this',
    // so QT's object ownership handles their deletion automatically.
}

// Override of the mousePressEvent handler to detect clicks on the GameWindow.
void GameWindow::mousePressEvent(QMouseEvent *event)
{
    // Check if the game hasn't started and the left mouse button was clicked.
    if (!gameStarted && event->button() == Qt::LeftButton)
    {
        startGame(); // Transition to the game setup.
    }
    else
    {
        // If the game is already started or it's not a left click,
        // pass the event to the base class for potential handling by items in the scene.
        QWidget::mousePressEvent(event);
    }
}

// Slot function to transition from the start screen to the game.
void GameWindow::startGame()
{
    // Prevent starting the game multiple times.
    if (!gameStarted)
    {
        gameStarted = true; // Set the game started flag.

        // Remove and delete the start message item.
        if (startMessage) {
            scene->removeItem(startMessage);
            delete startMessage;
            startMessage = nullptr;
        }

        // Call the function to set up the content of Level 1.
        setupLevel1();
    }
}

// Slot function to set up the elements of Level 1.
void GameWindow::setupLevel1()
{
    qDebug("Setting up Level 1..."); // Debug message.

    // --- Add Background Image ---
    QPixmap bgPixmap(":/images/images/backgroundL1.jpg"); // Load background image from resources.
    if (bgPixmap.isNull()) {
        qDebug() << "Error loading background image!";
    } else {
        // Scale background to scene size and add to scene.
        bgPixmap = bgPixmap.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        backgroundItem = scene->addPixmap(bgPixmap);
        backgroundItem->setZValue(-1); // Ensure background is behind other items.
    }

    // --- Create and Add Platforms ---
    // Create the main floor platform using the Platform class.
    // Platform(x, y, width, height)
    Platform *floorPlatform = new Platform(0, scene->height() - 50, scene->width(), 50);
    scene->addItem(floorPlatform); // Add the floor platform to the scene.

    // Create an example floating platform.
    // Position relative to the scene and the floor.
    Platform *floatingPlatform = new Platform(200, scene->height() - 150, 150, 20); // Adjusted size for better landing
    scene->addItem(floatingPlatform); // Add the floating platform to the scene.

    // ** Add more Platform objects here to build your level layout. **
    // Example:
    // Platform *anotherPlatform = new Platform(500, scene->height() - 250, 100, 20);
    // scene->addItem(anotherPlatform);

    // --- Create and Add the Player ---
    Player * player = new Player(); // Create a Player object.

    // Load the player's main character image from resources.
    QPixmap playerPixmap(":/images/images/PRINCE_OF_PERSIA_MAIN_CHARACTER-removebg-preview.png");

    // Check if the player image loaded successfully.
    if (playerPixmap.isNull()) {
        qDebug() << "Error loading player image!";
    } else {
        // Scale the player image.
        // Using scaledToWidth/Height ensures aspect ratio is kept.
        playerPixmap = playerPixmap.scaledToWidth(50); // Set player width to 50 pixels.
        // playerPixmap = playerPixmap.scaledToHeight(50); // Height will be scaled proportionally
    }

    // Set the loaded and scaled image as the pixmap for the player item.
    player->setPixmap(playerPixmap);

    // Set the player's initial position on the floor platform.
    // Position the player's bottom edge just above the floor platform's top edge.
    qreal initialPlayerX = 715; // Starting X position.
    qreal initialPlayerY = floorPlatform->y() - player->boundingRect().height() - 1; // Y position just above floor.
    player->setPos(initialPlayerX, initialPlayerY);

    // Add the player item to the QGraphicsScene.
    scene->addItem(player);

    // --- Enable Player Input ---
    // Make the player item focusable to receive keyboard events.
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    // Give keyboard focus to the player item.
    player->setFocus();

    // --- Connect Signals and Slots ---
    // Connect the playerDied signal from the player to the restartWindow slot in GameWindow.
    // This restarts the game when the player dies.
    connect(player, &Player::playerDied, this, &GameWindow::restartWindow);


    // --- Other Level 1 Setup (Add Enemies, Traps, Items here) ---
    // Example (you will uncomment and implement this later):
    // Trap * spikeTrap = new Trap(":/images/images/spike_trap.png");
    // spikeTrap->setPos(300, floorPlatform->y() - spikeTrap->boundingRect().height());
    // scene->addItem(spikeTrap);

    // Enemy * basicEnemy = new Enemy(":/images/images/enemy_image.png");
    // basicEnemy->setPos(600, floorPlatform->y() - basicEnemy->boundingRect().height());
    // scene->addItem(basicEnemy);
}

// Slot function to restart the game window.
void GameWindow::restartWindow(){
    // Close the current window.
    this->close();
    // Create a new GameWindow instance.
    GameWindow *newGame = new GameWindow();
    // Show the new game window.
    newGame->show();
    // Note: The old GameWindow and its scene/items will be deleted
    // when the event loop processes the close() event.
}
