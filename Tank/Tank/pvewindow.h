#ifndef PVEWINDOW_H
#define PVEWINDOW_H

#include <QWidget>

namespace Ui {
class PVEWindow;
}

class PVEWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PVEWindow(QWidget *parent = 0);
    void sendSlot();
    ~PVEWindow();
signals:
    void signalBack();
private:
    Ui::PVEWindow *ui;
};

#endif // PVEWINDOW_H
