#include "catch.hpp"
#include "reactor/common/creator.hpp"

/**
 * Example classes
 */

class Interface {
public:
    virtual void init(int value) = 0;
    virtual int getValue() = 0;
};

class Implementation : public Interface {
public:
    Implementation() {}
    Implementation(int value) { this->value = value; }

    void init(int value) { this->value = value; }
    int getValue() { return value; }

private:
    int value;
};

class InterfaceProxy : public Interface {
protected:
    Interface *implPtr;

public:
    InterfaceProxy(Interface *ptr) { implPtr = ptr; }
    ~InterfaceProxy() { delete implPtr; }

    void init(int value) { implPtr->init(value); }
    int getValue() { return implPtr->getValue(); };
};

/**
 * CREATE definitions
 */

#define CREATE_test_reactor_common_creator_CREATE_Interface_1(var, ...) INNER_CREATE_STATIC(Implementation, var, __VA_ARGS__)
#define CREATE_test_reactor_common_creator_CREATE_Interface_2(var, ...) INNER_CREATE_DYNAMIC_PROXY(InterfaceProxy, Implementation, var, __VA_ARGS__)

#define CREATE_PTR_test_reactor_common_creator_CREATE_PTR_Interface(ptrType, ptr, ...) INNER_CREATE_PTR_DYNAMIC_SHARED(ptrType, Implementation, ptr, __VA_ARGS__)
#define CREATE_PTR_STATIC_test_reactor_common_creator_CREATE_PTR_Interface(ptrType, ptr, ...) INNER_CREATE_PTR_STATIC(ptrType, Implementation, ptr, __VA_ARGS__)
#define CREATE_PTR_DYNAMIC_test_reactor_common_creator_CREATE_PTR_Interface(ptrType, ptr, ...) INNER_CREATE_PTR_DYNAMIC(ptrType, Implementation, ptr, __VA_ARGS__)

/**
 * Test cases
 */

TEST_CASE("creator CREATE macros is correct", "[creator.CREATE]") {
    CREATE(test_reactor_common_creator_CREATE_Interface_1, test1);
    test1.init(1);
    REQUIRE( test1.getValue() == 1 );

    CREATE(test_reactor_common_creator_CREATE_Interface_2, test2);
    test2.init(2);
    REQUIRE( test2.getValue() == 2 );

    CREATE(test_reactor_common_creator_CREATE_Interface_1, test3, 3);
    REQUIRE( test3.getValue() == 3 );
}

TEST_CASE("creator CREATE_PTR macroses is correct", "[creator.CREATE_PTR]") {
    CREATE_PTR(test_reactor_common_creator_CREATE_PTR_Interface, Interface *, test1);
    test1->init(1);
    REQUIRE( test1->getValue() == 1 );

    CREATE_PTR_STATIC(test_reactor_common_creator_CREATE_PTR_Interface, Interface *, test2);
    test2->init(2);
    REQUIRE( test2->getValue() == 2 );

    CREATE_PTR_DYNAMIC(test_reactor_common_creator_CREATE_PTR_Interface, Interface *, test3, 3);
    REQUIRE( test3->getValue() == 3 );
}