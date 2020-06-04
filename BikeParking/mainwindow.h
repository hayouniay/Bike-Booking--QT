#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cancel.h"
#include "book.h"
#include "db.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Show();

private slots:
    void on_btnBook_clicked();
    void on_btnCancel_clicked();


private:
    Ui::MainWindow *ui;
    void updateUI();

    Book *ptrBook;
    Cancel *ptrCancel;
};

#endif // MAINWINDOW_H
