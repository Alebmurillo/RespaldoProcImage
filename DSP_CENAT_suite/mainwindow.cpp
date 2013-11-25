#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    this->ptrScene = new QGraphicsScene;
    this->ptrSceneVideo = new QGraphicsScene;
    this->ptrController = new Controller();
    this->ui->setupUi(this);
    connect(ui->actionOtro_Abrir, SIGNAL(triggered()), this, SLOT(on_mnOpenImage_clicked()));

}

void MainWindow::showImage(QImage* qImage){
     QPixmap pixMap = QPixmap::fromImage(*qImage);
     this->ptrScene->clear();
     this->ptrScene->addPixmap(pixMap);
     this->ui->imgDisplay->setScene(this->ptrScene);
     this->ui->imgDisplay->show();

}

void MainWindow::showVideoImage(QImage* qImage){
    QPixmap pixMap = QPixmap::fromImage(*qImage);
    this->ptrSceneVideo->clear();
    this->ptrSceneVideo->addPixmap(pixMap);
    this->ui->videoDisplay->setScene(this->ptrSceneVideo);
    this->ui->videoDisplay->show();
    this->ui->centralwidget->repaint();
}

MainWindow::~MainWindow(){
    delete ui;
    delete this->ptrController;
}

void MainWindow::on_pushButton_clicked(){
    try{
        this->ptrController->applyBilateral();
        QImage* qImage = this->ptrController->getImage()->getQImage();
        showImage(qImage);
    }
    catch(Controller::ControllerException contExc){
        cout << contExc.what() << endl;
    }
}
void MainWindow::on_mnOpenImage_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Files (*.*)"));
    if(fileName != NULL){
        string nameStd = fileName.toStdString();
        char *ptrName = new char[nameStd.size() + 1];
        ptrName[nameStd.size()] = 0;
        memcpy(ptrName, nameStd.c_str(), nameStd.size());
        cout << "Image to load: " << ptrName << endl;
        this->ptrController->loadImage(ptrName);
        QImage* qImage = this->ptrController->getImage()->getQImage();
        showImage(qImage);
    }
}

void MainWindow::on_btn_def_img_clicked(){
    try{        
        this->ptrController->loadImage(DEF_IMAGE);
        QImage* qImage = this->ptrController->getImage()->getQImage();
        showImage(qImage);
    }
    catch(Controller::ControllerException contExc){
        cout << contExc.what() << endl;
    }
}

void MainWindow::on_btnDefaultVideo_clicked(){
    try{
        this->ptrController->loadVideo(DEF_VIDEO);
        QImage* qImage = this->ptrController->getVideo()->getQImage();
        showVideoImage(qImage);
    }
    catch(Controller::ControllerException contExc){
        cout << contExc.what() << endl;
    }
}

void MainWindow::on_btnHog_clicked(){
    QString fileName = "../input/videos/piso.mp4";
    this->ptrController->playVideoHog(fileName);
}

void MainWindow::on_btn_blockProcedure_clicked()
{
    this->ptrController->playVideoSegmented();
}


void MainWindow::on_btnMainFlow_clicked(){
    this->ptrController->processVideo();

}
