#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap map;
    QImage map_copy;
    map_copy.load("C:/Users/yarob/Desktop/room1.jpg");
    map.load("C:/Users/yarob/Desktop/room1.jpg");
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
    int DBm;
    for(int i = 0; i < map_size; i++){
        for(int j = 0; j < map_size; j++){
            col = map_copy.pixelColor(i, j);
            if (col == QColor(0,0,0))
                 DBm=199;
            else{
                DBm = (int)getDBm(i, j, 20, 390);
                int wloss = countWalls(i, j, 20, 390, map_copy);
                if (DBm>wloss)
                    DBm+=wloss;
            }
            p.setPen(array[DBm]);
            p.drawPoint(i, j);
        }
    }

    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

double MainWindow::countWalls(int x1, int y1, int x, int y, QImage map_copy){
    QColor col;
    int a=x1,b=x,c=y1,d=y, DBm=0;
    while (1){
        if (x1<x){
            if (a<b){
                a++;
            }
            if (y1<y){
                if (c<d)
                    c++;
            }
            else if (y1>y){
                if (c>d)
                    c--;
            }
        }
        else if (x1>x){
            if (a>b){
                a--;
            }
            if (y1<y){
                if (c<d)
                    c++;
            }
            else if (y1>y){
                if (c>d)
                    c--;
            }
        }
        if (x1==x){
            if (y1<y){
                if (c<d)
                    c++;
            }
            else if (y1>y){
                if (c>d)
                    c--;
            }
        }
        if ((a==b) && (c==d))
            break;
        col = map_copy.pixelColor(a, c);
        if (col == QColor(0,0,0))
             DBm+=1;
    }
    return DBm;
}

double MainWindow::calcDBm (double dist, double h) {
    return (20 * (log10((40 * 3.14 * dist * 5) / 3)) + qMin(0.03 * pow(h, 1.72), 10.0) * log10(dist) - qMin(0.044 * pow(h, 1.72), 14.77) + (0.002 * log10(h) * dist));
}

double MainWindow::getDBm (int i, int j, int x, int y) {
    int a = qAbs(x - i), b = qAbs(y - j);

    double dist = qSqrt(a * a + b * b);
    double break_point = (2 * 3.14 * 1.5 * 1.5 * 5 * pow(10,9)) / (3 * qPow(10, 8));
    double h = 1;
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

