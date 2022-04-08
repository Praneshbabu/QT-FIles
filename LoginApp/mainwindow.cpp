#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/pranesh/Desktop/index.png");
    ui->label_pic->setPixmap(pix);
    ui->statusbar->addPermanentWidget(ui->label_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoginButton_clicked()
{
    QString username=ui->UserName->text();
    QString password=ui->Password->text();
    if(username =="Pranesh" && password== "pranesh"){
        if(ui->checkBox->isChecked()){
        QMessageBox();QMessageBox::information(this,"Login Information","Login Sucessful and Password Saved");
        ui->statusbar->showMessage("Login Sucessful",2000);
        dialog=new QDialog(this);
        dialog->show();
        }else{
            QMessageBox();QMessageBox::information(this,"Login Information","Login Sucessful and Password not Saved");
            ui->statusbar->showMessage("Login Sucessful",2000);
        }

    }else{
        QMessageBox();QMessageBox::warning(this,"Login Error","Username and Password does not match");
    }


}

