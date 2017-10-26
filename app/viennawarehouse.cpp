#include "viennawarehouse.h"

ViennaWarehouse::ViennaWarehouse(QObject *parent)
    : Warehouse(parent)
{
    m_wares.insert(std::make_pair("Schnitzel", 15));
    m_wares.insert(std::make_pair("Tafelspitz", 5));
}

bool ViennaWarehouse::hasInventory(const QString &name, int amount) const
{
    return (m_wares.at(name) >= amount);
}

bool ViennaWarehouse::remove(const QString &name, int amount)
{
    const auto currentValue = m_wares.at(name);
    if (currentValue >= amount) {
        m_wares.insert(std::make_pair(name, currentValue - amount));
        return true;
    }
    else {
        return false;  //  not big enough
    }
}
