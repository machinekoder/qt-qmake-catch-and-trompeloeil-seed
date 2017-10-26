#include <catch.hpp>
#include <trompeloeil.hpp>

#include <QSignalSpy>
#include <warehouse.h>
#include <viennawarehouse.h>
#include <order.h>
#include <autoorder.h>

extern template struct trompeloeil::reporter<trompeloeil::specialized>;

TEST_CASE("ViennaWarehouse starts with exactly 15 Schnitzel", "[app]")
{
    ViennaWarehouse warehouse;

    SECTION("Checking for less than 15 Schnitzel works") {
        REQUIRE(warehouse.hasInventory("Schnitzel", 10));
    }

    SECTION("Checking for exactly 15 Schnitzel works") {
        REQUIRE(warehouse.hasInventory("Schnitzel", 15));
    }

    SECTION("Checking for more than 15 Schnitzel fails") {
        REQUIRE(warehouse.hasInventory("Schnitzel", 200) == false);
    }
}

class WarehouseMock: public Warehouse
{
public:
    MAKE_CONST_MOCK2(hasInventory, bool(const QString&, int));
    MAKE_MOCK2(remove, bool(const QString&, int));
};

TEST_CASE("Filling Order from Warehouse works", "[app]")
{
    Order order("Schnitzel", 50);
    WarehouseMock warehouse;

    SECTION("filling removes inventory if in stock") {
        REQUIRE_CALL(warehouse, hasInventory("Schnitzel", 50))
                .RETURN(true);
        REQUIRE_CALL(warehouse, remove("Schnitzel", 50))
                .RETURN(true);

        order.fill(warehouse);

        REQUIRE(order.isFilled());
    }

    SECTION("filling does not remove inventory if not in stock") {
        REQUIRE_CALL(warehouse, hasInventory("Schnitzel", 50))
                .RETURN(false);

        order.fill(warehouse);

        REQUIRE_FALSE(order.isFilled());
    }
}

TEST_CASE("Automatically ordering wares with AutoOrder works", "[app")
{
    WarehouseMock warehouse;

    GIVEN("We have an auto order of 1 Tafelspitz") {
        Order order("Tafelspitz", 1);
        AutoOrder autoOrder(&warehouse, &order);
        QSignalSpy waresOrderedSpy(&autoOrder, &AutoOrder::waresOrdered);
        QSignalSpy outOfWaresSpy(&autoOrder, &AutoOrder::outOfWares);

        WHEN("We start the auto order") {
            autoOrder.startOrdering(1);

        AND_WHEN("we have enough Tafelspitz in stock") {
            REQUIRE_CALL(warehouse, hasInventory("Tafelspitz", 1))
                    .RETURN(true);
            REQUIRE_CALL(warehouse, remove("Tafelspitz", 1))
                    .RETURN(true);

            THEN("we are notified about the order") {
                waresOrderedSpy.wait(10);

                REQUIRE(waresOrderedSpy.count() == 1);
            }
        }

        AND_WHEN("we don't have enough Tafelspitz in stock") {
            REQUIRE_CALL(warehouse, hasInventory("Tafelspitz", 1))
                    .RETURN(false);

            THEN("we are notified that we have just run out of stock") {
                outOfWaresSpy.wait(10);

                REQUIRE(outOfWaresSpy.count() == 0);
            }
        }
        }
    }
}
