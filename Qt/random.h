//
// Created by YY  WYX on 2019/8/23.
//

#ifndef HELLO_RANDOM_H
#define HELLO_RANDOM_H

#include <QLabel>
#include <random>
#include <QVariant>


struct YY{ //随机数初始化
private:
     std::uniform_int_distribution<int> distribution;
     std::default_random_engine  e;
public:
   YY(int min, int max, unsigned seed = 0): e(seed),distribution(min, max){};
    int roll(){
        return distribution(e);
    }
};
struct Label : QLabel{ //显示随机数
    Q_OBJECT
private:
    YY Rand = YY(1,6,0);  //初始化随机数
public:
    void setRollNumber(){
        setText(QVariant(Rand.roll()).toString());
    }
};
#endif //HELLO_RANDOM_H