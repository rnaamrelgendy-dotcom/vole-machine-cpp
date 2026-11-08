#pragma once
#include <QWidget>
#include "Machine.h"

class QLineEdit;
class QTableWidget;
class QTextEdit;
class QPushButton;

class MainWindow : public QWidget {
    Q_OBJECT
private:
    Machine machine;
    QString loadedFile;
    bool loaded = false;
    bool halted = false;

    QLineEdit    *fileEdit;
    QLineEdit    *searchEdit;
    QTableWidget *memTable;
    QTextEdit    *ioView;
    QPushButton  *browseBtn, *loadBtn, *runBtn, *stepBtn, *resetBtn;

    void buildUi();
    void applyStyle();
    void refreshMemory();
    void highlightPc();
    void appendOutput(const QString& text);

private slots:
    void onBrowse();
    void onLoad();
    void onRun();
    void onStep();
    void onReset();
    void onSearch(const QString& text);

public:
    explicit MainWindow(QWidget *parent = nullptr);
};