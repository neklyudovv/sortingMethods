#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QButtonGroup>
#include <QOverload>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup *sortGroup = new QButtonGroup(this);
    foreach (QRadioButton *rb, ui->groupBox_2->findChildren<QRadioButton*>())
        sortGroup->addButton(rb);

    connect(sortGroup, &QButtonGroup::buttonClicked, this, [this](QAbstractButton* button) {
        if (button)
            ui->plainTextEdit_2->setPlainText(QString("Выбрана сортировка: %1").arg(button->text()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
