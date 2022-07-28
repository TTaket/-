#ifndef TOOL_INFO_H
#define TOOL_INFO_H

#include <QWidget>
#include <QThread>
#include <QTimer>
namespace Ui {
class Tool_Info;
}

class Tool_Info : public QWidget
{
    Q_OBJECT

public:
    explicit Tool_Info(QWidget *parent = nullptr);
    ~Tool_Info();
    void showinfo(QString qstr);


private:
    Ui::Tool_Info *ui;
};

#endif // TOOL_INFO_H
