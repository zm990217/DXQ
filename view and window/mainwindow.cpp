#include <QtWidgets>

#include "mainwindow.h"
#include "stroke.h"

const int IdRole = Qt::UserRole;

MainWindow::MainWindow() {
    canvas = new CanvasManager();

    canvas->saveasflag=true;
    layernum = 1;
    createActions();
    createMenus();
    createToolbar();


    createToolbox();


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(canvas);
    layout->addWidget(layertoolbox);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("OhKami!"));
    resize(500, 500);
}



void MainWindow::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            canvas->openImage(fileName);
    }
}

void MainWindow::save() {
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::openKami() {
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Open Kami File"), QDir::currentPath());
    if(!fileName.isEmpty()) {
        canvas->loadKami(fileName);
        layertableinit();
    }
}

void MainWindow::saveKami() {
    QString initialPath = QDir::currentPath() + "/untitled." + "kami";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As Kami"),
                                  initialPath);
    if (!fileName.isEmpty()) {
       canvas->saveKami(fileName);
    }
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About OhKami!"),
            tr("<p>OhKami is paint program that let you paint.</p>"));
}

void MainWindow::createActions() {
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : imageFormats) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActs.append(action);
    }

    saveKamiAct = new QAction(tr("Save as &Kami"), this);
    connect(saveKamiAct, &QAction::triggered, this, &MainWindow::saveKami);
    openKamiAct = new QAction(tr("Open Kami"), this);
    connect(openKamiAct, &QAction::triggered, this, &MainWindow::openKami);

    renderAct = new QAction(tr("&Render"), this);
    renderAct->setShortcut(tr("Ctrl+R"));
    connect(renderAct, &QAction::triggered, canvas, &CanvasManager::renderCanvas);

    inputModeAct = new QAction(tr("&ChangeInputMode"), this);
    inputModeAct->setShortcut(tr("Ctrl+I"));
    connect(inputModeAct, &QAction::triggered, canvas, &CanvasManager::setInputMode);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcut(tr("Ctrl+Z"));
    connect(undoAct, &QAction::triggered, canvas, &CanvasManager::undo);

    penColorAct = new QAction(QIcon(":/images/color"),tr("Set Pen Color"), this);
    penColorAct->setShortcut(tr("Ctrl+P"));
    connect(penColorAct, &QAction::triggered, canvas, [=](){canvas->setColor(TT_PEN);});
    brushColorAct = new QAction(QIcon(":/images/brush"),tr("Set Brush Color"), this);
    brushColorAct->setShortcut(tr("Ctrl+B"));
    connect(brushColorAct, &QAction::triggered, canvas, [=](){canvas->setColor(TT_BRUSH);});
    backgroundColorAct = new QAction(tr("Set Background Color"), this);
    backgroundColorAct->setShortcut(tr("Ctrl+D"));
    connect(backgroundColorAct, &QAction::triggered, canvas, [=](){canvas->setColor(TT_BACKGROUND);});

    strokeModeAct = new QAction(tr("Change Stroke Mode"), this);
    strokeModeAct->setShortcut(tr("Ctrl+M"));
    connect(strokeModeAct, &QAction::triggered, canvas, &CanvasManager::changeStrokeMode);

    freeAct = new QAction(tr("&Brush"), this);
    freeAct->setShortcut(tr("Ctrl+1"));
    connect(freeAct, &QAction::triggered, canvas, [=](){canvas->setType(ST_FREE);});
    rectAct = new QAction(tr("&Rectangle"), this);
    rectAct->setShortcut(tr("Ctrl+2"));
    connect(rectAct, &QAction::triggered, canvas, [=](){canvas->setType(ST_RECT);});
    ellipseAct = new QAction(tr("&Ellipse"), this);
    ellipseAct->setShortcut(tr("Ctrl+3"));
    connect(ellipseAct, &QAction::triggered, canvas, [=](){canvas->setType(ST_ELLIPS);});
    diamondAct = new QAction(tr("&Diamond"), this);
    diamondAct->setShortcut(tr("Ctrl+4"));
    connect(diamondAct, &QAction::triggered, canvas, [=](){canvas->setType(ST_DIAMOND);});
    lineAct = new QAction(tr("&Line"), this);
    lineAct->setShortcut(tr("Ctrl+5"));
    connect(lineAct, &QAction::triggered, canvas, [=](){canvas->setType(ST_LINE);});
    eraseAct = new QAction(QIcon(":/images/eraser"),tr("&Eraser"), this);
    eraseAct->setShortcut(tr("Ctrl+6"));
    connect(eraseAct, &QAction::triggered, canvas, [=](){canvas->setType(ST_ERASE);});


    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, &QAction::triggered,
            canvas, &CanvasManager::clearImage);

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);


}

void MainWindow::createToolbar(){
    pentoolbar = addToolBar(tr("pen"));
    pentoolbar->addAction(penColorAct);

    QLabel *blank1 = new QLabel(tr("  "));
    QLabel *blank2 = new QLabel(tr("  "));
    QLabel *blank3 = new QLabel(tr("  "));
    QLabel *blank4 = new QLabel(tr("  "));
    QLabel *blank5 = new QLabel(tr("  "));
    QLabel *blank6 = new QLabel(tr("  "));
    QLabel *blank7 = new QLabel(tr("  "));
    QLabel *penlabel = new QLabel(tr("penwidth :"));
    QLabel *brushlabel = new QLabel(tr("brushwidth :"));
    QLabel *graphwidthlabel = new QLabel(tr("graphlength :"));
    QLabel *graphlengthlabel = new QLabel(tr("graphwidth :"));

    penwidspinbox = new QSpinBox;
    penwidspinbox->setRange(0,30);
    penwidspinbox->setValue(10);
    connect(penwidspinbox,SIGNAL(valueChanged(int)),this,SLOT(changepenwidth(int)));

    brushwidspinbox = new QSpinBox;
    brushwidspinbox->setRange(0,150);
    brushwidspinbox->setValue(50);
    connect(brushwidspinbox,SIGNAL(valueChanged(int)),this,SLOT(changebrushwidth(int)));

    graphwidthspinbox = new QSpinBox;
    graphwidthspinbox->setRange(0,3000);
    graphwidthspinbox->setValue(800);
    canvas->imagewidth= 800;
    connect(graphwidthspinbox,SIGNAL(valueChanged(int)),this,SLOT(changegraphwidth(int)));

    graphlengthspinbox = new QSpinBox;
    graphlengthspinbox->setRange(0,2000);
    graphlengthspinbox->setValue(600);
    canvas->imagelength = 600;
    connect(graphlengthspinbox,SIGNAL(valueChanged(int)),this,SLOT(changegraphlength(int)));

    penstyle = new QComboBox;
    penstyle->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    penstyle->addItem(tr("Linear Gradient"),
            static_cast<int>(Qt::LinearGradientPattern));
    penstyle->addItem(tr("Radial Gradient"),
            static_cast<int>(Qt::RadialGradientPattern));
    penstyle->addItem(tr("Conical Gradient"),
            static_cast<int>(Qt::ConicalGradientPattern));
    penstyle->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    penstyle->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    penstyle->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    penstyle->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    penstyle->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    penstyle->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    penstyle->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    penstyle->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    penstyle->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    penstyle->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    penstyle->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    penstyle->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    penstyle->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    penstyle->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    penstyle->addItem(tr("None"), static_cast<int>(Qt::NoBrush));
    penstylelabel = new QLabel(tr("&style:"));
    penstylelabel->setBuddy(penstyle);
    connect(penstyle, SIGNAL(activated(int)),
            this, SLOT(changepenstyle()));
    pentoolbar->addWidget(blank1);
    pentoolbar->addWidget(penlabel);
    pentoolbar->addWidget(penwidspinbox);
    pentoolbar->addWidget(blank2);
    pentoolbar->addAction(brushColorAct);
    pentoolbar->addWidget(blank4);
    pentoolbar->addWidget(brushlabel);
    pentoolbar->addWidget(brushwidspinbox);
    pentoolbar->addWidget(blank3);
    pentoolbar->addWidget(penstyle);
    pentoolbar->addWidget(blank5);
    pentoolbar->addAction(eraseAct);
    pentoolbar->addWidget(blank6);
    pentoolbar->addWidget(graphwidthlabel);
    pentoolbar->addWidget(graphwidthspinbox);
    pentoolbar->addWidget(blank7);
    pentoolbar->addWidget(graphlengthlabel);
    pentoolbar->addWidget(graphlengthspinbox);

}

void MainWindow::createToolbox(){


    QVBoxLayout *layout = new QVBoxLayout;

    layertable = new QTableWidget;
    layertable->setColumnCount(2);
    layertable->setRowCount(1);
    layertable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layertable->resizeColumnToContents(1);


    QStringList headers;
    headers<<"num"<<"vis";
    layertable->setHorizontalHeaderLabels(headers);
    QString s = QString("layer")+QString::number(1);
    layertable->setItem(0,0,new QTableWidgetItem(QString(s)));
    QTableWidgetItem *checkBox = new QTableWidgetItem();
    checkBox->setCheckState(Qt::Checked);
    layertable->setItem(0,1,checkBox);
    canvas->setvisible(0,true);
    layout->addWidget(layertable,0);
    connect(layertable,SIGNAL(cellChanged(int,int)),this,SLOT(visiblelayer(int,int)));
    connect(layertable,SIGNAL(cellClicked(int,int)),this,SLOT(changelayer(int,int)));



    QGridLayout *iconslayout = new QGridLayout;
    layerbuttongroup = new QButtonGroup(this);
    layerbuttongroup->setExclusive(false);
    connect(layerbuttongroup,SIGNAL(buttonClicked(int)),this,SLOT(layerbuttonclicked(int)));

    QToolButton *newbutton = new QToolButton;
    newbutton->setCheckable(true);
    layerbuttongroup->addButton(newbutton,0);
    newbutton->setIcon(QIcon(QPixmap(":/images/create")));
    newbutton->setIconSize(QSize(50,50));
    QGridLayout *newlayout = new QGridLayout;
    newlayout->addWidget(newbutton, 0, 0, Qt::AlignHCenter);
    newlayout->addWidget(new QLabel(tr("create")), 1, 0, Qt::AlignCenter);
    QWidget *newWidget = new QWidget;
    newWidget->setLayout(newlayout);
    iconslayout->addWidget(newWidget,0,0);

    QToolButton *downbutton = new QToolButton;
    downbutton->setCheckable(true);
    layerbuttongroup->addButton(downbutton,1);
    downbutton->setIcon(QIcon(QPixmap(":/images/delete")));
    downbutton->setIconSize(QSize(50,50));
    QGridLayout *downlayout = new QGridLayout;
    downlayout->addWidget(downbutton, 0, 0, Qt::AlignHCenter);
    downlayout->addWidget(new QLabel(tr("delete")), 1, 0, Qt::AlignCenter);
    QWidget *downWidget = new QWidget;
    downWidget->setLayout(downlayout);
    iconslayout->addWidget(downWidget,0,1);

    QWidget *icons = new QWidget;
    icons->setLayout(iconslayout);
    layout->addWidget(icons,1);

    current= new QLabel(tr("current:1"));
    layout->addWidget(current,2);

    layout->setStretch(0,10);
    layout->setStretch(1,3);
    layout->setStretch(2,2);

    QWidget *all = new QWidget;
    all->setLayout(layout);


    layertoolbox = new QToolBox;
    layertoolbox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    layertoolbox->setMinimumWidth(all->sizeHint().width());
    layertoolbox->addItem(all, tr("layers"));
   }



void MainWindow::createMenus() {
    saveAsMenu = new QMenu(tr("&Save As"), this);
    saveAsMenu->addActions(saveAsActs);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(openKamiAct);
    fileMenu->addAction(saveKamiAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);


    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(clearScreenAct);
    optionMenu->addAction(undoAct);
    optionMenu->addSeparator();
    optionMenu->addAction(renderAct);
    optionMenu->addAction(inputModeAct);
    optionMenu->addSeparator();
    optionMenu->addAction(freeAct);
    optionMenu->addAction(rectAct);
    optionMenu->addAction(ellipseAct);
    optionMenu->addAction(diamondAct);
    optionMenu->addAction(lineAct);
    optionMenu->addAction(eraseAct);
    optionMenu->addSeparator();
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(brushColorAct);
    optionMenu->addAction(backgroundColorAct);
    optionMenu->addAction(strokeModeAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave() {
    if (canvas->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat) {
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return canvas->saveImage(fileName, fileFormat.constData());
    }
}

void MainWindow::changepenwidth(const int width){
    canvas->setwidth(TT_PEN,width);
}

void MainWindow::changebrushwidth(const int width){
    canvas->setwidth(TT_BRUSH,width);
}

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

void MainWindow::layerbuttonclicked(int id){
    int index;
    QList<QAbstractButton *> buttons = layerbuttongroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (layerbuttongroup->button(id) != button)
            button->setChecked(false);
    }
    if (id == 0) {


        index=canvas->createnewlayer();
        insertintolist();
        QString s = QString("current:layer")+QString::number(layertable->rowCount());
        current->setText(s);
    }
    else if (id ==1) {

        index=layertable->currentRow();
        canvas->deletelayer(index);
        layertable->removeRow(index);
        canvas->setcurrentlayer(0);
        QString s = QString("current:")+QString::number(1);
        current->setText(s);
    }
}

void MainWindow::insertintolist(){
    int row;
    layernum++;
    row=layertable->rowCount();
    layertable->insertRow(row);
    QString num = QString::number(layernum);
    QString s = "layer"+num;
    layertable->setItem(row,0,new QTableWidgetItem(s));
    QTableWidgetItem *checkBox = new QTableWidgetItem();
    checkBox->setCheckState(Qt::Checked);
    layertable->setItem(row,1,checkBox);
}

void MainWindow::visiblelayer(int x,int y){
    if(y==0) return;
    if(layertable ->item(x,y)->checkState() == Qt::Checked)
           canvas->setvisible(x,true);
    else {
         canvas->setvisible(x,false);
    }
}

void MainWindow::changelayer(int x,int y){
    if(y==0){

        canvas->setcurrentlayer(x);
    }
    QString s = QString("current:")+QString::number(x+1);
    current->setText(s);
}

void MainWindow::layertableinit(){
    int i,num=canvas->getlayerscount();
    layernum=0;
    for(i=1;i<num;i++){
        insertintolist();
    }

}

void MainWindow::changegraphwidth(const int width){
    canvas->imagewidth =width;
}

void MainWindow::changegraphlength(const int length){
    canvas->imagelength= length;
}

void MainWindow::saveassize(){
    canvas->saveasflag=true;
    printf("set flag\n");
}
