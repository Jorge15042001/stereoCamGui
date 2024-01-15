#include "utils.hpp"
#include "gtkmm/object.h"
#include <algorithm>
#include <iterator>
#include <mutex>
Glib::RefPtr<Gtk::FileFilter>
createFileFilter(const std::vector<std::string> &fileExtensions) {
  Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
  for (const auto &fileExtension : fileExtensions) {
    filter->add_pattern(fileExtension);
  }
  return filter;
}
Glib::RefPtr<Gtk::FileFilter> createFileFilter(const std::string &glob) {
  Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
  filter->add_pattern(glob);
  return filter;
}
Glib::RefPtr<Gtk::FileFilter>
createFileFilterMimeType(const std::vector<std::string> &mimeTypes) {
  Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
  for (const auto &mimeType : mimeTypes) {
    filter->add_mime_type(mimeType);
  }
  return filter;
}
Glib::RefPtr<Gtk::FileFilter>
createFileFilterMimeType(const std::string &mimeType) {
  Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();
  filter->add_mime_type(mimeType);
  return filter;
}

Gtk::Label *createLabel(const std::string &label) {
  return Gtk::manage(new Gtk::Label(label));
}
std::vector<Gtk::Label *> createLabels(const std::vector<std::string> &labels) {
  std::vector<Gtk::Label *> gtkLabels;
  gtkLabels.reserve(labels.size());
  std::transform(labels.begin(), labels.end(), std::back_inserter(gtkLabels),
                 createLabel);
  return gtkLabels;
}
GuiRunner::GuiRunner() : mCond(nullptr) {}
bool GuiRunner::isReady() const { return ready; }
void GuiRunner::run(std::function<void(void)> callback,
                    std::condition_variable &cond) {
  dispatecher.connect([callback, this, &cond]() {
    ready = false;
    callback();
    ready = true;
    cond.notify_one();
  });
  dispatecher.emit();
}
RunOnGui::RunOnGui() : runners(50) {}
void RunOnGui::run(std::function<void(void)> callback) {
  const auto readyRunner =
      std::find_if(runners.begin(), runners.end(),
                   [](const GuiRunner &runner) { return runner.isReady(); });
  if (readyRunner == runners.end()) {
    std::unique_lock<std::mutex> lock(readyRunnerCond_m);
    readyRunnerCond.wait(lock);
    run(callback);
  }
  readyRunner->run(callback, readyRunnerCond);
}
RunOnGui &RunOnGui::get() {
  static RunOnGui instance;
  return instance;
}
