#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>

namespace Ui { class MainWindow; }

namespace monster {
class TraceView;
class StreamView;
class Session;
class MonsterServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    using SessionPtr = QSharedPointer<Session>;
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void onShowOptionsDialog();
    void onSessionCreated(SessionPtr session);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    void relayout();

private:
    using ServerPtr = QScopedPointer<MonsterServer>;
    using MainWindowPtr = std::unique_ptr<Ui::MainWindow>;
    using TraceViewPtr  = std::unique_ptr<TraceView>;
    using StreamViewPtr = std::unique_ptr<StreamView>;
    MainWindowPtr m_mainView;
    TraceViewPtr m_traceView;
    StreamViewPtr m_streamView;
    ServerPtr m_server;
};
}
#endif // MAINWINDOW_HPP
