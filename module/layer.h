#ifndef LAYER_H
#define LAYER_H
#include <QWidget>
#include <QtWidgets>
#include "stroke.h"

enum BlendingMode{
    NORMAL      //默认NORMAL
};

class Layer     //The Layer of pictures
{
public:
    bool visible;       //是否可见
    BlendingMode blendingMode;      //模式
    QVector<Stroke> data;
};

#endif // LAYER_H
