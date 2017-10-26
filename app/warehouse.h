#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QObject>

class Warehouse : public QObject
{
    Q_OBJECT

public:
    explicit Warehouse(QObject *parent = nullptr);

    virtual bool hasInventory(const QString &name, int amount) const = 0;
    virtual bool remove(const QString &name, int amount) = 0;

    virtual ~Warehouse();
};

#endif // WAREHOUSE_H
