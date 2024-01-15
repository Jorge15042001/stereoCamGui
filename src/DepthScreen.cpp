#include "DepthScreen.hpp"
Gtk::Box *DepthScreen::getBox() { return &box; }
DepthScreen::DepthScreen() {
  grid.set_column_homogeneous(true);
  grid.set_row_homogeneous(true);
  grid.set_hexpand(true);
  grid.set_vexpand(true);
  grid.set_row_spacing(20);

  grid.attach(jsonConfigFile.getNameLabel(), 0, 0);
  grid.attach(remapFile.getNameLabel(), 0, 1);
  grid.attach(extrinsicsFile.getNameLabel(), 0, 2);
  grid.attach(leftFiles.getNameLabel(), 0, 3);
  grid.attach(rightFiles.getNameLabel(), 0, 4);
  grid.attach(p1.getLabel(), 0, 5);
  grid.attach(p2.getLabel(), 0, 6);
  grid.attach(scale.getLabel(), 0, 7);
  grid.attach(lambda.getLabel(), 0, 8);
  grid.attach(sigma.getLabel(), 0, 9);
  grid.attach(minDistance.getLabel(), 0, 10);
  grid.attach(maxDistance.getLabel(), 0, 11);
  grid.attach(saveDepthMap.getLabel(), 0, 12);
  grid.attach(saveRawDepth.getLabel(), 0, 13);
  grid.attach(savePointCloud.getLabel(), 0, 14);

  grid.attach(jsonConfigFile.getStateLabel(), 2, 0);
  grid.attach(remapFile.getStateLabel(), 2, 1);
  grid.attach(extrinsicsFile.getStateLabel(), 2, 2);
  grid.attach(leftFiles.getStateLabel(), 2, 3);
  grid.attach(rightFiles.getStateLabel(), 2, 4);

  grid.attach(jsonConfigFile.getButtonWidget(), 1, 0);
  grid.attach(remapFile.getButtonWidget(), 1, 1);
  grid.attach(extrinsicsFile.getButtonWidget(), 1, 2);
  grid.attach(leftFiles.getButtonWidget(), 1, 3);
  grid.attach(rightFiles.getButtonWidget(), 1, 4);
  grid.attach(p1.getScale(), 1, 5);
  grid.attach(p2.getScale(), 1, 6);
  grid.attach(p2.getScale(), 1, 6);
  grid.attach(scale.getScale(), 1, 7);
  grid.attach(lambda.getScale(), 1, 8);
  grid.attach(sigma.getScale(), 1, 9);
  grid.attach(minDistance.getScale(), 1, 10);
  grid.attach(maxDistance.getScale(), 1, 11);
  grid.attach(saveDepthMap.getCheckButton(), 1, 12);
  grid.attach(saveRawDepth.getCheckButton(), 1, 13);
  grid.attach(savePointCloud.getCheckButton(), 1, 14);

  runButton.setOnButtonClick([this]() { this->onRun(); });

  box.pack_start(grid, Gtk::PACK_EXPAND_PADDING);
  box.pack_start(runButton.getButtonWidget(), Gtk::PACK_SHRINK);
}
void DepthScreen::onRun() {

  const auto jsonConfig = jsonConfigFile.getSelectedFiles();
  const auto remap = remapFile.getSelectedFiles();
  const auto leftImages = leftFiles.getSelectedFiles();
  const auto rightImgaes = rightFiles.getSelectedFiles();
  std::cout << "calibration screen running command " << jsonConfig[0]
            << remap[0] << " " << leftImages.size() << " " << rightImgaes.size()
            << std ::endl;
}
