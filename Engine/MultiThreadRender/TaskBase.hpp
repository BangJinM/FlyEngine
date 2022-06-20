#pragma once

namespace fly
{

class TaskBase
{
public:
    TaskBase() {}
    virtual ~TaskBase() {}

public:
    bool need_return_result_ = false;  //是否需要回传结果
    bool return_result_set_  = false;  //是否设置好了回传结果
};

}  // namespace fly
