#include "CCtrlDateEdit.h"
#include <QPainter>
#include <QDebug>

class CCtrlDateEdit::Private {
public:
    Private(CCtrlDateEdit* qq) : q(qq), m_Null(false), m_Nullable(false) {}

    CCtrlDateEdit* const q;

    bool m_Null;
    bool m_Nullable;

    void setNull(bool n) {
        m_Null = n;
        if (m_Null) {
            QLineEdit *edit = q->findChild<QLineEdit*>();
            if (!edit->text().isEmpty()) {
                edit->clear();
            }
        }
    }
};

CCtrlDateEdit::CCtrlDateEdit(QWidget *parent) :
    QDateEdit(parent),
    d(new Private(this))
{
    setDisplayFormat("yyyy-MM-dd");
}


QDateTime CCtrlDateEdit::dateTime() const
{
    if (d->m_Nullable && d->m_Null) {
        return QDateTime();
    }
    else {
        return QDateEdit::dateTime();
    }
}


QDate CCtrlDateEdit::date() const
{
    if (d->m_Nullable && d->m_Null) {
        return QDate();
    }
    else {
        return QDateEdit::date();
    }
}


QTime CCtrlDateEdit::time() const
{
    if (d->m_Nullable && d->m_Null) {
        return QTime();
    }
    else {
        return QDateEdit::time();
    }
}


void CCtrlDateEdit::setDateTime(const QDateTime &dateTime)
{
    if (d->m_Nullable && !dateTime.isValid()) {
        d->setNull(true);
    }
    else {
        d->setNull(false);
        QDateEdit::setDateTime(dateTime);
    }
}


void CCtrlDateEdit::setDate(const QDate &date)
{
    if (d->m_Nullable && !date.isValid()) {
        d->setNull(true);
    }
    else {
        d->setNull(false);
        QDateEdit::setDate(date);
    }
}

void CCtrlDateEdit::setTime(const QTime &time)
{
    if (d->m_Nullable && !time.isValid()) {
        d->setNull(true);
    }
    else {
        d->setNull(false);
        QDateEdit::setTime(time);
    }
}

bool CCtrlDateEdit::isNullable() const
{
    return d->m_Nullable;
}

void CCtrlDateEdit::setNullable(bool enable)
{
    d->m_Nullable = enable;

    update();
}


QSize CCtrlDateEdit::sizeHint() const
{
    const QSize sz = QDateEdit::sizeHint();
    return QSize(sz.width() + 3, sz.height());
}

QSize CCtrlDateEdit::minimumSizeHint() const
{
    const QSize sz = QDateEdit::minimumSizeHint();
    return QSize(sz.width() + 3, sz.height());
}

void CCtrlDateEdit::showEvent(QShowEvent *event)
{
    QDateEdit::showEvent(event);
    d->setNull(d->m_Null);
}

void CCtrlDateEdit::resizeEvent(QResizeEvent *event)
{
    QDateEdit::resizeEvent(event);
}

void CCtrlDateEdit::paintEvent(QPaintEvent *event)
{
    d->setNull(d->m_Null);
    QDateEdit::paintEvent(event);

}

void CCtrlDateEdit::keyPressEvent(QKeyEvent *event)
{
    if (d->m_Nullable &&
        (event->key() >= Qt::Key_0) &&
        (event->key() <= Qt::Key_9) &&
        d->m_Null) {
        setDateTime(QDateTime::currentDateTime());
    }
    if (event->key() == Qt::Key_Tab && d->m_Nullable && d->m_Null) {
        QAbstractSpinBox::keyPressEvent(event);
        return;
    }
    if (event->key() == Qt::Key_Backspace && d->m_Nullable){
        QLineEdit *edit = this->findChild<QLineEdit *>();
        if (edit->selectedText() == edit->text()) {
            setDateTime(QDateTime());
            event->accept();
            return;
        }
    }

    QDateEdit::keyPressEvent(event);
}

void CCtrlDateEdit::mousePressEvent(QMouseEvent *event)
{
    bool saveNull = d->m_Null;
    QDateEdit::mousePressEvent(event);
    if (d->m_Nullable && saveNull && calendarWidget()->isVisible()) {
        setDateTime(QDateTime::currentDateTime());
    }
}

bool CCtrlDateEdit::focusNextPrevChild(bool next)
{
    if (d->m_Nullable && d->m_Null){
        return QAbstractSpinBox::focusNextPrevChild(next);
    }
    else {
        return QDateEdit::focusNextPrevChild(next);
    }
}

QValidator::State CCtrlDateEdit::validate(QString &input, int &pos) const
{
    if (d->m_Nullable && d->m_Null){
        return QValidator::Acceptable;
    }
    return QDateEdit::validate(input, pos);
}
