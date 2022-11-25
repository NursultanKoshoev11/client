#ifndef ADD_WINDOW_H
#define ADD_WINDOW_H

#include <QWidget>

namespace Ui {
class add_window;
}

class add_window : public QWidget
{
    Q_OBJECT

public:
    explicit add_window(QWidget *parent = nullptr);
    ~add_window();

private:
    Ui::add_window *ui;

signals:
    void sent_strings(QString,QString,QString);

public slots:
    void add_bot();
    void exit_bot();
};

#endif // ADD_WINDOW_H
