#pragma once

#include "MultiThreadRender/TaskQueue.hpp"
#include "MultiThreadRender/TaskBase.hpp"

namespace fly
{
bool RenderTaskQueue::Initialize()
{
    renderTaskQueue = std::queue<TaskBase *>();
}
bool RenderTaskQueue::Finalize()
{
    while (renderTaskQueue.size() > 0)
    {
        TaskBase *task = renderTaskQueue.front();
        renderTaskQueue.pop();
        delete task;
    }
}

/// 添加任务到队列
/// \param render_task
void RenderTaskQueue::Push(TaskBase *render_task)
{
    renderTaskQueue.push(render_task);
}

/// 队列中是否没有了任务
/// \return
bool RenderTaskQueue::Empty()
{
    return renderTaskQueue.empty();
}
/// 获取队列中第一个任务
/// \return
TaskBase *RenderTaskQueue::Front()
{
    return renderTaskQueue.front();
}

/// 弹出队列中第一个任务
void RenderTaskQueue::Pop()
{
    renderTaskQueue.pop();
}

/// 获取队列中的任务数量
size_t RenderTaskQueue::Size()
{
    return renderTaskQueue.size();
}

}  // namespace fly