#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include "circle.h"

class Game : public QGraphicsView{
    Q_OBJECT
    friend class circle;
public:
    // constructor
    Game();
    // destructor
    ~Game();

    // draw panel for messages
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    // member fields
    QGraphicsScene *scene;

public slots:
    // member functions

    // display the window before game starts
    void displayMainWindow();
    // start the game
    void start();
    // restart the game when died
    void restart();
    // move the attacking rects
    void spawn();
    // move the big circles
    void spawn_trouble();
    // game over function
    void gameOver();
    // speed up the attackers' movements
    void speedUp();
    // show instructions
    void instructions();

private:
    // main character circle
    Circle *circle;
    // timer controls the rectangles
    QTimer *timer1;
    int time1;
    // timer controls the big circles
    QTimer *timer2;
    int time2;
    // timer controls the game over scheme
    QTimer *timer3;
    // timer controls the game difficulty
    QTimer *timer4;

};

#endif // GAME_H
