#include "RectifyScreen.hpp"
Gtk::Box *RectifyScreen::getBox() { return &box; }
RectifyScreen::RectifyScreen() {
  grid.set_column_homogeneous(true);
  grid.set_row_homogeneous(true);
  grid.set_hexpand(true);
  grid.set_vexpand(true);
  grid.set_row_spacing(20);

  grid.attach(remapFile.getNameLabel(), 0, 0);
  grid.attach(leftFiles.getNameLabel(), 0, 1);
  grid.attach(rightFiles.getNameLabel(), 0, 2);

  grid.attach(remapFile.getStateLabel(), 2, 0);
  grid.attach(leftFiles.getStateLabel(), 2, 1);
  grid.attach(rightFiles.getStateLabel(), 2, 2);

  grid.attach(remapFile.getButtonWidget(), 1, 0);
  grid.attach(leftFiles.getButtonWidget(), 1, 1);
  grid.attach(rightFiles.getButtonWidget(), 1, 2);

  runButton.setOnButtonClick([this]() { this->onRun(); });

  box.pack_start(grid, Gtk::PACK_SHRINK);
  box.pack_start(runButton.getButtonWidget(), Gtk::PACK_SHRINK);
}
void RectifyScreen::onRun() {

  const auto remap = remapFile.getSelectedFiles();
  const auto leftImages = leftFiles.getSelectedFiles();
  const auto rightImgaes = rightFiles.getSelectedFiles();
  std::cout << "running recification" << std::endl;
}
