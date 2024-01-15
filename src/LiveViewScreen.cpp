#include "LiveViewScreen.hpp"
#include "CommandRunner.hpp"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "gtkmm/object.h"
#include <iostream>
#include <string>
#include <vector>
Gtk::Box *LiveViewScreen::getBox() { return &box; }
LiveViewScreen::LiveViewScreen() {
  grid.set_column_homogeneous(true);
  grid.set_row_homogeneous(true);
  grid.set_hexpand(true);
  grid.set_vexpand(true);
  grid.set_row_spacing(20);

  grid.attach(jsonConfigFile.getNameLabel(), 0, 0);
  grid.attach(outDirectory.getNameLabel(), 0, 1);
  grid.attach(remapFile.getNameLabel(), 0, 2);
  grid.attach(saveUnrectify.getLabel(), 0, 3);
  grid.attach(saveRectify.getLabel(), 0, 4);

  grid.attach(jsonConfigFile.getStateLabel(), 2, 0);
  grid.attach(outDirectory.getStateLabel(), 2, 1);
  grid.attach(remapFile.getStateLabel(), 2, 2);

  grid.attach(jsonConfigFile.getButtonWidget(), 1, 0);
  grid.attach(outDirectory.getButtonWidget(), 1, 1);
  grid.attach(remapFile.getButtonWidget(), 1, 2);
  grid.attach(saveUnrectify.getCheckButton(), 1, 3);
  grid.attach(saveRectify.getCheckButton(), 1, 4);

  // Gtk::Button *runButton = Gtk::manage(new Gtk::Button("Run"));
  runButton.setOnButtonClick([this]() { this->onRun(); });

  box.pack_start(grid, Gtk::PACK_SHRINK);
  box.pack_start(runButton.getButtonWidget(), Gtk::PACK_SHRINK);
}
void LiveViewScreen::onRun() {
  if (jsonConfigFile.getSelectedFiles().empty()) {
    return;
  }
  const auto jsonConfig = jsonConfigFile.getSelectedFiles()[0];
  const auto remap = remapFile.getSelectedFiles().empty()
                         ? ""
                         : remapFile.getSelectedFiles()[0];
  const auto outDir = outDirectory.getSelectedFiles().empty()
                          ? ""
                          : outDirectory.getSelectedFiles()[0];
  const auto saveRect = saveRectify.getValue();
  const auto saveUnrect = saveUnrectify.getValue();
}
