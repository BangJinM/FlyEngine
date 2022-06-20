#pragma once

#include <queue>

#include "Common/IRuntimeModule.hpp"

class TaskBase;

namespace fly
{
/// 定义一个渲染任务队列
class RenderTaskQueue : public IRuntimeModule
{
private:
    std::queue<TaskBase *> renderTaskQueue;  //渲染任务队列

public:
    virtual bool Initialize();

    virtual bool Finalize();

    virtual void Tick(float deltaTime);

    /// 添加任务到队列
    /// \param render_task
    void Push(TaskBase *render_task);

    /// 队列中是否没有了任务
    /// \return
    bool Empty();
    /// 获取队列中第一个任务
    /// \return
    TaskBase *Front();

    /// 弹出队列中第一个任务
    void Pop();

    /// 获取队列中的任务数量
    size_t Size();
};
}  // namespace fly