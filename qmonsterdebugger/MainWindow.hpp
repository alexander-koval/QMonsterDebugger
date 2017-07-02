#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
class TraceView;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    void relayout();

private:
    using MainWindowPtr = std::unique_ptr<Ui::MainWindow>;
    using TraceViewPtr  = std::unique_ptr<Ui::TraceView>;
    MainWindowPtr m_mainView;
};

#endif // MAINWINDOW_HPP
