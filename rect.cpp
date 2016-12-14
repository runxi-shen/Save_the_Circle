#include "rect.h"
#include "circle.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand()
#include "Game.h"
#include <QDebug>

extern Game *game;

Rect::Rect():QObject(),QGraphicsRectItem(){
    setRect(0,0,100,100);
    speed = 5;

    // set random direction: 0: top, 1: bottom, 2: left, 3: right
    dir = rand() % 4;
    // generate random location
    x = rand() % 1200;
    y = rand() % 900;
    // constrain the rect to be in boundaries
    if (x > 1100)
        x = 1100;
    if (y > 800)
        y = 800;

    // randomly assign the colors for rect
    switch(dir){
    case 0:
        setBrush(Qt::lightGray);
        setPos(x,0);
        break;
    case 1:
        setBrush(Qt::cyan);
        setPos(x, 800);
        break;
    case 2:
        setBrush(Qt::blue);
        setPos(0, y);
        break;
    case 3:
        setBrush(Qt::darkCyan);
        setPos(1100,y);
        break;
    default:
        break;
    }

    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Rect::move(){
    // call the getHurt for the circle when collides
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0,n=colliding_items.size();i<n;i++){
        if (typeid(*(colliding_items[i])) == typeid(Circle)){
            Circle *item = dynamic_cast<Circle*> (colliding_items[i]);
            item->getHurt();
            item->changeColor();
            delete this;
            return;
        }
    }

    // setPos(pos().x(),pos().y()+5);
    switch(dir){
    case 0:
        // move bullet down
        setPos(pos().x(),pos().y()+speed);
        break;
    case 1:
        // move bullet up
        setPos(pos().x(),pos().y()-speed);
        break;
    case 2:
        // move right
        setPos(pos().x()+speed,pos().y());
        break;
    case 3:
        // move left
        setPos(pos().x()-speed,pos().y());
        break;
    default:
        break;
    }

    if (pos().y()>900||pos().y()<0||pos().x()<0||pos().x()>1200){
        scene()->removeItem(this);
        delete this;
    }
}

