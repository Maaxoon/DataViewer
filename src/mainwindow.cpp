#include "mainwindow.h"
#include "dataparser.h"
#include "graphwidget.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QStatusBar>
#include <QPushButton>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_SelectFileButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Открыть файл с данными"), "", tr("Data files (*.s1p)"));
    if (fileName.isEmpty())
    {
        return;
    }

    std::ifstream in{fileName.toStdString()};
    DataParser parser;
    DataValues data;

    try {
        data = parser.Parse(in);
        graphWidget->setData(data);
        statusBar()->showMessage(tr("График успешно отрисован. Ожидаю следующие данные!"));
    }  catch (std::exception& ex) {
        statusBar()->showMessage(tr("Ошибка при считывании данных. Повторите попытку!"));
        QMessageBox msgBox;
        msgBox.setText(tr("При считывании файла произошла ошибка: ") + ex.what());
        msgBox.exec();
    }
}

void MainWindow::setupUi()
{
    this->setObjectName(QStringLiteral("MainWindow"));
    this->resize(800, 600);

    auto centralwidget = new QWidget(this);
    centralwidget->setObjectName(QStringLiteral("centralWidget"));
    this->setCentralWidget(centralwidget);

    graphWidget = new GraphWidget(this);
    graphWidget->setMinimumSize(QSize{800, 600});

    auto openFileButton = new QPushButton();
    openFileButton->setFixedSize(QSize{200, 40});
    openFileButton->setText(tr("Открыть файл с данными"));

    auto mainGroupBox = new QGroupBox(tr("График"));
    mainGroupBox->setObjectName("mainGroupBox");
    auto mainGroupBoxLayout = new QVBoxLayout();
    mainGroupBoxLayout->setObjectName("mainGroupBoxLayout");
    mainGroupBoxLayout->addWidget(graphWidget);
    mainGroupBox->setLayout(mainGroupBoxLayout);
    auto mainLayout = new QVBoxLayout(centralwidget);
    mainLayout->setObjectName("mainLayout");
    mainLayout->addWidget(mainGroupBox);
    mainLayout->addWidget(openFileButton);

    mainLayout->setAlignment(openFileButton, Qt::AlignHCenter);

    centralWidget()->setLayout(mainLayout);

    setStatusBar(new QStatusBar(this));
    statusBar()->showMessage(tr("Готов к формированию графика. Ожидание данных"));
    statusBar()->setStyleSheet("QStatusBar { background-color: #FDD9B5 }");

    connect(openFileButton, &QPushButton::clicked, this, &MainWindow::on_SelectFileButton_clicked);
}

