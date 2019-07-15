#include <QtWidgets>
#include "canvasmanager.h"

CanvasManager::CanvasManager(QWidget *parent)
     : QWidget(parent) {
    // basic initialization
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);
    this->paint = new PaintManager(&image);
    layers.append(Layer());
    currentLayer = 0;
    strokeBegin = false;
    strokeEnd = false;
    backgroundColor = QColor("white");
    paint->setBackground(backgroundColor);
    inputMode = IM_CONTINUE;
}

/* SLOTS */
bool CanvasManager::openImage(const QString &filename) {
    QImage loadedImage;
    if (!loadedImage.load(filename))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

/*set width*/ 
void CanvasManager::setwidth(ToolType tool,int width){
    switch (tool) {
    case TT_PEN:{

        paint->setPenWidth(width);
    }
        break;
    case TT_BRUSH:{

        paint->setBrushWidth(width);
    }
        break;
    default:
        break;
    }
}

/*set brushstyle*/
void CanvasManager::setbrushstyle(const QBrush &brush){
    QBrush temp = brush;
    temp.setColor(paint->qbrush.color());
    paint->setBrush(temp);
}

/*set Color*/
void CanvasManager::setColor(ToolType tool) {
    switch (tool) {
    case TT_PEN:{
        QColor color = QColorDialog::getColor(paint->getPenColor(), this, "Choose Pen Color");
        paint->setPenColor(color);
    }
        break;
    case TT_BRUSH:{
        QColor color = QColorDialog::getColor(paint->getBrushColor(), this, "Choose Brush Color");
        paint->setBrushColor(color);
    }
        break;
    case TT_BACKGROUND:{
        QColor color = QColorDialog::getColor(backgroundColor, this, "Choose Background Color");
        backgroundColor = color;
        paint->setBackground(color);
        renderCanvas();
    }
        break;
    }
}

/*set type*/
void CanvasManager::setType(StrokeType st) {
    this->paint->strokeType = st;
    if(st == ST_FREE || st == ST_ERASE) {
        inputMode = IM_CONTINUE;
    } else {
        inputMode = IM_BEGIN_END;
    }
}

/*change stroke mode*/
void CanvasManager::changeStrokeMode() {
    paint->setStrokeMode(paint->strokeMode == STM_OUTLINE ? STM_FILL : (paint->strokeMode == STM_FILL ? STM_FILL_OUTLINE : STM_OUTLINE));
    std::cout<<"Init Stroke Mode:"<<paint->strokeMode<<std::endl;
}

/*save*/
bool CanvasManager::saveImage(const QString &filename, const char *fileFormat) {
    QImage visibleImage = image;
    //resizeImage(&visibleImage,QSize(imagewidth,imagelength));
    visibleImage=image.scaled(imagewidth,imagelength,Qt::KeepAspectRatioByExpanding);
    if (visibleImage.save(filename, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void CanvasManager::loadKami(const QString &fileName) {
    layers.clear();
    FileManager kami(fileName);
    layers = kami.loadKami();
    modified = false;
    backgroundColor = kami.getBackground();
    renderCanvas();
}

void CanvasManager::saveKami(const QString &fileName) {
    FileManager kami(fileName);
    kami.saveKami(layers, backgroundColor);
    modified = false;
}

void CanvasManager::clearImage() {
    // clear the whole image
    image.fill(backgroundColor);
    layers.clear();
    layers.append(Layer());
    currentLayer = 0;
    modified = true;
    update();
}

void CanvasManager::undo() {
    if (!layers.at(currentLayer).data.empty()) {
        std::cout<<"undo... at layer: "<< currentLayer <<std::endl;
        layers[currentLayer].data.removeLast();
        renderCanvas();
    }
}

void CanvasManager::setInputMode() {
    isTablet = isTablet ? false : true;
    // inputMode = (inputMode == IM_CONTINUE) ? IM_BEGIN_END : IM_CONTINUE;
}

void CanvasManager::resizeImage(QImage *image, const QSize &newSize)
{
    std::cout<<"size "<<newSize.width()<<" "<<newSize.height()<<std::endl;
    if (image->size() == newSize)
        return;
    std::cout<<"Resizing"<<std::endl;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void CanvasManager::updateArea(QRectF rect) {
    modified = true;
    int rad = 2;
    update(rect.toRect().adjusted(-rad,-rad, +rad, +rad));
}

void CanvasManager::renderCanvas() {
    if (layers.empty()) {
        image.fill(backgroundColor);
    } else {
        image.fill(backgroundColor);
        for (int i = 0; i < layers.length(); i++) {
            const Layer &la = layers.at(i);
            if (!la.data.empty() && la.visible) {
                for (int j = 0; j < la.data.length(); j++) {
                    const Stroke &st = la.data.at(j);
                    renderStroke(st);
                }
            }
        }
    }
    // render to screen
    update();
}

void CanvasManager::renderStroke(const Stroke &stroke) {
    paint->cacheState();
    paint->qpen = stroke.pen;
    paint->qbrush = stroke.brush;
    switch (stroke.type) {
    case ST_FREE:
        for (int i = 0; i < stroke.data.length(); i++) {
            paint->paintEllipse(stroke.data.at(i));
    }
        break;
    case ST_RECT:{
        QRectF rect(stroke.sStart, stroke.sEnd);
        paint->paintRect(rect);
    }
        break;
    case ST_ELLIPS:{
        QRectF rect(stroke.sStart, stroke.sEnd);
        paint->paintEllipse(rect);
    }
        break;
    case ST_DIAMOND:
        break;
    case ST_LINE:
        paint->paintLine(stroke.sStart, stroke.sEnd);
        break;
    case ST_ERASE:
        paint->setBackground(backgroundColor);
        for (int i = 0; i < stroke.data.length(); i++) {
            paint->eraseEllipse(stroke.data.at(i));
        }
        break;
    }
    paint->restoreState();
}

/* Overrided functions */
void CanvasManager::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    const QRect rect = event->rect();
    painter.drawImage(rect.topLeft(), image, rect);
}

void CanvasManager::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

bool CanvasManager::event(QEvent *event) {
    // handle the events -> strokes
    if (event->type() == QEvent::TouchBegin
            || event->type() == QEvent::TouchUpdate
            || event->type() == QEvent::TouchEnd) {
        const QTouchEvent *touch = static_cast<QTouchEvent *>(event);
        const QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        if (inputMode == IM_CONTINUE) {
            QRectF rect;
            for (const QTouchEvent::TouchPoint &touchPoint : touchPoints) {
                switch (touchPoint.state()) {
                case Qt::TouchPointStationary:
                case Qt::TouchPointReleased:
                    // don't do anything if this touch point hasn't moved or has been released
                    continue;
                default:
                     {
                        rect = touchPoint.rect();
                        if (rect.isEmpty()) {
                            qreal diameter = MAX_BRUSH_DIAMETER;
                            if (touch->device()->capabilities() & QTouchDevice::Pressure)
                                diameter = MAX_BRUSH_DIAMETER + (MAX_BRUSH_DIAMETER - MAX_BRUSH_DIAMETER) * touchPoint.pressure();
                            rect.setSize(QSizeF(diameter, diameter));
                        }
                        paint->paintTouch(rect);
                        updateArea(rect);
                    }
                    break;
                }
            }
            if (event->type() == QEvent::TouchBegin && !strokeBegin) {
                std::cout<<"Touch Stroke Begin: "<<std::endl;
                strokeBegin = true;
                strokeEnd = false;
                tempStroke.append(rect);
            } else if (event->type() == QEvent::TouchEnd && strokeBegin) {
                std::cout<<"Touch Stroke End"<<std::endl;
                strokeBegin = false;
                strokeEnd = true;
            } else if (!strokeEnd && strokeBegin) {
                tempStroke.append(rect);
            }
            if (strokeEnd) {
                Stroke stroke = paint->initStroke();
                stroke.data = tempStroke;
                layers[currentLayer].data.append(stroke);
                tempStroke.clear();
                strokeEnd = false; strokeBegin = false;
            }
        }  else if (inputMode == IM_BEGIN_END) {
            if (event->type() == QEvent::TouchBegin && !strokeBegin) {
                std::cout<<"Stroke Begin: "<<std::endl;
                strokeBegin = true;
                strokeEnd = false;
                sStart = touchPoints.at(0).pos();
            } else if (event->type() == QEvent::TouchEnd && strokeBegin) {
                std::cout<<"Stroke End"<<std::endl;
                strokeBegin = false;
                strokeEnd = true;
                sEnd = touchPoints.at(0).pos();
            } else if (!strokeEnd && strokeBegin) {
                // render temp stroke
                Stroke stroke = paint->initStroke();
                stroke.sStart = sStart;
                stroke.sEnd = touchPoints.at(0).pos();
                renderCanvas();
                renderStroke(stroke);
            }
            if (strokeEnd) {
                Stroke stroke = paint->initStroke();
                stroke.sStart = sStart;
                stroke.sEnd = sEnd;
                layers[currentLayer].data.append(stroke);
                tempStroke.clear();
                strokeEnd = false; strokeBegin = false;
                renderCanvas();
            }
        }
    } else if (isTablet && (event->type() == QEvent::TabletPress
               || event->type() == QEvent::TabletMove
               || event->type() == QEvent::TabletRelease)) {
            const QTabletEvent *tablet = static_cast<QTabletEvent* >(event);
            //std::cout<<"Tablet Pen Pressure "<<tablet->pressure()<<std::endl;
            if (inputMode == IM_CONTINUE) {
                QRectF rect;
                switch (tablet->pointerType()) {
                case QTabletEvent::Pen:{
                    if (tablet->pressure() > 0.0) {
                        rect = paint->paintTablet(*tablet);
                        updateArea(rect);
                    }
                    break;
                }
                case QTabletEvent::Eraser:{
                    if (tablet->pressure() > 0.0) {
                        rect = paint->eraseTablet(*tablet, backgroundColor);
                        updateArea(rect);
                    }
                    break;
                }
                default:
                        break;
                }
                if (event->type() == QEvent::TabletPress && !strokeBegin) {
                    std::cout<<"Tablet Stroke Begin"<<std::endl;
                    strokeBegin = true;
                    strokeEnd = false;
                    tempStroke.append(rect);
                } else if (event->type() == QEvent::TabletRelease && strokeBegin) {
                    std::cout<<"Tablet Stroke End"<<std::endl;
                    strokeBegin = false;
                    strokeEnd = true;
                } else if (!strokeEnd && strokeBegin) {
                    tempStroke.append(rect);
                }
                if (strokeEnd) {
                    Stroke stroke = paint->initStroke();
                    stroke.data = tempStroke;
                    if (tablet->pointerType() == QTabletEvent::Eraser) {
                        stroke.type = ST_ERASE;
                    }
                    layers[currentLayer].data.append(stroke);
                    tempStroke.clear();
                    strokeEnd = false; strokeBegin = false;
                }
            } else if (inputMode == IM_BEGIN_END) {
                if (event->type() == QEvent::TabletPress && !strokeBegin) {
                    std::cout<<"Spos"<<std::endl;
                    strokeBegin = true;
                    strokeEnd = false;
                    sStart = tablet->posF();
                } else if (event->type() == QEvent::TabletRelease && strokeBegin) {
                    std::cout<<"Epos"<<std::endl;
                    strokeBegin = false;
                    strokeEnd = true;
                    sEnd = tablet->posF();
                }  else if (!strokeEnd && strokeBegin) {
                    // render temp stroke at a lower rate than the actuall refresh rate
                    if (tabletFilter <= TABLET_PREVIEW_FILTER_STRENGTH) {
                        tabletFilter ++;
                    } else {
                        tabletFilter = 0;
                        Stroke stroke = paint->initStroke();
                        stroke.sStart = sStart;
                        stroke.sEnd = tablet->posF();
                        renderCanvas();
                        renderStroke(stroke);
                    }
                }
                if (strokeEnd) {
                    Stroke stroke = paint->initStroke();
                    stroke.sStart = sStart;
                    stroke.sEnd = sEnd;
                    layers[currentLayer].data.append(stroke);
                    tempStroke.clear();
                    strokeEnd = false; strokeBegin = false;
                    renderCanvas();
                }
            }
        } else if (!isTablet && (event->type() == QEvent::MouseButtonPress
                   || event->type() == QEvent::MouseMove
                   || event->type() == QEvent::MouseButtonRelease)) {
        const QMouseEvent *mouse = static_cast<QMouseEvent* >(event);
        if (inputMode == IM_CONTINUE) {
            QRectF rect;
            rect = paint->paintMouse(mouse->pos());
            updateArea(rect);
            if (mouse->type() ==  QEvent::MouseButtonPress && mouse->button() == Qt::LeftButton && !strokeBegin) {
                std::cout<<"Mouse Stroke Begin"<<std::endl;
                strokeBegin = true;
                strokeEnd = false;
                tempStroke.append(rect);
            } else if (mouse->type() ==  QEvent::MouseButtonRelease && mouse->button() == Qt::LeftButton && strokeBegin) {
                std::cout<<"Mouse Stroke End"<<std::endl;
                strokeBegin = false;
                strokeEnd = true;
            } else if (!strokeEnd && strokeBegin) {
                tempStroke.append(rect);
            }
            if (strokeEnd) {
                Stroke stroke = paint->initStroke();
                stroke.data = tempStroke;
                layers[currentLayer].data.append(stroke);
                tempStroke.clear();
                strokeEnd = false; strokeBegin = false;
                renderCanvas();
            }
        } else if (inputMode == IM_BEGIN_END) {
            if (mouse->type() ==  QEvent::MouseButtonPress && mouse->button() == Qt::LeftButton && !strokeBegin) {
                std::cout<<"Spos"<<std::endl;
                strokeBegin = true;
                strokeEnd = false;
                sStart = mouse->pos();
            } else if (mouse->type() ==  QEvent::MouseButtonRelease && mouse->button() == Qt::LeftButton && strokeBegin) {
                std::cout<<"Epos"<<std::endl;
                strokeBegin = false;
                strokeEnd = true;
                sEnd = mouse->pos();
            }  else if (!strokeEnd && strokeBegin) {
                // render temp stroke
                Stroke stroke = paint->initStroke();
                stroke.sStart = sStart;
                stroke.sEnd = mouse->pos();
                renderCanvas();
                renderStroke(stroke);
            }
            if (strokeEnd) {
                Stroke stroke = paint->initStroke();
                stroke.sStart = sStart;
                stroke.sEnd = sEnd;
                layers[currentLayer].data.append(stroke);
                tempStroke.clear();
                strokeEnd = false; strokeBegin = false;
            }
        }
    } else {
        return QWidget::event(event);
    }
    return true;
}

int CanvasManager::createnewlayer(){
    Layer *newitem = new Layer;
    layers.append(*newitem);
    currentLayer = layers.count()-1;
    return currentLayer;
}

void CanvasManager::deletelayer(int index){
    Layer *temp;
    setcurrentlayer(0);
    printf("delete one\n");
    temp=&layers[index];
    layers.remove(index);
    renderCanvas();
}

void CanvasManager::setcurrentlayer(int index){
    currentLayer=index;
    printf("current layer: %d\n",index);
}

void CanvasManager::setvisible(int index,bool flag){

    layers[index].visible=flag;
    renderCanvas();
}

int CanvasManager::getlayerscount(){
    return layers.count();
}
