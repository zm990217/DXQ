#ifndef STROKE_H
#define STROKE_H
#include <QWidget>
#include <QtWidgets>

enum StrokeType {
    ST_FREE,
    ST_RECT,
    ST_ELLIPS,
    ST_DIAMOND,
    ST_LINE,
    ST_ERASE
};

enum StrokeMode{
    STM_FILL,
    STM_OUTLINE,
    STM_FILL_OUTLINE
};

class Stroke
{
public:
    Stroke(){}
    Stroke(QVector<QRectF> stroke, StrokeType type = ST_FREE, StrokeMode mode = STM_FILL) {
        this->data = stroke;
        this->type = type;
        this->mode = mode;
    }
    QVector<QRectF> data;
    QColor fillColor;
    QColor outlineColor;
    StrokeType type;
    StrokeMode mode;
    QPointF sStart;
    QPointF sEnd;
    QPen pen;
    QBrush brush;
};

#endif // STROKE_H
