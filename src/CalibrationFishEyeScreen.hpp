#pragma once
#include "TaskManger.hpp"
#include "gtkmm/box.h"
#include "stereocam/StereoCam.hpp"
#include "stereocam/calibration.hpp"
#include "stereocam/notifier.hpp"
#include "utils.hpp"
#include "widgets.hpp"
#include <iostream>
class CalibrationFishEyeScreen {

  Button runButton{"Calibrate"};
  FileChooser jsonConfigFile{"Seleccionar archivio", "Archivo de configuracion",
                             false, FILE_SELECTOR, JSON_FILTER};
  FileChooser leftFiles{"Seleccionar imagenes", "Imagenes izquierdas", true,
                        FILE_SELECTOR, IMG_FILTER};
  FileChooser rightFiles{"Seleccionar imagenes", "Imagenes derechas", true,
                         FILE_SELECTOR, IMG_FILTER};
  Slider patternRows{"Filas del patron de calibracion", 27, 4, 30, 1};
  Slider patternCols{"Columnas del patron de calibracion", 19, 4, 30, 1};

  void onRun();

  Gtk::Box box{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Grid grid{};

public:
  CalibrationFishEyeScreen();
  Gtk::Box *getBox();
};
