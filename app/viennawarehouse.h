#ifndef VIENNAWAREHOUSE_H
#define VIENNAWAREHOUSE_H

#include <QObject>
#include "warehouse.h"

class ViennaWarehouse : public Warehouse
{
    Q_OBJECT

public:
    explicit ViennaWarehouse(QObject *parent = nullptr);

    // Warehouse interface
    bool hasInventory(const QString &name, int amount) const;
    bool remove(const QString &name, int amount);

private:
    std::map<QString, int> m_wares;
};

#endif // VIENNAWAREHOUSE_H
