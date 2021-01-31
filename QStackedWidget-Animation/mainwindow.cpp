#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );

	ui->stackedWidget->setCurrentIndex(0);

	connect(ui->stackedWidget, SIGNAL(sigGetWidgets(int )), SLOT(getWidgets(int)));
	connect(ui->pushButton, SIGNAL(clicked()), SLOT(changeToFirst()));
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(changeToSecond()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	m_startPos = event->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	move(event->globalPos() - m_startPos);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void MainWindow::initView()
{
	ui->stackedWidget->setLength(ui->stackedWidget->width(), AnimationStackedWidget::LeftToRight);
	QList<QWidget *> lstWs;
	lstWs.append(ui->widget_5);
	lstWs.append(ui->widget_6);
	m_mapWidget.insert(0, lstWs);

	QList<QPoint> lstpos;
	lstpos.append(ui->widget_5->pos());
	lstpos.append(ui->widget_6->pos());
	m_mappos.insert(0, lstpos);

	ui->stackedWidget->setCurrentIndex(1);

	QList<QWidget *> lstWs2;
	lstWs2.append(ui->widget);
	lstWs2.append(ui->widget_2);
	lstWs2.append(ui->widget_3);
	lstWs2.append(ui->widget_4);
	m_mapWidget.insert(1, lstWs2);

	QList<QPoint> lstpos1;
	lstpos1.append(ui->widget->pos());
	lstpos1.append(ui->widget_2->pos());
	lstpos1.append(ui->widget_3->pos());
	lstpos1.append(ui->widget_4->pos());
	m_mappos.insert(1, lstpos1);
	ui->stackedWidget->setCurrentIndex(2);

	QList<QWidget *> lstWs3;
	lstWs3.append(ui->widget_7);
	lstWs3.append(ui->widget_8);
	lstWs3.append(ui->widget_9);
	m_mapWidget.insert(2, lstWs3);

	QList<QPoint> lstpos2;
	lstpos2.append(ui->widget_7->pos());
	lstpos2.append(ui->widget_8->pos());
	lstpos2.append(ui->widget_9->pos());
	m_mappos.insert(2, lstpos2);

	ui->stackedWidget->setCurrentIndex(0);

	m_lstLabels.append(ui->label_4);
	m_lstLabels.append(ui->label_5);
	m_lstLabels.append(ui->label_6);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	ui->stackedWidget->setLength(ui->stackedWidget->width(), AnimationStackedWidget::LeftToRight);
}

void MainWindow::setLabelStyle(int mindex)
{
	for (int i = 0; i < m_lstLabels.size(); i++)
	{
		if (i == mindex)
		{
			m_lstLabels.at(i)->setStyleSheet("background-color: rgba(24, 46, 58, 90);");

		}
		else
		{
			m_lstLabels.at(i)->setStyleSheet("background-color: rgb(255, 255, 255,90);");

		}
	}
}

void MainWindow::changeToFirst()
{
	int index = ui->stackedWidget->currentIndex();
	int mindex = index;
	//ÓÒ»¬
	ui->stackedWidget->setNext(true);
	if (index == 0)
	{
		ui->stackedWidget->start(2);
		mindex = 2;
	}
	else
	{
		ui->stackedWidget->start(index - 1);
		mindex = index - 1;
	}
	setLabelStyle(mindex);
	
	ui->stackedWidget->setWidgets(m_mapWidget.value(mindex));
	ui->stackedWidget->setPos(m_mappos.value(mindex));
}

void MainWindow::changeToSecond()
{
	int index = ui->stackedWidget->currentIndex();
	ui->stackedWidget->setNext(false);

	int mindexx = index;
	if (index == 2)
	{
		ui->stackedWidget->start(0);
		mindexx = 0;
	}
	else
	{
		ui->stackedWidget->start(index + 1);
		mindexx = index + 1;

	}
	setLabelStyle(mindexx);
	ui->stackedWidget->setWidgets(m_mapWidget.value(mindexx));
	ui->stackedWidget->setPos(m_mappos.value(mindexx));
}

void MainWindow::getWidgets(int currentIndex)
{
	int index = ui->stackedWidget->currentIndex();

	ui->stackedWidget->setWidgets(m_mapWidget.value(index));
	ui->stackedWidget->setPos(m_mappos.value(index));
	setLabelStyle(currentIndex);
}
