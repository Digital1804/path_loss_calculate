#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap map;
    QImage map_copy;
    map_copy.load("C:/Users/yarob/Desktop/room.png");
    map.load("C:/Users/yarob/Desktop/room.png");
    int map_size = map.height();
    QPainter p(&map);
    QColor array[200];
    for (int i = 0; i < 200; i++) {
        if (i < 35) array[i] = QColor(230, 46, 46);
        else if (i < 45) array[i] = QColor(225, 83, 46);
        else if (i < 50) array[i] = QColor(220, 114, 46);
        else if (i < 55) array[i] = QColor(215, 151, 46);
        else if (i < 60) array[i] = QColor(210, 200, 46);
        else if (i < 65) array[i] = QColor(194, 230, 46);
        else if (i < 70) array[i] = QColor(138, 230, 46);
        else if (i < 75) array[i] = QColor(58, 230, 46);
        else if (i < 80) array[i] = QColor(46, 230, 138);
        else if (i < 85) array[i] = QColor(46, 230, 180);
        else if (i < 90) array[i] = QColor(46, 175, 230);
        else if (i < 95) array[i] = QColor(46, 80, 230);
        else if (i < 100) array[i] = QColor(65, 46, 230);
        else if (i < 105) array[i] = QColor(31, 18, 148);
        else if (i < 110) array[i] = QColor(19, 10, 97);
        else array[i] = QColor(0, 0, 0);
    }
    QColor col;
    for(int i = 0; i < map_size; i++){
        for(int j = 0; j < map_size; j++){
            int DBm = (int)getDBm(i + 1, j + 1, 150, 200);
            col = map_copy.pixelColor(i, j);
            if (col == QColor(0,0,0))
                 DBm+=30;
            p.setPen(array[DBm]);
            p.drawPoint(i, j);
        }
    }

    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

double MainWindow::calcDBm (double dist, double h) {
    return (20 * (log10((40 * 3.14 * dist * 5) / 3)) + qMin(0.03 * pow(h, 1.72), 10.0) * log10(dist) - qMin(0.044 * pow(h, 1.72), 14.77) + (0.002 * log10(h) * dist));
}

double MainWindow::getDBm (int i, int j, int x, int y) {
    int a = qAbs(x - i), b = qAbs(y - j);

    double dist = qSqrt(a * a + b * b);
    double break_point = (2 * 3.14 * 150*10*5*pow(10,9)) / (3 * qPow(10, 8));
    double h = 5;
    if (dist < 10)
        return 1;
    else if (dist >= 10.0 && dist <= break_point)
        return calcDBm(dist, h);
    else if (dist > break_point && dist < 10000.0)
        return (calcDBm(break_point, h) + (40 * log10(dist / break_point)));
    else
        return 199;

}

MainWindow::~MainWindow() {
}

