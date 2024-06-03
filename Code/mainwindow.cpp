#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ai_NetWork = new NetWork();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*  解析回复语句
 *  text：回复语句
*/
void MainWindow::handle_GetAnswerText(const QString &text)
{
    QString hex;
    //定义正则表达式，用于获取指定result值后的数据
    QRegularExpression regular("\"result\":\"(.*?)\"");
    QRegularExpressionMatch match = regular.match(text);
    QString matchedString = match.captured();   //捕获匹配正则表达式的数据

    //设置正则表达式，用于匹配\x后面的数据
    regular.setPattern("\\\\x([0-9A-Fa-f]{2})");

    //迭代正则表达式匹配的结果
    QRegularExpressionMatchIterator iteration = regular.globalMatch(matchedString);

    while (iteration.hasNext()) {       //循环遍历寻找匹配数据
        QRegularExpressionMatch match = iteration.next();
        hex = match.captured(1);
        bool ok;
        int decimal = hex.toInt(&ok, 16);
        if (ok) {
            matchedString.replace(match.capturedStart(), match.capturedLength(), QString(QChar(decimal)));
        }
    }

    //文本处理
    matchedString.replace("result\":\"", "");
    matchedString.replace("\\n", "\n");
    ui->reply_Text->clear();
    ui->reply_Text->setText(matchedString);
}

//询问Ai
void MainWindow::on_enquire_Btn_clicked()
{
    QString input_Text = ui->question_Text->toPlainText();
    if(!input_Text.isEmpty()){    //判断是否输入文字
        ui->question_Text->clear();
        ui->reply_Text->setText("正在生成回复文本");
        QString Str = ai_NetWork->handle_SetEnquireText(input_Text);
        handle_GetAnswerText(Str);  //处理答复语句
    }
    else{
        QMessageBox::warning(nullptr,"错误","未输入信息",QMessageBox::Ok);
    }
}

//设置鉴权元素
void MainWindow::on_set_API_clicked()
{
    QString input_Key = ui->key_Text->text();
    QString input_Secret = ui->secret_Text->text();
    if(input_Key.isEmpty() || input_Secret.isEmpty()){
        QMessageBox::warning(nullptr,"错误","未输入鉴权元素",QMessageBox::Ok);
    }else{
        ai_NetWork->handle_SetAuthentication(input_Key,input_Secret);    //设置鉴权元素
    }
}

