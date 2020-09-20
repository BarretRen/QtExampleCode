#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintAll(QSvgGenerator* generator)
{
    QPainter painter;

    if (generator)
    {
        painter.begin(generator);//绑定painter和SVG generator
    }
    else
    {
        painter.begin(this);
    }

    painter.setFont(QFont("Times", 14, QFont::Bold));
    painter.drawText(QPoint(40, 40), "Testing");

    painter.drawLine(QPoint(50, 60), QPoint(100, 100));

    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(QRect(40, 120, 80, 30));

    QPen ellipsePen;
    ellipsePen.setColor(Qt::red);
    ellipsePen.setStyle(Qt::DashDotLine);

    painter.setPen(ellipsePen);
    painter.drawEllipse(QPoint(80, 200), 50, 20);

    QPainterPath rectPath;
    rectPath.addRect(QRect(150, 40, 100, 50));

    painter.setPen(QPen(Qt::red, 1, Qt::DashDotLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::yellow);
    painter.drawPath(rectPath);

    QPainterPath ellipsePath;
    ellipsePath.addEllipse(QPoint(200, 120), 50, 20);

    painter.setPen(QPen(QColor(79, 106, 25), 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(QColor(122, 163, 39));
    painter.drawPath(ellipsePath);

    QImage image;
    image.load(":/tux.png");
    painter.drawImage(QPoint(300, 225), image);

    painter.end();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    paintAll();
}

void MainWindow::on_actionSave_as_AVG_triggered()
{
    //打开文件选择框
    QString filePath = QFileDialog::getSaveFileName(this, "Save SVG", "SVG files (*,svg)");
    if (filePath == "")
    {
        return;
    }
    //创建QSvgGenerator
    QSvgGenerator generator;
    generator.setFileName(filePath);//设置文件路径
    generator.setSize(QSize(this->width(), this->height()));//设置大小
    generator.setViewBox(QRect(0, 0, this->width(), this->height()));
    generator.setTitle(("SVG example"));
    generator.setDescription("This SVG file is generated by QT");
    paintAll(&generator);
}