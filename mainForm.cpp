#include "mainForm.h"
#include "ui_mainForm.h"

MainForm::MainForm(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->timerDisplay->display(QString("00:00"));
}

MainForm::~MainForm()
{
    delete ui;
}