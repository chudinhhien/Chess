#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "iostream"
#include "UDPCLient.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    struct User {
        string username;
        string password;
    };

    User account;

    account.username = ui->textEdit->toPlainText().toStdString();
    account.password = ui->textEdit_2->toPlainText().toStdString();

    UDPClient client("127.0.0.1",5500);

    client.sendRequestLogin(account.username,account.password);

    cout << account.username <<  ' ' << account.password << endl;
}

