#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene &getScene();

  private:
    QGraphicsScene scene;
    QGraphicsView  view;

};

#endif // MAINWINDOW_HPP
