#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void readSerial();
    void updateLCD(const QString);

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
        static const quint16 arduino_uno_product_id = 67;
        QString arduino_port_name;
        bool arduino_is_available;
        QByteArray serialData;
        QString serialBuffer;
};
#endif // DIALOG_H
