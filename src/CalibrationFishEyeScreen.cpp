#include "CalibrationFishEyeScreen.hpp"
Gtk::Box *CalibrationFishEyeScreen::getBox() { return &box; }
CalibrationFishEyeScreen::CalibrationFishEyeScreen() {
  grid.set_column_homogeneous(true);
  grid.set_row_homogeneous(true);
  grid.set_hexpand(true);
  grid.set_vexpand(true);
  grid.set_row_spacing(20);

  grid.attach(jsonConfigFile.getNameLabel(), 0, 0);
  grid.attach(leftFiles.getNameLabel(), 0, 1);
  grid.attach(rightFiles.getNameLabel(), 0, 2);
  grid.attach(patternRows.getLabel(), 0, 3);
  grid.attach(patternCols.getLabel(), 0, 4);

  grid.attach(jsonConfigFile.getStateLabel(), 2, 0);
  grid.attach(leftFiles.getStateLabel(), 2, 1);
  grid.attach(rightFiles.getStateLabel(), 2, 2);

  grid.attach(jsonConfigFile.getButtonWidget(), 1, 0);
  grid.attach(leftFiles.getButtonWidget(), 1, 1);
  grid.attach(rightFiles.getButtonWidget(), 1, 2);
  grid.attach(patternRows.getScale(), 1, 3);
  grid.attach(patternCols.getScale(), 1, 4);

  runButton.setOnButtonClick([this]() { this->onRun(); });

  box.pack_start(grid, Gtk::PACK_SHRINK);
  box.pack_start(runButton.getButtonWidget(), Gtk::PACK_SHRINK);
}
void CalibrationFishEyeScreen::onRun() {
  if (jsonConfigFile.getSelectedFiles().empty()) {
    return;
  }
  if (leftFiles.getSelectedFiles().empty()) {
    return;
  }
  if (rightFiles.getSelectedFiles().empty()) {
    return;
  }

  TaskManagerWidget::get().addTask(
      "Calibracion", [this](ProgressBar &progressBar) {
        ProgressNotifier progressNotifier;
        progressNotifier.progressNotifier = [&progressBar](double_t progress) {
          RunOnGui::get().run([progress, &progressBar]() {
            progressBar.setProgress(progress);
          });
        };
        progressNotifier.stateNotifier =
            [&progressBar](const std::string &state) {
              RunOnGui::get().run(
                  [state, &progressBar]() { progressBar.setState(state); });
            };
        progressBar.setProgress(0);
        progressBar.setState("Detectando patron");
        StereoCam::Calibration::StereoCalibParams params{};
        const std::filesystem::path jsonConfig =
            jsonConfigFile.getSelectedFiles()[0];
        const std::filesystem::path extrinsicsFile =
            jsonConfig.parent_path() / "extrinsics.yml";
        const std::filesystem::path intrinsicsFile =
            jsonConfig.parent_path() / "intrinsics.yml";
        const std::filesystem::path remapFile =
            jsonConfig.parent_path() / "stereoMap.yml";
        params.StereoConfigFile = jsonConfig;
        params.extrinsicsFile = extrinsicsFile;
        params.intrinsicsFile = intrinsicsFile;
        params.streoMapFile = remapFile;
        params.imagelistLeft = leftFiles.getSelectedFiles();
        params.imagelistRight = rightFiles.getSelectedFiles();
        params.boardSize =
            cv::Size{int(patternCols.getValue()), int(patternRows.getValue())};
        params.showRectified = false;
        params.useCalibrated = true;

        StereoCam::Calibration::StereoCalibFisheye(params, progressNotifier);
        progressBar.setProgress(100);
      });
}
