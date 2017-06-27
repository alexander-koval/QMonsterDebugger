#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    using MainWindowPtr = std::unique_ptr<Ui::MainWindow>;

    MainWindowPtr mainView;

};

#endif // MAINWINDOW_HPP
