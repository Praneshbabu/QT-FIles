#include "dialog.h"
#include "ui_dialog.h"
#include<QtSerialPort>
#include<QSerialPortInfo>
#include<QDebug>
#include<QtWidgets>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    arduino_is_available = false;
    arduino_port_name="";
    arduino =new QSerialPort;
    serialBuffer="";

    qDebug()<<"Available ports:"<<QSerialPortInfo::availablePorts().length();

    qDebug() <<"Number of ports: " <<QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            qDebug() << "Description: " << serialPortInfo.description() << "\n";
            qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
            qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
        }


    foreach(const QSerialPortInfo&serialPortInfo,QSerialPortInfo::availablePorts()){
    if(serialPortInfo.hasVendorIdentifier()&&serialPortInfo.hasProductIdentifier()){
        if(serialPortInfo.vendorIdentifier()==arduino_uno_vendor_id){
            if(serialPortInfo.productIdentifier()==arduino_uno_product_id){
                arduino_port_name=serialPortInfo.portName();
                arduino_is_available=true;
            }
        }
    }
}



if(arduino_is_available){
    //configuring the port
    arduino->setPortName(arduino_port_name);
    arduino->open(QSerialPort::ReadOnly);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    QObject::connect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));

}else{
    //giving an error message
    qDebug()<<"couldn't find the arduino.\n";
    QMessageBox::warning(this,"port error","couldn't find Arduino");

}
}

Dialog::~Dialog()
{    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}
void Dialog::readSerial(){
//    qDebug()<<"Serialport Works";
//    serialData=arduino->readAll();
//    serialBuffer+=QString::fromStdString(serialData.toStdString());
//    qDebug()<<serialBuffer;

        QStringList bufferSplit=serialBuffer.split(",");
        if(bufferSplit.length()<3){
            serialData=arduino->readAll();
            serialBuffer+=QString::fromStdString(serialData.toStdString());

        }else{
            qDebug()<<bufferSplit;
            Dialog::updateLCD(bufferSplit[1]);
            serialBuffer="";

        }



}
void Dialog::updateLCD(const QString sensor_reading){
    ui->lcdNumber->display(sensor_reading);
}

