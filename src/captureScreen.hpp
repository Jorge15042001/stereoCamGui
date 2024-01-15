#pragma once
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "utils.hpp"
#include "widgets.hpp"
#include <iostream>
class CaptureScreen {
  FileChooser jsonConfigFile{"Archivo de configuracion json",
                             "Archivo de configuracion", false, FILE_SELECTOR,
                             JSON_FILTER};
  FileChooser remapFile{
      "Archivo de calibracion",
      "Archivo de rectificacion",
      false,
      FILE_SELECTOR,
      YML_FILTER,
  };
  FileChooser outDirectory{"Carpeta de imagenes", "Carpeta de imagenes", false,
                           FOLDER_SELECTOR};
  Button runButton{"Capture"};
  Gtk::Box box{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Grid grid{};

  void onRun();

public:
  CaptureScreen();
  Gtk::Box *getBox();
};
