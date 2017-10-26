#ifndef AUTOORDER_H
#define AUTOORDER_H

#include <QObject>
#include <QPointer>
#include <QTimer>
#include "warehouse.h"
#include "order.h"

class AutoOrder : public QObject
{
    Q_OBJECT

public:
    explicit AutoOrder(QPointer<Warehouse> warehouse, QPointer<Order> order, QObject *parent = nullptr);

    void startOrdering(int interval);

signals:
    void waresOrdered();
    void outOfWares();

private:
    QPointer<Warehouse> m_warehouse;
    QPointer<Order> m_order;
    QTimer m_orderTimer;

private slots:
    void orderWares();

};

#endif // AUTOORDER_H
