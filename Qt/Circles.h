//
// Created by YY  WYX on 2019/8/23.
//

#ifndef HELLO_CIRCLE_H
#define HELLO_CIRCLE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
#include <QGraphicsItem>
#include <QRect>

#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include <QVector>
#include <QPen>


struct Circle : QGraphicsObject {
Q_OBJECT
private:
    QString text;
public:
    //圆圈上的数字以及？？
    explicit Circle(const QString &text, QGraphicsItem *parent = nullptr) :
            text(text), QGraphicsObject(parent) {}

    QRectF boundingRect() const override {
        return {0, 0, 40, 40}; //包裹圆圈的正方形，限制圆圈的大小
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->setPen(QPen(Qt::black, 3.3, Qt::SolidLine)); //
        painter->setBrush(Qt::yellow); //填充圆圈的颜色为黄色
        painter->drawEllipse(boundingRect());//显示椭圆

        QFont font;
        font.setPointSize(15); //字体大小
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, text);//？？
    }

    void animate(const std::vector<int> &result) {
    } //？？显示结果？？
};
#endif //HELLO_MYCIRCLE_H