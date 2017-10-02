#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TraceView;
class StreamView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void showOptionsDialog();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    void relayout();

private:
    using MainWindowPtr = std::unique_ptr<Ui::MainWindow>;
    using TraceViewPtr  = std::unique_ptr<TraceView>;
    using StreamViewPtr = std::unique_ptr<StreamView>;
    MainWindowPtr m_mainView;
    TraceViewPtr m_traceView;
    StreamViewPtr m_streamView;
};

#endif // MAINWINDOW_HPP
