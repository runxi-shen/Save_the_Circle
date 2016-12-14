/** main character circle
*/

#include "circle.h"
#include "rect.h"
#include "trouble.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

Circle::Circle(): QObject(),QGraphicsEllipseItem(){
    size = 100;
    life = 3;
    setRect(0,0,size,size);
    setPos(550,400);
    setBrush(Qt::green);
}

void Circle::keyPressEvent(QKeyEvent *event)
{
    // move the circle with keyboard
    if (event->key() == Qt::Key_Left){
        if (scenePos().x()>0)
            setPos(x()-20, y());
    }
    else if (event->key() == Qt::Key_Right){
        if (scenePos().x()-200 < 900)
            setPos(x()+20, y());
    }
    else if (event->key() == Qt::Key_Up){
        if (scenePos().y() > 0)
            setPos(x(), y()-20);
    }
    else if (event->key() == Qt::Key_Down){
        if (scenePos().y()+400 < 1200)
            setPos(x(), y()+20);
    }
}

void Circle::getHurt(){
    life -= 1;
    changeColor();
}

void Circle::changeColor(){
    if (life == 2)
        setBrush(Qt::yellow);
    else if (life == 1)
        setBrush(Qt::red);
    else
        return;
}

void Circle::changeSize(){
    size += 25;
    setRect(0,0,size,size);
    setPos(pos().x(),pos().y());
}

bool Circle::dead(){
    if (life == 0)
        return true;
    else
        return false;
}
