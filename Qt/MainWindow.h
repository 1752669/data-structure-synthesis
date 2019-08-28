//
// Created by YY  WYX on 2019/8/23.
//

#ifndef HELLO_MAINWINDOW_H
#define HELLO_MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include "MyCircle.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QStateMachine>
#include <QState>
#include <QTimer>
#include <QPushButton>
#include "Circles.h"
#include "Game.h"

struct MainWindow : QMainWindow {
private:
    QGraphicsView view;
    // 最大的人数选择
    const int maxPeople = 20;
    // 圆圈的视图
    ManyCircles *circles = nullptr;
    // 结果
    QLineEdit lineEdit;
    // 随机数牌子
    QPushButton label;
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        lineEdit.setReadOnly(true);
        lineEdit.setText("结果");
        lineEdit.move(0, 50); //结果框显示在界面的位置
        lineEdit.setFixedSize(500,30);
        label.setText("随机数");
        label.move(400, 400); //随机数LABLE在界面显示的位置

        // view作为子对象显示
        view.setParent(this);
        this->setCentralWidget(&view);

        // 把圆圈扔进这个scene场景里面
        auto scene = new QGraphicsScene(QRect(0, 0, 1500, 800), this);
        view.setScene(scene);

        scene->addWidget(&label);
        scene->addWidget(&lineEdit);
//设计一个菜单栏
        auto menu = menuBar()->addMenu("操作");
        auto choosePeople = menu->addAction("选择人数");
        auto startGame = menu->addAction("开始游戏");

        // 选择了这个菜单栏的这个动作就会自动运行下面的choosePeople
        QObject::connect(choosePeople, &QAction::triggered, this, &MainWindow::choosePeople);
        QObject::connect(startGame, &QAction::triggered, this, &MainWindow::startGame);
    }

    void startGame() {
        if (circles == nullptr) { return; } //如果人数为0的话直接返回，不进行游戏
        int peopleCount = circles->count(); //输入的选择游戏的人数
        Game game(peopleCount);
        const auto &result = game.playing(peopleCount - 1);
        circles->animate(QVector<int>::fromStdVector(result));

        QString s; //一个数组用来显示出列的人的编号
        for (int index : result) {
            s += QVariant(index).toString() + " ";
        }
        lineEdit.setText(s);

        const auto &randoms = game.getRandoms(); //随机数（用来显示当前的随机数）

        QVector<QState *> states; //状态机
        auto stateMachine = new QStateMachine;
        for (int number : randoms) {
            auto state = new QState;
            state->assignProperty(&label, "text", QVariant(number).toString());
            states.push_back(state);
            stateMachine->addState(state);//连接各种状态（1->2->3....)
        }
        stateMachine->setInitialState(states.first()); //状态初始化

        auto timer = new QTimer(this); //加一个时钟，让随机数与出列的人同步进行
        timer->setInterval(1200);

        for (int i = 0; i < states.size() - 1; ++i) {
            states[i]->addTransition(timer, &QTimer::timeout, states[i + 1]);
        }

        timer->start();
        stateMachine->start();
    }

    void choosePeople() {
        // 子对话框
        QDialog dialog(this);

        // 下拉菜单，用来选择人数，依附于对话框上
        QComboBox selector(&dialog);
        for (int i = 2; i <= maxPeople; ++i) {
            selector.addItem(QVariant(i).toString());
        }

        // 阻塞程序，等待用户选择完人数
        dialog.exec();

        // 用选择的人数初始化circles
        int peopleNumber = selector.currentText().toInt();
        circles = new ManyCircles(peopleNumber);
        // 把它加入到场景里
        view.scene()->addItem(circles);
        circles->setPos(400, 400);
    }
};


#endif //HELLO_MAINWINDOW_H