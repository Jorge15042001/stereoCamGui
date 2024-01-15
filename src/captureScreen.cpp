#include "captureScreen.hpp"
#include "TaskManger.hpp"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "gtkmm/object.h"
#include "utils.hpp"
#include "widgets.hpp"
#include <chrono>
#include <functional>
#include <string>
#include <thread>
#include <vector>
CaptureScreen::CaptureScreen() {
  // Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
  // Gtk::Grid *grid = Gtk::manage(new Gtk::Grid{});
  grid.set_column_homogeneous(true);
  grid.set_row_homogeneous(true);
  grid.set_hexpand(true);
  grid.set_vexpand(true);
  grid.set_row_spacing(20);

  grid.attach(jsonConfigFile.getNameLabel(), 0, 0);
  grid.attach(outDirectory.getNameLabel(), 0, 1);
  grid.attach(remapFile.getNameLabel(), 0, 2);

  grid.attach(jsonConfigFile.getStateLabel(), 2, 0);
  grid.attach(outDirectory.getStateLabel(), 2, 1);
  grid.attach(remapFile.getStateLabel(), 2, 2);

  grid.attach(jsonConfigFile.getButtonWidget(), 1, 0);
  grid.attach(remapFile.getButtonWidget(), 1, 1);
  grid.attach(outDirectory.getButtonWidget(), 1, 2);

  // Gtk::Button *runButton = Gtk::manage(new Gtk::Button("Run"));
  runButton.setOnButtonClick([this]() { this->onRun(); });

  box.pack_start(grid, Gtk::PACK_SHRINK);
  box.pack_start(runButton.getButtonWidget(), Gtk::PACK_SHRINK);
}
Gtk::Box *CaptureScreen::getBox() { return &box; }

void CaptureScreen::onRun() {

  // const auto jsonConfig = jsonConfigFile.getSelectedFiles();
  // const auto remap = remapFile.getSelectedFiles();
  // const auto outDir = outDirectory.getSelectedFiles();
  // std::cout << "capture screen running command " << jsonConfig[0] << remap[0]
  //           << outDir[0] << std ::endl;
  TaskManagerWidget::get().addTask("Capturando", [](ProgressBar &pb) {
    RunOnGui::get().run([&pb](void) -> void { pb.setState("capturando"); });
    for (int i = 0; i < 3; i++) {
      std::this_thread::sleep_for(std::chrono::seconds{1});
      RunOnGui::get().run(
          [&pb, i](void) -> void { pb.setProgress(std::double_t(i + 1) / 3); });
    }
  });
}
