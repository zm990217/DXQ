#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QColorDialog>
#include "canvasmanager.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QButtonGroup;
class QAbstractButton;
class QTableWidget;
class QLabel;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void openKami();
    void saveKami();
    void about();
    void changepenwidth(const int width);
    void changebrushwidth(const int width);
    void changepenstyle();
    void layerbuttonclicked(int id);
    void visiblelayer(int x,int y);
    void changelayer(int x,int y);
    void layertableinit();
    void saveassize();
    void changegraphwidth(const int width);
    void changegraphlength(const int length);

private:
    void createActions();
    void createMenus();
    void createToolbar();
    void createToolbox();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    void insertintolist();

    CanvasManager *canvas;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QMenu *toolMenu;

    QToolBar *pentoolbar;
    QSpinBox *penwidspinbox;
    QSpinBox *brushwidspinbox;
    QComboBox *penstyle;
    QLabel *penstylelabel;
    QSpinBox *graphwidthspinbox;
    QSpinBox *graphlengthspinbox;
    int graphwidth;
    int graphlength;

    QToolBox *layertoolbox;
    QButtonGroup *layerbuttongroup;
    QTableWidget *layertable;
    QLabel *current;
    int layernum;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *openKamiAct;
    QAction *saveKamiAct;
    QAction *exitAct;
    QAction *renderAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *inputModeAct;
    QAction *undoAct;
    QAction *saveasAct;
    // settings
    QAction *penColorAct;
    QAction *brushColorAct;
    QAction *backgroundColorAct;
    QAction *strokeModeAct;
    // stroke type
    QAction *freeAct;
    QAction *rectAct;
    QAction *ellipseAct;
    QAction *diamondAct;
    QAction *lineAct;
    QAction *eraseAct;
};

#endif
