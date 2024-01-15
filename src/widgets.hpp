#pragma once

#include "gtkmm/adjustment.h"
#include "gtkmm/button.h"
#include "gtkmm/checkbutton.h"
#include "gtkmm/filechooser.h"
#include "gtkmm/label.h"
#include "gtkmm/progressbar.h"
#include <cmath>
#include <cstddef>
#include <functional>
#include <gtkmm.h>
#include <string>
#include <vector>

class Control {};

class Slider {
public:
  Slider(const std::string &label, const double value, const double minValue,
         const double maxValue, const double step, const int digit = 0);
  Gtk::Scale &getScale();
  void setValue(const double newVal);
  double getValue();
  void resetSlider(const double value, const double minValue,
                   const double maxValue, const double step,
                   const int digits = 0);
  void setOnChangeCallback(std::function<void(double)> changeCallback);
  Gtk::Label &getLabel();

private:
  double mValue;
  Gtk::Scale mSlider;
  Glib::RefPtr<Gtk::Adjustment> mAdjustment;
  std::function<void(double)> mChangeCallback = [](double) {};
  Gtk::Label mLabel;
};

class Button {
  Gtk::Button mButton;

  std::function<void(void)> mOnButtonClick = []() {};

public:
  Button(const std::string &label = "");
  void setOnButtonClick(std::function<void(void)> buttonClickedCallback);
  void setLabel(const std::string &label);
  Gtk::Button &getButtonWidget();
};
class FileChooser {

  std::vector<std::string> mFiles;
  Button mFileChooserTrigger;
  Gtk::FileChooserDialog mFileChooser;
  Gtk::Label mStateLabel;
  Gtk::Label mNameLabel;
  void clearFiles();
  void triggerCallback();
  void onFileDialogResponse(int respose_id);

  std::function<void(const std::vector<std::string> &)> mOnFileSelected =
      [](const std::vector<std::string> &) {};

public:
  FileChooser(const std::string &label, const std::string &nameLabel,
              const bool multipleFiles = false,
              Gtk::FileChooserAction action =
                  Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN,
              const Glib::RefPtr<Gtk::FileFilter> fileFilter =
                  Gtk::FileFilter::create());
  Gtk::Button &getButtonWidget();
  const std::vector<std::string> &getSelectedFiles();
  void setOnFileSelectedCallback(
      std::function<void(const std::vector<std::string> &)> callback);
  Gtk::Label &getNameLabel();
  Gtk::Label &getStateLabel();
};
class CheckBox {
  Gtk::CheckButton mCheckButton;
  Gtk::Label mNameLabel;
  std::function<void(bool)> mOnChangeCallback = [](bool) {};

public:
  CheckBox(const std::string &label);
  bool getValue() const;
  void setValue(const bool newValue);
  // void setLabel(const std::string &label);
  Gtk::Label &getLabel();
  void setOnValueChanged(std::function<void(bool)> callback);
  Gtk::CheckButton &getCheckButton();
  void onStateChange();
};

class ProgressBar {
  Gtk::ProgressBar mProgressBar;
  Gtk::Label mCompletedLabel;
  Gtk::Label mStateLabel;
  Gtk::Label mTitleLabel;
  Button mTerminateButton{"Cancelar"};
  std::double_t percentCompleted = 0;
  std::function<void(void)> terminationFunction;
  void terminate();

public:
  ProgressBar(const std::string &title);
  Gtk::ProgressBar &getProgressBar();
  Gtk::Label &getStateLabel();
  Gtk::Label &getProgressLabel();
  Gtk::Label &getTitleLabel();

  Gtk::Button &getTerminateButton();
  void setTerminationCallback(std::function<void(void)> callback);
  void setState(const std::string &state);
  void setProgress(const std::double_t percentCompleted);
};
