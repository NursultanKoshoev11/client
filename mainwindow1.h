#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class mainwindow1;
}

class mainwindow1 : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow1(QTcpSocket &_socket,QWidget *parent = nullptr);
    ~mainwindow1();

   void sent_to_server();

private:
    Ui::mainwindow1 *ui;
    QTcpSocket *socket;
    qint16 sizeblock = 0;
    qint16 sizepass;
    qint16 sizelogin;
    QByteArray data;
    bool is_server_ready = false;



public slots:
    void but_enter_clicked();
    void but_reg_clicked();
    void read();

signals:
    void enter_info(QString &);

};

#endif // MAINWINDOW1_H
