#include "mainwindow1.h"
#include "ui_mainwindow1.h"


mainwindow1::mainwindow1(QTcpSocket &_socket,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow1)
{
    ui->setupUi(this);
    this->socket = &_socket;

    this->resize(600,500);

    this->setFixedWidth(450);
    this->setFixedHeight(550);

    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));

    connect(ui->button_enter,SIGNAL(clicked(bool)),this,SLOT(but_enter_clicked()));
    connect(ui->button_reg,SIGNAL(clicked(bool)),this,SLOT(but_reg_clicked()));


    socket->connectToHost("127.0.0.1",2002);

    if(!is_server_ready){
        ui->info_label_enter->setText("Нет подключение к серверу!");
        ui->info_label_reg->setText("Нет подключение к серверу!");
    }
}

void mainwindow1::but_enter_clicked(){
    if(is_server_ready){
        sent_to_server();
    }
}

void mainwindow1::but_reg_clicked(){
    if(is_server_ready){
        QString login = ui->reg_login_line->text();
        QString pass = ui->reg_pass_line->text();
        QString reg = "reg";
        data.clear();
        QDataStream out(&data,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_3);
        out<<qint16(0)<<reg<<login<<pass;
        out.device()->seek(0);
        out<<qint16(data.size()-sizeof(qint16));
        socket->write(data);
    }
}


void mainwindow1::read(){
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_3);
    if(in.status()==QDataStream::Ok){
        for(;;){
            if(sizeblock==0){
                if(socket->bytesAvailable()<2){
                    break;
                }
                in>>sizeblock;
            }
            if(socket->bytesAvailable()<sizeblock){
                break;
            }
            QString answer,access;
            in>>answer;
            sizeblock = 0;
            if(answer == "reg_success"){
                ui->info_label_reg->setText("Успешная регистрация");
                break;
            }
            if(answer == "reg_no_success"){
                ui->info_label_reg->setText("Такой пользователь уже существует");
                break;
            }
            if(answer == "ok"){
                in>>access;
                emit enter_info(access);
                break;
            }
            if(answer != "serverready"){
                ui->info_label_enter->setText("Нет подключение к серверу!");
                ui->info_label_reg->setText("Нет подключение к серверу!");
            }
            else {
                ui->info_label_enter->setText("Сервер готов!");
                ui->info_label_reg->setText("Сервер готов!");
                is_server_ready = true;
            }
            break;
        }
    }
    else {
        qDebug()<<"not";
    }
}


void mainwindow1::sent_to_server(){
    QString login = ui->login_line->text();
    QString pass = ui->pass_line->text();

    sizelogin = qint16(login.size());
    sizepass = qint16(pass.size());

    data.clear();

    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out<<qint16(0)<<login<<pass;
    out.device()->seek(0);
    out<<qint16(data.size()-sizeof(qint16));
    socket->write(data);
}

mainwindow1::~mainwindow1()
{
    delete ui;
}


