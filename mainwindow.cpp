#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "sort.h"

#include <QButtonGroup>
#include <QElapsedTimer>
#include <QOverload>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    buttonGroup(new QButtonGroup(this))
{
    ui->setupUi(this);

    buttonGroup->addButton(ui->radioButton, 1);
    buttonGroup->addButton(ui->radioButton_2, 2);
    buttonGroup->addButton(ui->radioButton_3, 3);
    buttonGroup->addButton(ui->radioButton_4, 4);
    buttonGroup->addButton(ui->radioButton_5, 5);
    buttonGroup->addButton(ui->radioButton_6, 6);
    buttonGroup->addButton(ui->radioButton_7, 7);
    buttonGroup->addButton(ui->radioButton_8, 8);

    // Connect buttons
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateArray);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortArray);
}

void MainWindow::generateArray() {
    const int n = 20000;
    std::vector<int> array(n);
    std::srand(std::time(nullptr));

    QString arrayText;
    for(int i = 0; i < n; i++)
        array[i] = rand()%n;

    for (int num : array)
        arrayText += QString::number(num) + " ";

    ui->plainTextEdit->setPlainText(arrayText);
}

void MainWindow::sortArray() {
    QString sortedArrayText = "";
    QString arrayText = ui->plainTextEdit->toPlainText();
    QStringList numbers = arrayText.split(" ", Qt::SkipEmptyParts);
    std::vector<int> array;

    for (const QString &num : numbers)
        array.push_back(num.toInt());

    int selectedSort = buttonGroup->checkedId();

    QElapsedTimer timer;
    timer.start();
    switch(selectedSort) {
    case 1: BubbleSort(array); break;
    case 2: ShakerSort(array); break;
    case 3: CombSort(array); break;
    case 4: InsertionSort(array); break;
    case 5: SelectionSort(array); break;
    case 6: QuickSort(array); break;
    case 7: MergeSort(array); break;
    case 8: HeapSort(array); break;
    default: break;
    }

    qint64 elapsedTime = timer.elapsed();

    for(int i = 0; i<array.size(); i++){
        ui->progressBar->setValue(i);
        QApplication::processEvents();
    }

    for (int num : array)
        sortedArrayText += QString::number(num) + " ";

    ui->plainTextEdit_2->setPlainText(sortedArrayText);
    ui->plainTextEdit_3->setPlainText(QString("Время сортировки: %1 мс").arg(elapsedTime));
}


MainWindow::~MainWindow()
{
    delete ui;
}
