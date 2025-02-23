#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <algorithm>
#include "sort.h"

#include <QButtonGroup>
#include <QElapsedTimer>
#include <QOverload>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // подключаем кнопки
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

    QElapsedTimer timer;
    timer.start();

    QList<QRadioButton*> buttons = ui->groupBox_2->findChildren<QRadioButton*>();

    std::sort(buttons.begin(), buttons.end(), [](QRadioButton *a, QRadioButton *b) {
        return a->y() < b->y();
    });

    for (int i = 0; i < buttons.size(); ++i)
        if (buttons[i]->isChecked())
            switch(i) {
            case 0: BubbleSort(array); break;
            case 1: ShakerSort(array); break;
            case 2: CombSort(array); break;
            case 3: InsertionSort(array); break;
            case 4: SelectionSort(array); break;
            case 5: QuickSort(array); break;
            case 6: MergeSort(array); break;
            case 7: HeapSort(array); break;
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
