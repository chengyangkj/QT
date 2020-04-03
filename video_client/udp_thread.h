#ifndef UDP_THREAD_H
#define UDP_THREAD_H

#include <QObject>

class udp_thread : public QObject
{
    Q_OBJECT
public:
    explicit udp_thread(QObject *parent = 0);

signals:

public slots:
};

#endif // UDP_THREAD_H