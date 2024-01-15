#pragma once
#include "gtkmm/box.h"
#include "utils.hpp"
#include "widgets.hpp"
#include <iostream>
class LiveViewScreen {
  // Slider mSlider{10, 0, 100, 1};
  FileChooser jsonConfigFile{"Archivo de configuracion json",
                             "Archivo de configuracion", false, FILE_SELECTOR,
                             JSON_FILTER};
  FileChooser remapFile{"Archivo de calibracion", "Archivo de rectificacion",
                        false, FILE_SELECTOR, YML_FILTER};
  FileChooser outDirectory{"Carpeta de imagenes", "Carpeta de imagenes", false,
                           FOLDER_SELECTOR};
  CheckBox saveUnrectify{"Guardar imagnes sin rectificar"};
  CheckBox saveRectify{"Guardar imagenes calibradas"};
  Button runButton{"Comenzar"};
  Gtk::Box box{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Grid grid{};

  void onRun();

public:
  LiveViewScreen();
  Gtk::Box *getBox();
};
