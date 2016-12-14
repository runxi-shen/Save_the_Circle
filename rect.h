/* class Rect is the attacking rectangles that hurt
 * the main character circle when colliding with it
*/
#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Rect: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructor
    Rect();
    // the moving speed of the rect
    int speed;
public slots:
    // the function for moving
    void move();
private:
    // x and y coordinates for initial location
    int x;
    int y;
    // moving direction of the rect
    int dir;
};

#endif // BULLET_H


