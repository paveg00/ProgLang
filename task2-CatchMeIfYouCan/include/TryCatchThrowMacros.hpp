//
// Created by pavel on 05.04.2022.
//

#pragma once

#include <iostream>
#include <csetjmp>
#include <stack>
#include <functional>

#define LOG(str) std::cout << str << std::endl;

struct JumpPoint {
    jmp_buf *env;
    std::vector<std::function<void()>> objects;
};

enum EXC_CODE {
    MEM,
    EMPTY,
};

#define EXCEPTION_ON \
std::stack<JumpPoint> jump_points; \
EXC_CODE curr_exc_code;            \
bool exc_mode = false;



#define TRY \
{           \
LOG("TRY")\
jmp_buf env;\
jump_points.push(JumpPoint{.env=&env});\
int val = setjmp (env);\
if (val == 0)

#define THROW(EX_CODE)     \
LOG("THROW")      \
if (exc_mode) {            \
    LOG("throw while another exception processing")                       \
    exit(1);                         \
}\
auto* throw_env = jump_points.top().env; \
exc_mode = true;\
longjmp(*throw_env, EX_CODE);

#define CATCH(exc_code) \
else {                  \
    LOG("Clear stack CATCH")\
    for (int i = jump_points.top().objects.size() - 1; i >= 0; --i) {\
        jump_points.top().objects[i]();\
    }\
    LOG("CATCH")  \
    jump_points.pop(); \
    if ((exc_code) != curr_exc_code) {\
        if (jump_points.empty()) {\
            LOG("CATCH failed - exit(1)")            \
            exit(1);                        \
    }               \
        auto *env = jump_points.top().env;                 \
        longjmp(*env, exc_code);               \
        LOG("CATCH failed - go up") \
    }                   \
} \
if (exc_mode)              \

#define END_CATCH exc_mode = false; }


#define RegisterGuard(T, obj) \
jump_points.top().objects.emplace_back([t = &(obj)]() { t->~T(); })

