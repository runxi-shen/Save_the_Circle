#include "game.h"
#include "circle.h"
#include "trouble.h"
#include "rect.h"
#include "button.h"
#include <QKeyEvent>
#include <QLabel>
#include <QObject>
#include <stdlib.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QDebug>

/** game constructor
 * @ set up the game
 * @ create the circle and background
 * @ create timers that generate attacking rectangles and circles
 * @ control the whole game procedure
*/

Game::Game():QGraphicsView(){

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,900);
    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,900);
    setScene(scene);
}

Game::~Game(){
    delete circle;
    delete timer1;
    delete timer2;
    delete timer3;
    delete timer4;
    delete scene;
}

// start the game
void Game::start(){
    scene->clear();

    circle = new Circle();
    circle->setFlag(QGraphicsItem::ItemIsFocusable);
    circle->setFocus();
    scene->addItem(circle);

    // the timer for sending out the rectangles
    timer1 = new QTimer();
    time1 = 2000;
    QObject::connect(timer1, SIGNAL(timeout()),this,SLOT(spawn()));
    timer1->start(time1);

    // the timer for sending out the big circles
    timer2 = new QTimer();
    time2 = 5000;
    QObject::connect(timer2, SIGNAL(timeout()),this,SLOT(spawn_trouble()));
    timer2->start(time2);

    // the timer for checking the status of the circle
    timer3 = new QTimer();
    QObject::connect(timer3, SIGNAL(timeout()),this,SLOT(gameOver()));
    timer3->start(1);

    // the timer for speed-up movement of attackers to increase difficulty
    timer4 = new QTimer();
    QObject::connect(timer4, SIGNAL(timeout()),this,SLOT(speedUp()));
    timer4->start(8000);
}

// restart the game
void Game::restart(){
    delete circle;
    delete timer1;
    delete timer2;
    delete timer3;
    delete timer4;
    scene->clear();
    start();
}

// display the window before game starts
void Game::displayMainWindow(){
    scene->clear();
    // create the title for the game
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("Save the Circle"));
    QFont titleFont("comic sans", 20);
    title->setFont(titleFont);
    int tx = this->width()/2 - title->boundingRect().width()/2;
    int ty = 100;
    title->setPos(tx,ty);
    scene->addItem(title);

    // create the play button
    Button *play = new Button(QString("Play"));
    int bx = this->width()/2 - play->boundingRect().width()/2;
    int by = 350;
    play->setPos(bx,by);
    connect(play,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(play);

    // create the instruction button
    // create the quit button
    Button *instr = new Button(QString("Instruction"));
    int ix = this->width()/2 - instr->boundingRect().width()/2;
    int iy = 450;
    instr->setPos(ix, iy);
    connect(instr,SIGNAL(clicked()),this,SLOT(instructions()));
    scene->addItem(instr);

    // create the quit button
    Button *quit = new Button(QString("Quit"));
    int qx = this->width()/2 - quit->boundingRect().width()/2;
    int qy = 550;
    quit->setPos(qx, qy);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quit);
}

// show instructions
void Game::instructions(){
    scene->clear();

    drawPanel(0,0,1200,900,Qt::black,0.65);

    QString instruction = "Welcome to Save the Circle!\nYou are the circle running away from the rectangular attackers that hurt your life \nand the big-circle trouble makers that increase your size.\nUse the direction keys on keyboard to control the circle's movement.\nYou have three lives in total and your color will remind you how many lives you have left.\nGood luck!";
    QGraphicsTextItem *text = new QGraphicsTextItem(instruction);
    QFont textFont("comic sans", 8);
    text->setFont(textFont);
    int tx = 0;
    int ty = 100;
    text->setPos(tx,ty);
    scene->addItem(text);

    Button* back = new Button(QString("Back"));
    int qx = this->width()/2 - back->boundingRect().width()/2;
    int qy = 600;
    back->setPos(qx,qy);
    scene->addItem(back);
    connect(back,SIGNAL(clicked()),this,SLOT(displayMainWindow()));
}

// move the attacking rects
void Game::spawn(){
    Rect *rect = new Rect();
    scene->addItem(rect);
}

// move the big circles
void Game::spawn_trouble(){
    Trouble *trouble = new Trouble();
    scene->addItem(trouble);
}

// speed up the attackers' movements
void Game::speedUp(){
    timer1->start(int(time1/2));
    timer2->start(int(time2/2));
}

// draw panel for messages
void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

// game over function
void Game::gameOver(){
    if (circle->dead()){
        QString message("Game Over");
        timer1->stop();
        timer2->stop();
        timer3->stop();
        timer4->stop();
        // pop up panel to show game over message
        drawPanel(0,0,1200,900,Qt::black,0.65);
        drawPanel(100,50,1000,800,Qt::lightGray,0.75);
        // create text annoucning winner
        QGraphicsTextItem* overText = new QGraphicsTextItem(message);
        QFont textFont("comic sans", 20);
        overText->setFont(textFont);
        int tx = this->width()/2 - overText->boundingRect().width()/2;
        int ty = 100;
        overText->setPos(tx,ty);
        scene->addItem(overText);
        // create playAgain button
        Button* playAgain = new Button(QString("Play Again"));
        int bx = this->width()/2 - playAgain->boundingRect().width()/2;
        int by = 400;
        playAgain->setPos(bx,by);
        scene->addItem(playAgain);
        connect(playAgain,SIGNAL(clicked()),this,SLOT(restart()));
        // create quit button
        Button* quit = new Button(QString("Quit"));
        int qx = this->width()/2 - quit->boundingRect().width()/2;
        int qy = 600;
        quit->setPos(qx,qy);
        scene->addItem(quit);
        connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    }
    else
        return;
}
