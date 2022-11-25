#include "add_window.h"
#include "ui_add_window.h"
#include <QMessageBox>

add_window::add_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_window)
{
    ui->setupUi(this);
    connect(ui->add_bot,SIGNAL(clicked(bool)),this,SLOT(add_bot()));
    connect(ui->exit_bot,SIGNAL(clicked(bool)),this,SLOT(exit_bot()));
}

void add_window::add_bot(){
    QString number,name,count;
    number = ui->number->text();
    name = ui->name->text();
    count = ui->count->text();

    if(number == "" || name == "" || count == ""){
        QMessageBox::critical(this,"Error","Вы неправильно ввели!",QMessageBox::Ok);
    }
    else {
        emit sent_strings(number,name,count);
    }

}

void add_window::exit_bot(){
    this->deleteLater();
}

add_window::~add_window()
{
    delete ui;
}
