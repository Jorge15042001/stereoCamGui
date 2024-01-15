#pragma once
#include "gtkmm.h"
#include "gtkmm/adjustment.h"
#include "gtkmm/button.h"
#include "gtkmm/checkbutton.h"
#include "gtkmm/dialog.h"
#include "gtkmm/enums.h"
#include "gtkmm/filechooser.h"
#include "gtkmm/filechooserdialog.h"
#include "gtkmm/label.h"
#include "sigc++/functors/mem_fun.h"
#include "sigc++/functors/ptr_fun.h"
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

const static Gtk::FileChooserAction FILE_SELECTOR =
    Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN;
const static Gtk::FileChooserAction FOLDER_SELECTOR =
    Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER;

Glib::RefPtr<Gtk::FileFilter>
createFileFilter(const std::vector<std::string> &filesExts);
Glib::RefPtr<Gtk::FileFilter> createFileFilter(const std::string &glob);
Glib::RefPtr<Gtk::FileFilter>
createFileFilterMimeType(const std::vector<std::string> &filesExts);
Glib::RefPtr<Gtk::FileFilter>
createFileFilterMimeType(const std::string &mimeType);

static const Glib::RefPtr<Gtk::FileFilter> JSON_FILTER =
    createFileFilterMimeType("application/json");
static const Glib::RefPtr<Gtk::FileFilter> YML_FILTER =
    createFileFilterMimeType("application/x-yaml");
static const Glib::RefPtr<Gtk::FileFilter> IMG_FILTER =
    createFileFilterMimeType("image/*");

Gtk::Label *createLabel(const std::string &label);
std::vector<Gtk::Label *> createLabels(const std::vector<std::string> &labels);

class GuiRunner {
  Glib::Dispatcher dispatecher{};
  bool ready{true};
  std::condition_variable *mCond;

public:
  GuiRunner();
  bool isReady() const;
  void run(std::function<void(void)> callback, std::condition_variable &cond);
};

class RunOnGui {
  std::vector<GuiRunner> runners;
  std::condition_variable readyRunnerCond;
  std::mutex readyRunnerCond_m;

  RunOnGui();

public:
  static RunOnGui &get();

  void run(std::function<void(void)> callback);
};
