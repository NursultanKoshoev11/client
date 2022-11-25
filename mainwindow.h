#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QLabel>
#include <mainwindow1.h>
#include <QStandardItemModel>
#include "add_window.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    mainwindow1 *second_window;
    QString access;

    QByteArray data;
    qint16 sizeblock = 0;
    QVector<QString> list_string;
    add_window *ad_window;

    QTcpSocket *socket;

    void sent_to_server(QString str);



public slots:
    void enter_info(QString &);
    void read_server();
    void bot_delete();
    void bot_add();
    void get_strings(QString,QString,QString);
};
#endif // MAINWINDOW_H
