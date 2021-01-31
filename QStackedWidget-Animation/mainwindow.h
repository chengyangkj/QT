#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	void initView();
	void resizeEvent(QResizeEvent *event);
	void setLabelStyle(int);
public slots:
    void changeToFirst();
    void changeToSecond();
	void getWidgets(int);

private:
    Ui::MainWindow *ui;
	QMap<int, QList<QWidget *>> m_mapWidget;
	QMap<int, QList<QPoint>> m_mappos;
	QList<QLabel*> m_lstLabels;
	QPoint m_startPos;
};

#endif // MAINWINDOW_H
