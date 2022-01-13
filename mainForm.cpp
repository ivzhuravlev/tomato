#include "mainForm.h"
#include "ui_mainForm.h"

MainForm::MainForm(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}