#pragma once
#include "gtkmm/box.h"
#include "utils.hpp"
#include "widgets.hpp"
#include <iostream>
class RectifyScreen {

  Button runButton{"Rectificar"};
  FileChooser leftFiles{"Seleccionar imagenes", "Imagenes izquierdas", true,
                        FILE_SELECTOR, IMG_FILTER};
  FileChooser rightFiles{"Seleccionar imagenes", "Imagenes derechas", true,
                         FILE_SELECTOR, IMG_FILTER};
  FileChooser remapFile{"Seleccionar archivo", "Archivo de rectificacion",
                        false, FILE_SELECTOR, YML_FILTER};

  void onRun();
  Gtk::Box box{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Grid grid{};

public:
  RectifyScreen();
  Gtk::Box *getBox();
};
