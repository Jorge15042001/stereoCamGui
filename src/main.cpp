#include <gtkmm.h>
#include <iostream>
#include <vector>

#include <gtkmm.h>
#include <iostream>

class MainWindow : public Gtk::Window {
private:
  Gtk::CheckButton *checkbox;
  Gtk::Scale *slider;

public:
  MainWindow() {
    set_title("Command GUI");
    set_border_width(10);
    set_default_size(400, 300);

    // Create the header bar
    Gtk::HeaderBar *headerBar = Gtk::manage(new Gtk::HeaderBar());
    headerBar->set_show_close_button(true); // Show the standard close button

    // Create the home button
    Gtk::Button *homeButton = Gtk::manage(new Gtk::Button("Home"));
    homeButton->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_home_button_clicked));
    headerBar->pack_start(*homeButton);

    // Set the header bar in the window
    set_titlebar(*headerBar);

    // Create the home screen
    create_home_screen();

    show_all_children();
  }

protected:
  void cleanScreen() {
    std::cout << "cleaning screen\n";
    auto children = get_children();
    for (auto child : children) {
      Gtk::Container::remove(*child);
    }
    std::cout << "screen cleaned\n";
  }
  // Function to create the capture page
  // Function to create the capture page
  void create_capture_page() {
    cleanScreen();

    // Create a vertical box layout
    Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*box);

    // Create widgets for the "capture" subcommand parameters
    // Example: Checkbox for boolean variable
    checkbox = Gtk::manage(new Gtk::CheckButton("Use Calibration"));
    box->pack_start(*checkbox, Gtk::PACK_SHRINK);

    // Example: Slider for a number (adjust as needed)
    slider = Gtk::manage(new Gtk::Scale(Gtk::ORIENTATION_HORIZONTAL));
    slider->set_range(0, 100);
    slider->set_value(50);
    box->pack_start(*slider, Gtk::PACK_SHRINK);

    // Create a "Run" button
    Gtk::Button *runButton = Gtk::manage(new Gtk::Button("Run"));
    runButton->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_run_capture_button_clicked));
    box->pack_start(*runButton, Gtk::PACK_SHRINK);

    show_all_children(); // Show all added widgets
  }

  // Event handler for "Run" button for the "capture" subcommand
  void on_run_capture_button_clicked() {
    // Extract the values from widgets and construct the command
    bool useCalibration = checkbox->get_active();
    double sliderValue = slider->get_value();

    // Construct the command string based on the values
    // This is a placeholder command, replace it with your actual command
    std::string command = "your_capture_command_here";
    // Append command line arguments based on the parameter values

    // Execute the command (use std::system or other methods)
    int result = std::system(command.c_str());

    // Check the result, handle errors or update UI as needed
    if (result == 0) {
      std::cout << "Capture command executed successfully." << std::endl;
    } else {
      std::cerr << "Error executing capture command." << std::endl;
    }
  }

  // Function to create the home screen
  void create_home_screen() {
    // Clear existing widgets
    cleanScreen();

    // Create a vertical box layout
    Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*box);

    // Create buttons for each subcommand
    for (const auto &subcommand : subcommands) {
      std::cout << "addming command for " << subcommand.first << " option"
                << std::endl;
      Gtk::Button *button = Gtk::manage(new Gtk::Button(subcommand.first));
      button->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(*this, &MainWindow::on_button_clicked),
                     subcommand.first));
      box->pack_start(*button, Gtk::PACK_SHRINK);
    }
  }

  // Function to create the configuration page for a subcommand
  void create_config_page(const std::string &subcommand) {
    // Clear existing widgets
    cleanScreen();

    // Create a vertical box layout for the configuration page
    Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*box);

    // Add widgets for configuring parameters based on subcommand
    if (subcommand == "capture") {
      std::cout << "Capture command detected" << std::endl;
      create_capture_page();

    } else if (subcommand == "calibration") {
      // Example: Add widgets for the 'calibration' subcommand
      // ...

    } else if (subcommand == "liveview") {
      // Example: Add widgets for the 'liveview' subcommand
      // ...
    }
    // Add more conditions for other subcommands...

    // Add a "Run" button to execute the command
    Gtk::Button *runButton = Gtk::manage(new Gtk::Button("Run"));
    runButton->signal_clicked().connect(sigc::bind(
        sigc::mem_fun(*this, &MainWindow::on_run_button_clicked), subcommand));
    box->pack_end(*runButton, Gtk::PACK_SHRINK);
  }

  // Event handler for home button
  void on_home_button_clicked() { create_home_screen(); }

  // Event handler for subcommand buttons
  void on_button_clicked(const std::string &subcommand) {
    std::cout << "Selected subcommand: " << subcommand << std::endl;
    create_config_page(subcommand);
  }

  // Event handler for the "Run" button
  void on_run_button_clicked(const std::string &subcommand) {
    std::cout << "Executing command for subcommand: " << subcommand
              << std::endl;
    // TODO: Run the command with selected parameters
  }

private:
  const std::vector<std::pair<std::string, std::string>> subcommands = {
      {"capture", "Capture images with uncalibrated stereo cameras"},
      {"calibration", "Perform image rectification and stereo calibration from "
                      "a set of images"},
      {"liveview", "Live view (record all frames)"},
      {"fisheye_calibration",
       "Perform image rectification and stereo calibration from set of images "
       "for fisheye cameras"},
      {"shutter", "Live view with rectification and shutter functionality"},
      {"rotation", "Live view rotation, estimate the camera position, "
                   "chessboard pattern must appear in frame"},
      {"rectify", "rectify images"},
      {"depth", "Compute depth data for image list"}};
};

int main(int argc, char **argv) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  MainWindow mainWindow;

  // Start the application main loop
  return app->run(mainWindow);
}
