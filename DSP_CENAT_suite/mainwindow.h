#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "controller.h"
#include "includes.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
     QTimer _timer;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Controller* ptrController;
    QGraphicsScene* ptrScene;
    QGraphicsScene* ptrSceneVideo;
private slots:
    void showImage(QImage* qImage);
    void showVideoImage(QImage* qImage);
    void on_mnOpenImage_clicked();
    void on_pushButton_clicked();
    void on_btn_def_img_clicked();

    void on_btnDefaultVideo_clicked();

    void on_btnHog_clicked();

    void on_btn_blockProcedure_clicked();

    void on_btnMainFlow_clicked();

private:
    Ui::MainWindow *ui;
};

#endif
