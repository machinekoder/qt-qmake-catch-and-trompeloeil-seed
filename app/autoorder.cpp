#include "autoorder.h"

AutoOrder::AutoOrder(QPointer<Warehouse> warehouse, QPointer<Order> order, QObject *parent)
    : QObject(parent)
    , m_warehouse(warehouse)
    , m_order(order)
{
    connect(&m_orderTimer, &QTimer::timeout, this, &AutoOrder::orderWares);
}

void AutoOrder::startOrdering(int interval)
{
    m_orderTimer.start(interval);
}

void AutoOrder::orderWares()
{
    if (m_warehouse.isNull() || m_order.isNull()) {
        return;
    }

    if (m_order->fill(*m_warehouse)) {
        emit waresOrdered();
    }
    else {
        emit outOfWares();
        m_orderTimer.stop();
    }
}
