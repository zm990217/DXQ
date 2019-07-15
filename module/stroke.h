#ifndef STROKE_H
#define STROKE_H
#include <QWidget>
#include <QtWidgets>

enum StrokeType {       //毛刷类型
    ST_FREE,
    ST_RECT,
    ST_ELLIPS,
    ST_DIAMOND,
    ST_LINE,
    ST_ERASE
};

enum StrokeMode{        //毛刷模式
    STM_FILL,
    STM_OUTLINE,
    STM_FILL_OUTLINE
};

class Stroke        //保存定义属性
{
public:
    Stroke(){}
    Stroke(QVector<QRectF> stroke, StrokeType type = ST_FREE, StrokeMode mode = STM_FILL) {
        this->data = stroke;
        this->type = type;
        this->mode = mode;
    }
    QVector<QRectF> data;
    QColor fillColor;           //颜色填充
    QColor outlineColor;
    StrokeType type;
    StrokeMode mode;
    QPointF sStart;     //笔头起点与终点
    QPointF sEnd;
    QPen pen;
    QBrush brush;
};

#endif // STROKE_H
