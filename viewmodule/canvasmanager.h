#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H
#include <QImage>
#include <QWidget>
#include <QPainter>
#include <iostream>

#include "paintmanager.h"
#include "filemanager.h"
#include "layer.h"

enum InputMode {
    IM_CONTINUE,
    IM_BEGIN_END
};

enum ToolType{
    TT_PEN,
    TT_BRUSH,
    TT_BACKGROUND
};

class CanvasManager : public QWidget
{
     Q_OBJECT // required for classes that need signals and slots

public:
    CanvasManager(QWidget *parent = nullptr);
    bool openImage(const QString &filename);
    bool saveImage(const QString &filename, const char *fileFormat);
    bool isModified() const {return modified;}
    void setBackground(QColor color) {
        backgroundColor = color; 
        paint->setBackground(color);
    }
    void saveKami(const QString &fileName);
    void loadKami(const QString &fileName);
    int createnewlayer();
    void deletelayer(int index);
    void setcurrentlayer(int index);
    void setvisible(int index,bool flag);
    int getlayerscount();
    void saveresize(int x,int y);
    bool saveasflag;
    int imagewidth;
    int imagelength;

public slots:
    void clearImage();
    void renderCanvas(); // render the whole canvas layer by layer
    void setInputMode();
    void undo();
    void setType(StrokeType st);
    void setColor(ToolType tool);
    void changeStrokeMode();
    void setwidth(ToolType tool,int width);
    void setbrushstyle(const QBrush &brush);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    bool event(QEvent *event) override;

private:
    QImage image;  // the base drawing target
    bool modified; // whether the canvas is modified
    PaintManager *paint;
    QColor backgroundColor; // backgroundColor (also the eraser color)
    QVector<Layer> layers;
    QVector<QRectF> tempStroke;
    bool strokeBegin, strokeEnd;
    int currentLayer;
    InputMode inputMode;
    QPointF sStart, sEnd;
    int tabletFilter = 0;
    bool isTablet = false;
    bool penPressed = false;
    void resizeImage(QImage *image, const QSize &newSize);
    void updateArea(QRectF rect);
    void renderStroke(const Stroke &stroke);
};

#endif // CANVASMANAGER_H
