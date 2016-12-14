/* The main character in "Save the Circle" game. Controlled by user to avoid
*  the attacks from rectangles and can be enlarged by the big circle to increase
*  the odds of being attacked.
*  Circle has three lives in total and the color will change correspondingly
*  when it loses its life.
*/

#ifndef CIRCLE_H
#define CIRCLE_H
#include <QObject>
#include <QGraphicsEllipseItem>

class Circle: public QObject,public QGraphicsEllipseItem{
    Q_OBJECT
public:
    Circle();
    // decrease the life of the circle by 1
    void getHurt();
    // change the color of the circle to remind player of how many lives left
    void changeColor();
    // increase the size when attacked by big circle
    void changeSize();
    // move the circle by keyboard
    void keyPressEvent(QKeyEvent *event);
    // return the circle is dead or not
    bool dead();

private:
    int life;
    int size;
};
#endif // CIRCLE_H
