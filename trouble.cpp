#include "trouble.h"
#include "circle.h"
#include "rect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand()
#include "Game.h"
#include <QDebug>

extern Game *game;

Trouble::Trouble():QObject(),QGraphicsEllipseItem(){
    setRect(0,0,200,200);
    setBrush(Qt::black);
    speed = 10;

    // set random direction: 0: top, 1: bottom, 2: left, 3: right
    dir = rand() % 4;
    // generate random location
    x = rand() % 1200;
    y = rand() % 900;
    // constrain the location to be in boundaries
    if (x > 900)
        x = 900;
    if (y > 700)
        y = 600;

    // randomly assign the location for big circles
    switch(dir){
    case 0:
        setPos(x,0);
        break;
    case 1:
        setPos(x, 800);
        break;
    case 2:
        setPos(0, y);
        break;
    case 3:
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

void Trouble::move(){

    // increase the size of the circle when collides
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0,n=colliding_items.size();i<n;i++){
        if (typeid(*(colliding_items[i])) == typeid(Circle)){
            Circle *item = dynamic_cast<Circle*> (colliding_items[i]);
            item->changeSize();
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
