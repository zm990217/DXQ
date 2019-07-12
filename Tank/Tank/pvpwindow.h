#ifndef PVPWINDOW_H
#define PVPWINDOW_H

#include <QWidget>

namespace Ui {
class PVPWindow;
}

class PVPWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PVPWindow(QWidget *parent = 0);
    void sendSlot();
    ~PVPWindow();
signals:
    void signalBack();
private:
    Ui::PVPWindow *ui;
};

#endif // PVPWINDOW_H
