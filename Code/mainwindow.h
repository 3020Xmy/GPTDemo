#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NetWork.h"
#include <QMainWindow>
#include <QRegularExpressionMatch>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    MainWindow(QWidget *parent = nullptr);
    //解析回复语句
    void handle_GetAnswerText(const QString &text);

private slots:
    //设置鉴权元素
    void on_set_API_clicked();
    //询问Ai
    void on_enquire_Btn_clicked();

private:
    Ui::MainWindow *ui;
    NetWork* ai_NetWork;    //获取鉴权元素对象
};
#endif // MAINWINDOW_H
