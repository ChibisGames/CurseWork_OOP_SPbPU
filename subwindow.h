#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QString>

#include "BookUnit.h"


enum WindowMode {
    Add = 0,
    Refactor = 1,
    Delete = 2
};

class SubWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SubWindow(WindowMode mode, QTableWidget *tableWidget, list<BookUnit> *bookUnits, QWidget *parent = nullptr);

    int getRow();
    int getRefactorItemIndex();
    int getRefactorPhoneNumberIndex();
    QString getRefactorLine();
    QString getNewEmailLine();


    vector<std::string> getFullName();

    vector<std::string> getAddress();

    vector<int> getDateEdit();

    std::string getEmail();
    std::string getPhoneNumber();


private slots:
    void acceptAdd();
    void acceptRefactor();
    void acceptDelete();
    void cancelEdit();

private:
    void setupSubWindow();
    void setupAddWindow();
    void setupRefactorWindow();
    void setupDeleteWindow();

    bool doAccept();
    bool doRefactor();


    QTableWidget *newTableWidget;

    WindowMode mode;
    list<BookUnit> *bookUnits;

    QPushButton *acceptButtun;
    QPushButton *cancelButton;

    QComboBox *refactorItemCombo;
    QLineEdit *refactorItemLine;
    QLineEdit *newEmailEdit;
    QSpinBox *refactorPhoneNumberIndex;

    QSpinBox *spinBox;
    QSlider *slider;

    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QLineEdit *patronymicEdit;

    QLineEdit *countryEdit;
    QLineEdit *regionEdit;
    QLineEdit *cityEdit;
    QLineEdit *streetEdit;
    QLineEdit *homeEdit;
    QLineEdit *corpusEdit;
    QLineEdit *flatEdit;

    QDateEdit *dateEdit;

    QLineEdit *emailEdit;

    QLineEdit *phoneNumberEdit;


};

#endif // SUBWINDOW_H
