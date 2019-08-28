//
// Created by YY  WYX on 2019/8/23.
//
//约瑟夫环的显示
#ifndef HELLO_MYCIRCLE_H
#define HELLO_MYCIRCLE_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QVector>
#include "Circles.h"
#include <cmath>
//继承QT函数
struct ManyCircles : QGraphicsObject {
Q_OBJECT
private:
    QVector<Circle *> circle;
public:
    ManyCircles(int n, QGraphicsItem *parent = nullptr) : QGraphicsObject(parent) {
        int r = 150;  //大圆的半径
        double rad = 0;
        const double step = 2 * 3.1415926 / n;  //每个人分别占有大圆圈的平均角度
        for (int i = 0; i < n; ++i) {
            double x = r * cos(rad);
            double y = r * sin(rad);
            circle.push_back(new Circle(QVariant(i).toString(), this)); //圆圈上的数值
            circle.last()->setPos(x, y);  //设置每个人的坐标
            rad += step;
        }
    }

    int count() { return circle.count(); }  //返回圆圈的数量

    void animate(const QVector<int> &order) {
        auto group = new QSequentialAnimationGroup;
        for (int index : order) {
            auto animation = new QPropertyAnimation(circle[index], "opacity", this);
            animation->setEndValue(0); //？？？
            animation->setDuration(1200); //人消失的时间长度
            group->addAnimation(animation);
        }
        group->start(QPropertyAnimation::DeleteWhenStopped);//？？
    }

    QRectF boundingRect() const override { return {}; } //？？

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {} //？？？
};


#endif //HELLO_MYCIRCLE_H
