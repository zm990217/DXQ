#ifndef LAYER_H
#define LAYER_H
#include <QWidget>
#include <QtWidgets>
#include "stroke.h"

enum BlendingMode{
    NORMAL
};

class Layer
{
public:
    bool visible;
    BlendingMode blendingMode;
    QVector<Stroke> data;
};

#endif // LAYER_H
