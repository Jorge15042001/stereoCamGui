#include <gtkmm.h>
#include <iostream>
#include <vector>

#include "CalibrationFishEyeScreen.hpp"
#include "CalibrationScreen.hpp"
#include "DepthScreen.hpp"
#include "LiveViewScreen.hpp"
#include "RectifyScreen.hpp"
#include "TaskManger.hpp"
#include "captureScreen.hpp"
#include "gtkmm/box.h"
#include "gtkmm/hvbox.h"
#include "gtkmm/object.h"
#include "widgets.hpp"
#include <gtkmm.h>
#include <iostream>

class MainWindow : public Gtk::Window {
private:
  Gtk::CheckButton *checkbox;
  // Gtk::Scale *slider;
  CaptureScreen captureScreen;
  CalibrationScreen calibScreen;
  CalibrationFishEyeScreen calibFishEyeScreen;
  LiveViewScreen liveviewScreen;
  RectifyScreen rectifyScreen;
  DepthScreen depthScreen;
  Gtk::Box mainMenu{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Box mainMenuItems{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::VBox rootBox{};
  Gtk::VBox mainBox{};
  Button homeButton{"Inicio"};

  void createButtons() {
    mButtons.clear();
    mButtons.reserve(subcommands.size());
    for (const auto &subcommand : subcommands) {
      mButtons.emplace_back(subcommand.first);
      mButtons[mButtons.size() - 1].setOnButtonClick(
          [this, subcommand]() { this->create_config_page(subcommand.first); });
    }
  }

public:
  MainWindow() {
    set_title("Command GUI");
    set_border_width(10);
    set_default_size(400, 300);

    // Create the header bar
    Gtk::HeaderBar *headerBar = Gtk::manage(new Gtk::HeaderBar());
    headerBar->set_show_close_button(true); // Show the standard close button

    // Create the home button
    homeButton.setOnButtonClick([this]() { this->on_home_button_clicked(); });
    headerBar->pack_start(homeButton.getButtonWidget());

    // Set the header bar in the window
    set_titlebar(*headerBar);
    rootBox.set_hexpand(true);
    rootBox.set_vexpand(true);
    rootBox.set_spacing(10);
    rootBox.pack_start(TaskManagerWidget::get(), Gtk::PACK_SHRINK);
    rootBox.pack_start(mainBox, Gtk::PACK_EXPAND_WIDGET);
    add(rootBox);

    mainBox.set_hexpand(false);
    mainBox.set_vexpand(false);
    mainBox.set_spacing(10);

    mainBox.pack_start(*captureScreen.getBox(), Gtk::PACK_EXPAND_WIDGET);
    mainBox.pack_start(*calibScreen.getBox(), Gtk::PACK_EXPAND_WIDGET);
    mainBox.pack_start(*calibFishEyeScreen.getBox(), Gtk::PACK_EXPAND_WIDGET);
    mainBox.pack_start(*liveviewScreen.getBox(), Gtk::PACK_EXPAND_WIDGET);
    mainBox.pack_start(*rectifyScreen.getBox(), Gtk::PACK_EXPAND_WIDGET);
    mainBox.pack_start(*depthScreen.getBox(), Gtk::PACK_EXPAND_WIDGET);

    // Create the home screen
    createButtons();
    for (auto &button : mButtons) {
      mainMenuItems.pack_start(button.getButtonWidget(), Gtk::PACK_SHRINK);
    }
    mainMenu.pack_start(mainMenuItems, Gtk::PACK_EXPAND_PADDING);
    mainBox.pack_start(mainMenu, Gtk::PACK_EXPAND_WIDGET);
    hideAll();
    show_all_children();
    create_home_screen();
  }

protected:
  void hideAll() {
    captureScreen.getBox()->hide();
    calibScreen.getBox()->hide();
    calibFishEyeScreen.getBox()->hide();
    liveviewScreen.getBox()->hide();
    rectifyScreen.getBox()->hide();
    depthScreen.getBox()->hide();
    mainMenu.hide();
  }

  // Function to create the capture page
  void create_capture_page() {
    hideAll();

    captureScreen.getBox()->show_all();

    // show_all_children(); // Show all added widgets
  }
  void create_calibration_page() {
    hideAll();

    calibScreen.getBox()->show_all();
    // add(*box);

    // show_all_children(); // Show all added widgets
  }
  void create_fiseye_calibration_page() {
    hideAll();

    calibFishEyeScreen.getBox()->show_all();
    // add(*box);

    // show_all_children(); // Show all added widgets
  }
  void create_liveview_page() {
    hideAll();

    liveviewScreen.getBox()->show_all();

    // show_all_children(); // Show all added widgets
  }
  void create_rectify_screen() {
    hideAll();

    rectifyScreen.getBox()->show_all();
    // add(*box);

    // show_all_children(); // Show all added widgets
  }
  void create_depth_screen() {
    hideAll();

    depthScreen.getBox()->show_all();
    // add(*box);

    // show_all_children(); // Show all added widgets
  }

  // Function to create the home screen
  void create_home_screen() {
    // Clear existing widgets
    hideAll();

    // Create a vertical box layout
    mainMenu.show_all();
    // queue_draw();
    // show_all_children(); // Show all added widgets
  }

  // Function to create the configuration page for a subcommand
  void create_config_page(const std::string &subcommand) {
    // Clear existing widgets
    hideAll();

    // Create a vertical box layout for the configuration page
    // Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    // add(*box);

    // Add widgets for configuring parameters based on subcommand
    if (subcommand == "capture") {
      create_capture_page();

    } else if (subcommand == "calibration") {
      create_calibration_page();
    } else if (subcommand == "fisheye_calibration") {
      create_fiseye_calibration_page();

    } else if (subcommand == "liveview") {
      create_liveview_page();
    } else if (subcommand == "rectify") {
      create_rectify_screen();
    } else if (subcommand == "depth") {
      create_depth_screen();
    }

    // Add more conditions for other subcommands...
  }

  // Event handler for home button
  void on_home_button_clicked() { create_home_screen(); }

private:
  std::vector<Button> mButtons;
  const std::vector<std::pair<std::string, std::string>> subcommands = {
      {"capture", "Capture images with uncalibrated stereo cameras"},
      {"calibration", "Perform image rectification and stereo calibration from "
                      "a set of images"},
      {"fisheye_calibration",
       "Perform image rectification and stereo calibration from set of images "
       "for fisheye cameras"},
      {"liveview", "Live view (record all frames)"},
      {"rectify", "rectify images"},
      {"depth", "Compute depth data for image list"}};
};

int main(int argc, char **argv) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  MainWindow mainWindow;

  // Start the application main loop
  return app->run(mainWindow);
}
// #include <gtkmm.h>
//
// class SubPage : public Gtk::Box {
// public:
//   SubPage(const Glib::ustring &title, Gtk::Window &parent) : parent_(parent)
//   {
//     label.set_text(title);
//     button_back.set_label("Back");
//     button_back.signal_clicked().connect(
//         sigc::mem_fun(*this, &SubPage::on_back_clicked));
//
//     pack_start(label, Gtk::PACK_SHRINK);
//     pack_start(button_back, Gtk::PACK_SHRINK);
//   }
//
//   void on_back_clicked() {
//     hide();
//     parent_.present(); // Show the parent window
//   }
//
// private:
//   Gtk::Label label;
//   Gtk::Button button_back;
//   Gtk::Window &parent_;
// };
//
// class MainWindow2 : public Gtk::Window {
// public:
//   MainWindow2() {
//     set_default_size(400, 200);
//
//     button_open.set_label("Open SubPage");
//     button_open.signal_clicked().connect(
//         sigc::mem_fun(*this, &MainWindow2::on_open_clicked));
//
//     box.pack_start(button_open, Gtk::PACK_SHRINK);
//     add(box);
//   }
//
//   void on_open_clicked() {
//     SubPage *subpage = new SubPage("SubPage", *this);
//     subpage->show_all();
//     box.pack_start(*subpage, Gtk::PACK_SHRINK); // Add SubPage to the
//     container
//   }
//
// private:
//   Gtk::Box box;
//   Gtk::Button button_open;
// };
//
// int main(int argc, char *argv[]) {
//   // Initialize GTKmm
//   Gtk::Main kit(argc, argv);
//
//   // Create the main window
//   MainWindow2 main_window;
//
//   // Display the main window
//   main_window.show_all();
//
//   // Start the GTK main loop
//   Gtk::Main::run();
//
//   return 0;
// }
