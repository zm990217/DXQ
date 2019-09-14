# 图形编辑器项目设计说明

## 需求分析以及实现

### 图形编辑器的要求

#### 基本目标

友好的图形用户界面
图片文件的读取与保存
各种图形元素的绘制，包括直线、曲线、几何图形等
支持橡皮擦
边框线条颜色设置与色彩填充
支持不同类型的画笔（铅笔、钢笔等）、刷子，不同粗细的线条。支持插入文字。 
支持图层，支持保存为包含图层信息的工程文件。保存时支持修改图片质量。

#### 实现关键点

表示图形元素及图形文件的数据结构 
图形编辑时鼠标运动的捕获和计算 
如何生成不同类型画笔的效果 
表示图层的数据结构 
对JPG、BMP等主流图像文件类型的兼容问题

### 模型的架构

主要分为view,viewmodule以及module三个部分，app，windows以及common层由于qt自身的便捷性被我们简化了。module部分为图形存储的内部结构，event事件的实现等等部分，view则负责图画的显示以及图层的分布，viewmodule则作为两者的连接。

### 图形编辑器的功能

基本实现了所有的基本目标和高级目标功能。基本目标中，能够支持对基本的图片格式如BMP、JPG、PNG等的保存和读取，能够绘制直线、曲线和基本的几何图形等，能够支持橡皮擦与清屏，能够设置线条或背景颜色及色彩填充。高级目标中，能够对画笔的类型进行更改，使用不同粗细的线条及纹理，能够支持图层，并且支持图层的隐藏，添加和删除，能够支持保存和读入格式为.kami的工程文件，并且额外支持撤回功能及触控笔输入模式。

## 总体设计

系统模块说明：详细请见个人报告

### 图形编辑器的界面

### 图形编辑器的绘制管理

```c++
PaintManager::PaintManager(QImage *image, StrokeMode paintMode) {  
	    this->painter = new QPainter();  
	    this->strokeMode = paintMode;  
	    this->image = image;  
       // for test only  
	    setStrokeMode(STM_FILL);  
	    this->strokeType = ST_FREE;  
	    this->qbrush = QBrush(QColor("grey"));  
	    this->brushSize = 150.0;  
	}  
```

### 图形编辑器的画布管理
```c++
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
```

## 系统设计难点及解决

### 表示图形元素和图形文件的数据结构

将笔画存为stroke,利用qt自带的qpen记录笔刷的起始和结束位置，笔刷的种类和颜色。定义stroke类。最终依次渲染到图层上

```c++
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
 
```

### 图形编辑时鼠标运动的捕获和计算

```c++
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
```
同时我们还增加了对触控笔和手写的支持。QT分别带有对手写和触控笔的event，甚至能够做到压力感应。

### 生成不同类型画笔效果
我们采用了QT中的Qtbrushstrle来设置不同笔刷的效果，QTbrushstyle是笔刷形式的内部填充物，十分的丰富，还可以自己加入图片实现纹理。

```c++
void MainWindow::changepenstyle(){
    Qt::BrushStyle style = Qt::BrushStyle(penstyle->itemData(
            penstyle->currentIndex(), IdRole).toInt());

    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::black);
        canvas->setbrushstyle(linearGradient);
    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::black);
        canvas->setbrushstyle(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::black);
        canvas->setbrushstyle(conicalGradient);
    } else if (style == Qt::TexturePattern) {
        canvas->setbrushstyle(QBrush(QPixmap(":/images/color")));
    } else {
        canvas->setbrushstyle(QBrush(Qt::green, style));
    }
}

```

### 表示图层的数据结构

我们的设想是图层将由一个个笔画来构成，笔画的向量集构成图层。同时在图层里设置变量visible，只有当选择可见的时候才将图层渲染到画布上。将图层同样以向量layers记录，可以将图层一层层渲染到图画上实现图层的绘制。

```c++
class Layer
{
public:
    bool visible;
    BlendingMode blendingMode;
    QVector<Stroke> data;
};
```

## 效果图

### 示例图

![pic1](https://github.com/zm990217/DXQ/blob/master/doc/demo.jpg)

### 界面

![pic2](https://github.com/zm990217/DXQ/blob/master/doc/1.png)

### 选项菜单
![pic3](https://github.com/zm990217/DXQ/blob/master/doc/2.png)

### 图层界面
![pic4](https://github.com/zm990217/DXQ/blob/master/doc/3.png)



## 总结

本次的大作业让我们对c++的面向对象和类有了更深层次的理解，将一个大程序拆分成不同的对象来进行实现。而不同于以前我们所使用的c语言的流程式结构。显然面向对象更加适合人类的理解方式，更便于书写。但是实际上的对象的设计仍然是有一定的难度的。需要对这个项目有足够深入的认识。同时这次的项目也让我们接触到了QT这个十分便利的工具。QT自带很好的GUI支持和对图形绘制的支持，还有丰富的样例供我们参考。为我们的工作提供了极大的便利。使我们能够在较为有限的时间里完成这个项目。其中qt的信号槽机制尤为突出，极大地便利了图形化界面的实施。每一个GUI的部件都可以很便利地同后端建立连接。Qt所提供的开发框架也非常的强大，特别是QDataStream 能基本序列化Qt所有的基本类型和部分容器和类，可以非常高效的将内存中的数据持久化，并且不需要手动的读取byte再输出。


另外的遗憾是，我们的开发过程是艰辛的，在听课过程中，我们并没有很好的理解MVVM框架的具体架构，没有达到以MVVM模式框架进行开发的高效，在开发的过程中走了很多的弯路。在今后的学习中，我们不仅要学习各种理论知识，还要学习更多团队开发的技巧，学会更好的与他人合作。



