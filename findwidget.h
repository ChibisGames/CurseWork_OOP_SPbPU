// FindAndSortWidget.h
#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class FindAndSortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindAndSortWidget(QTableWidget *tableWidget, QWidget *parent = nullptr);
    //~FindAndSortWidget();
    void clearSortStatus();


private slots:
    void onSearchClicked();
    void onClearClicked();
    void highlightSearchResults(int row, int column, int previousRow, int previousColumn);
    void onEnterPressed();
    void onSortClicked();

private:
    void setupFindWidget();
    void performFind();
    void clearHighlights();
    void sortTable();

    QTableWidget *newTableWidget;
    QComboBox *categoryCombo;
    QLineEdit *findEdit;
    QPushButton *findButton;
    QPushButton *clearButton;
    QPushButton *sortButton;
    QLabel *findStatusLabel;
    QLabel *sortStatusLabel;


    QList<QTableWidgetItem*> foundItems;
    int currentFoundIndex;
};

#endif // SEARCHWIDGET_H
