#pragma once
#include "gtkmm/box.h"
#include "utils.hpp"
#include "widgets.hpp"
#include <iostream>
#include <stereocam/calibration.hpp>
#include <string>
#include <vector>
class CalibrationScreen {

  Button runButton{"Calibrar"};
  FileChooser jsonConfigFile{"Seleccionar archivo", "Archivo de configuracion",
                             false, FILE_SELECTOR, JSON_FILTER};
  FileChooser leftFiles{"Seleccionar imagenes", "Imagenes izquierda", true,
                        FILE_SELECTOR, IMG_FILTER};
  FileChooser rightFiles{"Seleccionar imagenes", "Imagenes derechas", true,
                         FILE_SELECTOR, IMG_FILTER};
  // CheckBox showCalibratedImages{"Mostrar imagnes calibradas"};
  Slider patternRows{"Filas del patron de calibracion", 27, 4, 30, 1};
  Slider patternCols{"Columnas del patron de calibracion", 19, 4, 30, 1};

  Gtk::Box box{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Grid grid{};
  void onRun();

public:
  CalibrationScreen();
  Gtk::Box *getBox();
};
