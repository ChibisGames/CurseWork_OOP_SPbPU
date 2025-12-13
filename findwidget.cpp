// FindAndSortWidget.cpp
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QKeyEvent>
#include <QMessageBox>
#include <QAction>

#include "findwidget.h"


FindAndSortWidget::FindAndSortWidget(QTableWidget *tableWidget, QWidget *parent) : QWidget(parent),
    newTableWidget(tableWidget),
    currentFoundIndex(-1)
{
    setupFindWidget();

    // Подсвечиваем изменения текущей ячейки
    if (newTableWidget) {
        connect(newTableWidget, &QTableWidget::currentCellChanged,
                this, &FindAndSortWidget::highlightSearchResults);
    }
}

//FindAndSortWidget::~FindAndSortWidget(){}

void FindAndSortWidget::setupFindWidget(){
    // выбор категории
    categoryCombo = new QComboBox(this);
    categoryCombo->setMinimumWidth(150);

    // Заполняем категории
    for (int col = 0; col < newTableWidget->columnCount(); col++) {
        categoryCombo->addItem(newTableWidget->horizontalHeaderItem(col)->text(), col);
    }
    // Ол инклюзив
    categoryCombo->insertItem(0, "Все столбцы", -1);
    categoryCombo->setCurrentIndex(0);

    // Поле ввода для поиска
    findEdit = new QLineEdit(this);
    findEdit->setPlaceholderText("Введите текст для поиска...");
    findEdit->setMinimumWidth(200);

    // клик по Enter (спасибо слову "Key", иначе я бы удалил документацию Qt)
    auto *searchAction = new QAction(this);
    searchAction->setShortcut(QKeySequence(Qt::Key_Return));
    connect(searchAction, &QAction::triggered, this, &FindAndSortWidget::onEnterPressed);
    findEdit->addAction(searchAction, QLineEdit::TrailingPosition);

    // Кнопка поиска
    findButton = new QPushButton("Найти", this);
    findButton->setDefault(true);
    connect(findButton, &QPushButton::clicked, this, &FindAndSortWidget::onSearchClicked);

    // Кнопка очистки
    clearButton = new QPushButton("Очистить", this);
    connect(clearButton, &QPushButton::clicked, this, &FindAndSortWidget::onClearClicked);

    // Кнопка сортировки
    sortButton = new QPushButton("Сортировать", this);
    sortButton->setDefault(true);
    connect(sortButton, &QPushButton::clicked, this, &FindAndSortWidget::onSortClicked);

    // Статусная строка поиска
    findStatusLabel = new QLabel("Готово к поиску", this);
    findStatusLabel->setStyleSheet("QLabel { color: gray; }");

    // Статусная строка сортировки
    sortStatusLabel = new QLabel("Готово к сортировке", this);
    sortStatusLabel->setStyleSheet("QLabel { color: gray; }");

    // горизонтальный layout опций файнда
    auto *findWidgetsLayout = new QHBoxLayout();
    findWidgetsLayout->addWidget(new QLabel("Категория:", this));
    findWidgetsLayout->addWidget(categoryCombo);
    findWidgetsLayout->addWidget(new QLabel("Поиск:", this));
    findWidgetsLayout->addWidget(findEdit);
    findWidgetsLayout->addWidget(findButton);
    findWidgetsLayout->addWidget(clearButton);
    findWidgetsLayout->addSpacing(40); // отступ дял кнопки сортировки
    findWidgetsLayout->addWidget(sortButton);
    findWidgetsLayout->addStretch();

    auto *statusLayout = new QHBoxLayout();
    statusLayout->addWidget(findStatusLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(sortStatusLabel);


    // Вертикальный layout для статуса (под основной строкой)
    auto *verticalLayout = new QVBoxLayout(this);
    verticalLayout->addLayout(findWidgetsLayout);
    verticalLayout->addLayout(statusLayout);

    this->setLayout(verticalLayout);
}

void FindAndSortWidget::onSearchClicked(){ // клик по кнопке

    performFind();
}

// обработка кнопки очистки
void FindAndSortWidget::onClearClicked(){

    clearHighlights();
    findEdit->clear();
    foundItems.clear();
    currentFoundIndex = -1;
    findStatusLabel->setText("Готово к поиску");
    findStatusLabel->setStyleSheet("QLabel { color: gray; }"); // статус в серый)
}

// Cас поиск
void FindAndSortWidget::performFind(){
    QString searchText = findEdit->text().trimmed();

    if (searchText.isEmpty()) {
        findStatusLabel->setText("Введите текст для поиска");
        findStatusLabel->setStyleSheet("QLabel { color: orange; }"); // если ничего не введено, то апельсиновый
        return;
    }

    clearHighlights();
    foundItems.clear();
    currentFoundIndex = -1;

    int categoryIndex = categoryCombo->currentData().toInt();

    // для поиска по всем столбцам
    bool searchAllColumns = (categoryIndex == -1);

    // Ищем совпадения
    for (int row = 0; row < newTableWidget->rowCount(); ++row) {
        if (searchAllColumns) {
            // Поиск по всем столбцам
            for (int col = 0; col < newTableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = newTableWidget->item(row, col);
                if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                    foundItems.append(item);
                }
            }
        } else {
            // Поиск по определённому столбцу
            QTableWidgetItem *item = newTableWidget->item(row, categoryIndex);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                foundItems.append(item);
            }
        }
    }

    if (!foundItems.isEmpty()) {
        // Подсвечиваем найденные ячейки
        for (auto *item : foundItems) {
            item->setBackground(QBrush(QColor(255, 255, 0, 100))); // Желтый???
        }

        // Переходим к первому результату
        currentFoundIndex = 0;
        QTableWidgetItem *firstItem = foundItems.first();
        newTableWidget->setCurrentCell(firstItem->row(), firstItem->column());
        newTableWidget->scrollToItem(firstItem);

        findStatusLabel->setText(QString("Найдено: %1 совпадений").arg(foundItems.size())); // :)
        findStatusLabel->setStyleSheet("QLabel { color: green; }");
    } else {
        findStatusLabel->setText("Совпадений не найдено"); // :(
        findStatusLabel->setStyleSheet("QLabel { color: red; }");
    }
}

// Сбрасываем цвет для всех ячеек
void FindAndSortWidget::clearHighlights(){
    for (int row = 0; row < newTableWidget->rowCount(); ++row) {
        for (int col = 0; col < newTableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = newTableWidget->item(row, col);
            if (item) {
                item->setBackground(QBrush()); // Возвращаем стандартный
            }
        }
    }
}

// Подсветка результатов
void FindAndSortWidget::highlightSearchResults(int row, int column, int previousRow, int previousColumn){
    Q_UNUSED(previousRow); // Это типо чтобы компилятор голову не забивал неиспользованием переменной
    Q_UNUSED(previousColumn);

    if (!foundItems.isEmpty()) {
        // Находим индекс текущего элемента в списке найденных
        for (int i = 0; i < foundItems.size(); ++i) {
            QTableWidgetItem *item = foundItems[i];
            if (item->row() == row && item->column() == column) {
                currentFoundIndex = i;

                // Подсвечиваем первый элемент цветом
                item->setBackground(QBrush(QColor(0, 255, 0, 100))); // Зелёненький

                // Обновляем статус
                findStatusLabel->setText(QString("Найдено: %1/%2")
                                           .arg(currentFoundIndex + 1)
                                           .arg(foundItems.size()));
                break;
            }
        }
    }
}

// клик по клаве (энтер)
void FindAndSortWidget::onEnterPressed(){
    performFind();
}


void FindAndSortWidget::sortTable(){
    int categoryIndex = categoryCombo->currentData().toInt();

    bool searchAllColumns = (categoryIndex == -1);


    if (!searchAllColumns)
    {
        newTableWidget->sortItems(categoryIndex, Qt::AscendingOrder);
        sortStatusLabel->setText(QString("Отсортировано по столбцу '%1'").
                                 arg(newTableWidget->horizontalHeaderItem(categoryIndex)->text()));
        sortStatusLabel->setStyleSheet("QLabel { color: aqua; }"); // голубенький

    }
    else {
        sortStatusLabel->setText("Не выбрана категоря для сортировки");
        sortStatusLabel->setStyleSheet("QLabel { color: crimson; }"); // блуди - кровавый :3
    }
}


void FindAndSortWidget::onSortClicked(){
    sortTable();
}

// Обнуление статуса сортировки
void FindAndSortWidget::clearSortStatus(){
    currentFoundIndex = -1;
    sortStatusLabel->setText("Готово к сортировке");
    sortStatusLabel->setStyleSheet("QLabel { color: gray; }");

}
