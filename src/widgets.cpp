#include "widgets.hpp"
#include "gtkmm/adjustment.h"
#include "gtkmm/button.h"
#include "gtkmm/checkbutton.h"
#include "gtkmm/dialog.h"
#include "gtkmm/enums.h"
#include "gtkmm/filechooser.h"
#include "gtkmm/filechooserdialog.h"
#include "gtkmm/label.h"
#include "gtkmm/progressbar.h"
#include "sigc++/functors/mem_fun.h"
#include "utils.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <vector>

Slider::Slider(const std::string &label, const double value,
               const double minValue, const double maxValue, const double step,
               const int digits)
    : mLabel(label), mValue(value), mSlider(Gtk::ORIENTATION_HORIZONTAL),
      mAdjustment(
          Gtk::Adjustment::create(value, minValue, maxValue, step, step, 0)) {

  mSlider.set_adjustment(mAdjustment);
  mSlider.set_digits(digits);
  mSlider.signal_value_changed().connect([this]() {
    const double value = mAdjustment->get_value();
    if (this->mChangeCallback) {
      this->mChangeCallback(value);
    } else {
      std::cout << "No callback defined" << std::endl;
    }
  });
}

Gtk::Scale &Slider::getScale() { return mSlider; }
void Slider::setValue(const double newVal) {
  mValue = newVal;
  mAdjustment->set_value(newVal);
}
double Slider::getValue() {
  mValue = mAdjustment->get_value();
  return mAdjustment->get_value();
}

void Slider::resetSlider(const double value, const double minValue,
                         const double maxValue, const double step,
                         const int digits) {

  mAdjustment =
      Gtk::Adjustment::create(value, minValue, maxValue, step, step, 0);
  mSlider.set_adjustment(mAdjustment);
  mSlider.set_digits(digits);
}
void Slider::setOnChangeCallback(std::function<void(double)> changeCallback) {
  mChangeCallback = changeCallback;
}
Gtk::Label &Slider::getLabel() { return mLabel; }

Button::Button(const std::string &label) {
  mButton.set_label(label);
  mButton.signal_clicked().connect([this]() {
    if (this->mOnButtonClick)
      this->mOnButtonClick();
  });
}
void Button::setOnButtonClick(std::function<void(void)> buttonClickedCallback) {
  mOnButtonClick = buttonClickedCallback;
}
void Button::setLabel(const std::string &label) { mButton.set_label(label); }
Gtk::Button &Button::getButtonWidget() { return mButton; }

FileChooser::FileChooser(const std::string &label, const std::string &nameLabel,
                         const bool multipleFiles,
                         Gtk::FileChooserAction action,
                         const Glib::RefPtr<Gtk::FileFilter> fileFilter)
    : mFileChooser("Select a file"), mNameLabel(nameLabel),
      mStateLabel("Ningun archivo ha sido seleccionado"),
      mFileChooserTrigger(label) {
  mFileChooser.set_action(action);
  mFileChooser.set_select_multiple(multipleFiles);
  mFileChooser.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  mFileChooser.add_button("_Open", Gtk::RESPONSE_OK);
  mFileChooser.set_current_folder(
      "/home/jorge1504/projects/stereocam2/stereoConfig");
  mFileChooser.signal_response().connect(
      sigc::mem_fun(*this, &FileChooser::onFileDialogResponse));

  // mFileChooserTrigger.setLabel("Open File");
  mFileChooserTrigger.setOnButtonClick([this]() { this->triggerCallback(); });

  if (action == FILE_SELECTOR) {
    mFileChooser.add_filter(fileFilter);
  }

  // file_chooser_dialog.set_title("Select a file or set of files");
}
void FileChooser::onFileDialogResponse(int response_id) {

  // Handle the response:
  switch (response_id) {
  case Gtk::ResponseType::RESPONSE_OK: {
    std::cout << "Open clicked." << std::endl;

    // Notice that this is a std::string, not a Glib::ustring.
    mFiles.clear();
    mFiles = mFileChooser.get_filenames();
    if (this->mOnFileSelected) {
      this->mOnFileSelected(mFileChooser.get_filenames());
    }
    mStateLabel.set_label(std::to_string(mFiles.size()) +
                          " archivos seleccionados");

    break;
  }
  case Gtk::ResponseType::RESPONSE_CANCEL: {
    std::cout << "Cancel clicked." << std::endl;
    break;
  }
  default: {
    std::cout << "Unexpected button clicked." << std::endl;
    break;
  }
  }
  // delete dialog;
}
void FileChooser::triggerCallback() {
  // Show the file chooser dialog
  int result = mFileChooser.run();

  // Check the user's response
  if (result == Gtk::RESPONSE_OK) {
    std::string selected_file = mFileChooser.get_filename();
    std::cout << "Selected file: " << selected_file << std::endl;
  } else {
    std::cout << "File selection canceled." << std::endl;
  }

  // Hide the file chooser dialog
  mFileChooser.hide();
}
Gtk::Button &FileChooser::getButtonWidget() {
  return mFileChooserTrigger.getButtonWidget();
}
Gtk::Label &FileChooser::getNameLabel() { return mNameLabel; }

Gtk::Label &FileChooser::getStateLabel() { return mStateLabel; }

const std::vector<std::string> &FileChooser::getSelectedFiles() {
  return mFiles;
}
void FileChooser::setOnFileSelectedCallback(
    std::function<void(const std::vector<std::string> &)> callback) {
  mOnFileSelected = callback;
}
CheckBox::CheckBox(const std::string &label)
    : mCheckButton(""), mNameLabel(label) {
  mCheckButton.signal_toggled().connect(
      sigc::mem_fun(*this, &CheckBox::onStateChange));
}
bool CheckBox::getValue() const { return mCheckButton.get_active(); }
void CheckBox::setValue(const bool newValue) {
  mCheckButton.set_active(newValue);
}

// void CheckBox::setLabel(const std::string &newLabel) {
//   mCheckButton.set_label(newLabel);
// }
Gtk::Label &CheckBox::getLabel() { return mNameLabel; }
Gtk::CheckButton &CheckBox::getCheckButton() { return mCheckButton; }
void CheckBox::setOnValueChanged(std::function<void(bool)> callback) {
  mOnChangeCallback = callback;
}
void CheckBox::onStateChange() {
  if (mOnChangeCallback) {
    mOnChangeCallback(this->getValue());
  }
}
ProgressBar::ProgressBar(const std::string &title) {
  mProgressBar.set_fraction(0.0);

  mTerminateButton.setOnButtonClick([this]() { this->terminate(); });

  mCompletedLabel.set_label(fmt::format("{}%", 0));
  mStateLabel.set_label("");
  mTitleLabel.set_label(title);
}
Gtk::ProgressBar &ProgressBar::getProgressBar() { return mProgressBar; }
Gtk::Button &ProgressBar::getTerminateButton() {
  return mTerminateButton.getButtonWidget();
}
Gtk::Label &ProgressBar::getProgressLabel() { return mCompletedLabel; }
Gtk::Label &ProgressBar::getStateLabel() { return mStateLabel; }
Gtk::Label &ProgressBar::getTitleLabel() { return mTitleLabel; }
void ProgressBar::setProgress(const std::double_t percentCompleted) {
  mProgressBar.set_fraction(percentCompleted);
  mCompletedLabel.set_label(fmt::format("{:0.2f}%", percentCompleted * 100));
}
void ProgressBar::setState(const std::string &state) {
  mStateLabel.set_label(state);
}
void ProgressBar::setTerminationCallback(std::function<void(void)> callback) {
  terminationFunction = callback;
}
void ProgressBar::terminate() {
  if (terminationFunction) {
    terminationFunction();
  }
}
