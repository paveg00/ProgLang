//
// Created by pavel on 05.04.2022.
//


#include <TryCatchThrowMacros.hpp>

EXCEPTION_ON

struct A {
    A() {
        LOG("Construct A");
    }

    ~A() {
        LOG("Destruct A");
    }
};

struct B: A {
    B() {
        LOG("Construct B");
    }

    virtual ~B() {
        LOG("Destruct B");
    }
};

void easy_test() {
    TRY {
            LOG("Do smthing before throw")
            THROW(EXC_CODE::MEM)
            LOG("Do smthing after throw")
        } CATCH(EXC_CODE::MEM) {
            LOG("Do smthing on catch")
        }
    END_CATCH
}

void easy_test_destructor() {
    TRY {
            A a; RegisterGuard(A, a);
            LOG("Do smthing before throw")
            THROW(EXC_CODE::MEM)
            LOG("Do smthing after throw")
        } CATCH(EXC_CODE::MEM) {
            LOG("Do smthing on catch")
        }
    END_CATCH
}

void not_caught_exception() {
    TRY {
            A a; RegisterGuard(A, a);
            LOG("Do smthing before throw")
            THROW(EXC_CODE::MEM)
            LOG("Do smthing after throw")
        } CATCH(EXC_CODE::EMPTY) {
            LOG("Do smthing on catch")
        }
    END_CATCH
}

void throwable_func() {
    TRY {
            LOG("Do smthing before throw in throwable_func")
            B a; RegisterGuard(B, a);
            THROW(EXC_CODE::MEM)
            B b; RegisterGuard(B, b);
            LOG("Do smthing after throw in throwable_func")
        } CATCH(EXC_CODE::EMPTY) {
            LOG("Do smthing in throwable_func")
        }
    END_CATCH
}

void long_jump_exception() {
    TRY {
            LOG("Do smthing before throw")
            throwable_func();
            LOG("Do smthing after throw")
        } CATCH(EXC_CODE::MEM) {
            LOG("Do smthing on catch")
        }
    END_CATCH
}

struct TestPlugin {
    static void Test(std::function<void()> test, std::string_view test_name) {
        std::cout << "|------------------Test_" << test_name << "------------------|" << std::endl;
        test();
        std::cout << "|------------------TestEnd------------------|" << std::endl;
    }
};

int main() {
    TestPlugin::Test(easy_test, "easy_test");
    TestPlugin::Test(easy_test_destructor, "easy_test_destructor");
    TestPlugin::Test(long_jump_exception, "long_jump_exception");
    TestPlugin::Test(not_caught_exception, "not_caught_exception");
}