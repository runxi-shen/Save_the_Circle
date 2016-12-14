/* class Trouble is the big circle that will increase
 * the size of main character circle to increase game
 * difficulty
*/

#ifndef TROUBLE_H
#define TROUBLE_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QGraphicsItem>

class Trouble: public QObject,public QGraphicsEllipseItem{
    Q_OBJECT

public:
    Trouble();
    // moving speed
    int speed;

public slots:
    void move();
private:
    // initial location
    int x;
    int y;
    // moving direction
    int dir;
};
#endif // TROUBLE_H
