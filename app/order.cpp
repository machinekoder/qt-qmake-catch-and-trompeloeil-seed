#include "order.h"

Order::Order(const QString &name, int amount, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_amount(amount)
    , m_filled(false)
{

}

bool Order::fill(Warehouse &w)
{
    if (m_filled) {
        return false;
    }

    if (!w.hasInventory(m_name, m_amount)) {
        return false;
    }

    m_filled = w.remove(m_name, m_amount);

    return m_filled;
}

bool Order::isFilled() const
{
    return m_filled;
}
