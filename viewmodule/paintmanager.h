#ifndef PAINTMANAGER_H
#define PAINTMANAGER_H
#include <iostream>
#include <QPainter>
#include <QWidget>
#include <QtWidgets>
#include "config.h"
#include "layer.h"

// provide basic drawing APIs
// handles QBrush & QPen & mbrush
class PaintManager
{
public:
    StrokeType strokeType;
    StrokeMode strokeMode;
    Qt::BrushStyle brushStyle;
    PaintManager(QImage *image, StrokeMode strokeMode = STM_FILL);
    void setStrokeMode(StrokeMode strokeMode);
    Stroke initStroke();
    void setBackground(QColor background);
    void cacheState() {
        penCache = qpen;
        brushCache = qbrush;
    }
    void restoreState() {
        qpen = penCache;
        qbrush = brushCache;
    }
    // paint APIs
    QPen qpen;
    QBrush qbrush;

    QColor getPenColor() {return qpen.color();}
    QColor getBrushColor() {return qbrush.color();}
    void setPenColor(QColor color) {qpen.setColor(color);}
    void setBrushColor(QColor color) {qbrush.setColor(color);}
    void setPenWidth(int width){qpen.setWidth((width));}
    void setBrushWidth(int width){brushSize = static_cast<qreal>(width);}
    void setBrush(const QBrush &brush);

    QRectF paintTablet(const QTabletEvent &tablet);
    QRectF eraseTablet(const QTabletEvent &tablet, QColor backgroundColor);
    QRectF paintMouse(const QPointF &pos);
    void paintTouch(QRectF rect);
    void paintEllipse(const QRectF &rect);
    void eraseEllipse(const QRectF &rect);
    void paintRect(QRectF rect);
    void eraseRect(QRectF rect);
    void paintLine(QPointF pos1, QPointF pos2);
    void eraseLine(QPointF pos1, QPointF pos2);

private:
    QImage *image;
    QPainter *painter;
    qreal brushSize;
    void updatePainterSetting();
    QColor backgroundColor;
    // do not use explicitly
    QPen penCache;
    QBrush brushCache;
};
#endif // PAINTMANAGER_H
