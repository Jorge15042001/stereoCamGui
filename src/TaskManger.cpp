#include "TaskManger.hpp"
#include "glibmm/main.h"
#include "glibmm/miscutils.h"
#include "glibmm/threads.h"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "gtkmm/widget.h"
#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>
TaskWidget::TaskWidget(
    const std::string &title,
    std::function<void(ProgressBar &progressBar)> taskFunction)
    : mProgressBar(title), mFunction(taskFunction) {
  set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  set_spacing(10);
  set_hexpand(true);
  set_vexpand(false);
  std::cout << "creating task widget" << std::endl;

  pack_start(mProgressBar.getTitleLabel(), Gtk::PACK_SHRINK);
  pack_start(mProgressBar.getProgressBar(), Gtk::PACK_EXPAND_WIDGET);
  pack_start(mProgressBar.getStateLabel(), Gtk::PACK_SHRINK);
  pack_start(mProgressBar.getProgressLabel(), Gtk::PACK_SHRINK);
  pack_start(mProgressBar.getTerminateButton(), Gtk::PACK_SHRINK);

  std::cout << "creating task function" << std::endl;
  mTAsk = std::thread([this]() {
    std::cout << "running task" << std::endl;
    mFunction(this->mProgressBar);
    std::cout << "task concluded" << std::endl;
    gdk_threads_add_idle(
        [](void *thisPtr) -> gboolean {
          TaskWidget *task = static_cast<TaskWidget *>(thisPtr);
          task->get_parent()->remove(*task);
          return false;
        },
        this);

    if (mOnTaskCompleted) {
      mOnTaskCompleted();
    }
  });
}
void TaskWidget::setTaskCompletedCallback(std::function<void(void)> callback) {
  mOnTaskCompleted = callback;
}

TaskManagerWidget::TaskManagerWidget() {
  set_orientation(Gtk::ORIENTATION_VERTICAL);
  set_spacing(10);
  set_hexpand(true);
  set_vexpand(false);
}
void TaskManagerWidget::addTask(
    const std::string &title,
    std::function<void(ProgressBar &progressBar)> taskFunction) {

  auto *taskPtr = Gtk::manage(new TaskWidget(title, taskFunction));
  pack_start(*taskPtr, Gtk::PACK_SHRINK);
  show_all_children();
}
TaskManagerWidget &TaskManagerWidget::get() {
  static TaskManagerWidget instance;
  return instance;
}
