//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_MAINWINDOW_H
#define ENG1_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow * ui;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif //ENG1_MAINWINDOW_H
