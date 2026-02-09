#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <list>

#include "BookUnit.h"
#include "findwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //~MainWindow(); // как бы надо, но боюсь отключить автоматический деструктор

private slots:
    void addBook();
    void refactorBook();
    void deleteBook();

    void loadData();
    void saveData();

private:
    void setupMainWindow();
    void createTable();
    void setupButtons();
    void addBookUnitToTable(BookUnit& bookUnit, int row);
    void updateTable();

    void qtReadFile(const QString& filename);
    void qtWrite(const QString& filename);

    QTableWidget *tableWidget;

    //SubWindow *subWindow;
    QPushButton *addButton;
    QPushButton *refactorButton;
    QPushButton *deleteButton;

    QPushButton *loadButton;
    QPushButton *saveButton;

    FindAndSortWidget *findBlock;

    list<BookUnit> *bookUnits;

    const char *FILENAME = "../../data.txt";
    static const int MAX_UNITS = 50;
    unsigned int personIndex = 0;
};

#endif // MAINWINDOW_H
