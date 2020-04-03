#ifndef CCTRLDATEEDIT_H
#define CCTRLDATEEDIT_H

#include <QWidget>
#include <QDateEdit>
#include <QStyle>
#include <QPushButton>
#include <QLineEdit>
#include <QStyleOptionSpinBox>
#include <QKeyEvent>
#include <QCalendarWidget>

class CCtrlDateEdit : public QDateEdit
{
    Q_OBJECT
public:
public:
    explicit CCtrlDateEdit(QWidget *parent = 0);

    QDateTime dateTime() const;
    QDate date() const;
    QTime time() const;

    bool isNullable() const;
    void setNullable(bool enable);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
        void mousePressEvent(QMouseEvent *event);
    bool focusNextPrevChild(bool next);
    QValidator::State validate(QString &input, int &pos) const;

public slots:
    void setDateTime(const QDateTime &dateTime);
    void setDate(const QDate &date);
    void setTime(const QTime &time);

private:
    Q_DISABLE_COPY(CCtrlDateEdit)
    class Private;
    friend class Private;
    Private* d;
};

#endif // CCTRLDATEEDIT_H
