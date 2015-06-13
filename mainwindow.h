#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "mainwindow.h"


#include <QMainWindow>
#include <QTextStream>
#include <QPlainTextEdit>
#include <QStyledItemDelegate>
#include <QTextDocument>
#include <QPainter>
#include <QTableWidget>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QItemDelegate>
#include <QStyle>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTableWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class Programmation;
class Projet;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void update();
    void afficherCalendar();



private:
    Ui::MainWindow *ui;
    void displayProgrammation(const Programmation& p);

    void addTreeRoot(QString name, Projet& p);
    void addTreeChild(QTreeWidgetItem *parent, QString name);
    void treeGestion();
    void projetGestion();
    void afficherEvents();
    void afficherTacheRestanteProgrammer();

public slots:
    //void on_MainWindow_quit();
    void on_addProgTache_clicked();
    void on_CalendarNext_clicked();
    void on_CalendarPrevious_clicked();

    void on_ajoutEvent_clicked();
    //void on_addtachetoproject_clicked();

private slots:
    void on_addProjet_pressed();
    void on_ajouterTache_pressed();
    void on_printTache_pressed();
    void on_ajoutPrecedance_pressed();
};



#endif // MAINWINDOW_H
