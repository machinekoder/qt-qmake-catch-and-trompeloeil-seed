#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include "warehouse.h"

class Order : public QObject
{
    Q_OBJECT

public:
    explicit Order(const QString &name, int amount, QObject *parent = nullptr);
    bool fill(Warehouse &w);
    bool isFilled() const;

private:
    QString m_name;
    int m_amount;
    bool m_filled;
};

#endif // ORDER_H
