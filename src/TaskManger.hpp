#pragma once
#include "gtkmm/box.h"
#include "gtkmm/progressbar.h"
#include "widgets.hpp"
#include <cstddef>
#include <functional>
#include <gtkmm.h>
#include <list>
#include <mutex>
#include <thread>
#include <vector>
class TaskWidget : public Gtk::Box {
  ProgressBar mProgressBar;
  std::thread mTAsk;
  std::function<void(void)> mOnTaskCompleted;

public:
  std::function<void(ProgressBar &progressBar)> mFunction;
  TaskWidget(const std::string &title,
             std::function<void(ProgressBar &progressBar)> taskFunction);
  [[deprecated]] void
  setTaskCompletedCallback(std::function<void(void)> callback);
};
class TaskManagerWidget : public Gtk::Box {

  TaskManagerWidget();

public:
  void addTask(const std::string &title,
               std::function<void(ProgressBar &progressBar)> taskFunction);
  static TaskManagerWidget &get();
};
