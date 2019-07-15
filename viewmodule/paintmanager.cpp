#include <QtWidgets>

#include "paintmanager.h"

PaintManager::PaintManager(QImage *image, StrokeMode paintMode) {
    this->painter = new QPainter();
    this->strokeMode = paintMode;
    this->image = image;
    // defaults
    setStrokeMode(STM_FILL);
    this->strokeType = ST_FREE;
    this->qbrush = QBrush(QColor("grey"));
    this->brushSize = 50.0;
}

void PaintManager::setStrokeMode(StrokeMode strokeMode) {
    if (this->strokeType != ST_LINE) {
        this->strokeMode = strokeMode;
    } else {
        this->strokeMode = STM_OUTLINE;
    }
    updatePainterSetting();
}

void PaintManager::updatePainterSetting() {
    switch(strokeMode) {
        case STM_FILL:
            painter->setPen(Qt::NoPen);
            painter->setBrush(qbrush);
            break;
        case STM_OUTLINE:
            painter->setPen(qpen);
            painter->setBrush(Qt::NoBrush);
            break;
        case STM_FILL_OUTLINE:
            painter->setPen(qpen);
            painter->setBrush(qbrush);
            break;
    }
}

void PaintManager::setBackground(QColor background) {
    backgroundColor = background;
}

// for real time rendering
QRectF PaintManager::paintTablet(const QTabletEvent &tablet) {
    qreal len = (brushSize - 5.0) * tablet.pressure();
    QRectF rect = QRectF(tablet.posF().x() - len / 2, tablet.posF().y() - len / 2, len, len);
    if (strokeType == ST_ERASE) {
        eraseEllipse(rect);
    } else {
        paintEllipse(rect);
    }
    return rect;
}

QRectF PaintManager::eraseTablet(const QTabletEvent &tablet, QColor backgroundColor) {
    qreal len = (brushSize - 5.0) * tablet.pressure();
    QRectF rect = QRectF(tablet.posF().x() - len / 2, tablet.posF().y() - len / 2, len, len);
    painter->begin(image);
    QBrush tempBrush = qbrush;
    qbrush = QBrush(backgroundColor);
    updatePainterSetting();
    painter->drawEllipse(rect);
    painter->end();
    qbrush = tempBrush;
    return rect;
}

QRectF PaintManager::paintMouse(const QPointF &pos) {
    QRectF rect = QRectF(pos.x() - brushSize / 2, pos.y() - brushSize / 2, brushSize, brushSize);
    if (strokeType == ST_ERASE) {
        eraseEllipse(rect);
    } else {
        paintEllipse(rect);
    }
    return rect;
}

void PaintManager::paintTouch(QRectF rect) {
    if (strokeType == ST_ERASE) {
        eraseEllipse(rect);
    } else {
        paintEllipse(rect);
    }
}

// for render the whole canvas
void PaintManager::paintEllipse(const QRectF &rect) {
    painter->begin(image);
    updatePainterSetting();
    painter->drawEllipse(rect);
    painter->end();
}

void PaintManager::eraseEllipse(const QRectF &rect) {
    QBrush tempBrush = qbrush;
    qbrush.setColor(backgroundColor);
    paintEllipse(rect);
    qbrush = tempBrush;
}

void PaintManager::paintRect(QRectF rect) {
    painter->begin(image);
    updatePainterSetting();
    painter->drawRect(rect);
    painter->end();
}

void PaintManager::eraseRect(QRectF rect) {
    QBrush tempBrush = qbrush;
    qbrush.setColor(backgroundColor);
    paintRect(rect);
    qbrush = tempBrush;
}

void PaintManager::paintLine(QPointF pos1, QPointF pos2) {
    StrokeMode stm = strokeMode;
    setStrokeMode(STM_OUTLINE);
    painter->begin(image);
    updatePainterSetting();
    painter->drawLine(pos1, pos2);
    painter->end();
    setStrokeMode(stm);
}

void PaintManager::eraseLine(QPointF pos1, QPointF pos2) {
    QBrush tempBrush = qbrush;
    qbrush.setColor(backgroundColor);
    paintLine(pos1, pos2);
    qbrush = tempBrush;
}

Stroke PaintManager::initStroke() {
    Stroke stroke = Stroke();
    stroke.fillColor = qbrush.color();
    stroke.outlineColor = qpen.color();
    stroke.mode = strokeMode;
    stroke.type = strokeType;
    stroke.pen = qpen;
    stroke.brush = qbrush;
    std::cout<<"Initing stroke type: "<<strokeType<<std::endl;
    return stroke;
}

void PaintManager::setBrush(const QBrush &brush)
{
    this->qbrush = brush;

}



