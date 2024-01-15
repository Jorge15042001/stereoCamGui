#pragma once
#include "gtkmm/box.h"
#include "utils.hpp"
#include "widgets.hpp"
#include <iostream>
class DepthScreen {

  Button runButton{"Ejecutar"};
  FileChooser jsonConfigFile{"Seleccionar archivio", "Archivo de configuracion",
                             false, FILE_SELECTOR, JSON_FILTER};
  FileChooser leftFiles{"Seleccionar imagenes", "Imagenes izquierdas", true,
                        FILE_SELECTOR, IMG_FILTER};
  FileChooser rightFiles{"Seleccionar imagenes", "Imagees derechas", true,
                         FILE_SELECTOR, IMG_FILTER};
  FileChooser remapFile{"Seleccionar archivo", "Archivo de rectificacion",
                        false, FILE_SELECTOR, YML_FILTER};
  FileChooser extrinsicsFile{"Seleccionar archivo",
                             "Archivo de parametros intrinsecos", false,
                             FILE_SELECTOR, YML_FILTER};
  Slider p1{"P1", 8, 0, 10, 1};
  Slider p2{"P2", 32, 0, 40, 4};
  Slider minDistance{"Distancia minima (mm)", 240, 100, 600, 10};
  Slider maxDistance{"Distancion maxima (mm)", 460, 100, 600, 10};
  Slider sigma{"Sigma", 1, 0, 5, 0.1, 1};
  Slider lambda{"Lambda", 1000, 0, 10000, 100};
  Slider scale{"Scale", 4, 1, 8, 0.1, 1};
  CheckBox saveDepthMap{"Guardar mapa de profundidad"};
  CheckBox saveRawDepth{"Guardar datos de profundidad raw"};
  CheckBox savePointCloud{"Guardar nube de puntos"};

  Gtk::Box box{Gtk::ORIENTATION_VERTICAL, 10};
  Gtk::Grid grid{};

  void onRun();

public:
  DepthScreen();
  Gtk::Box *getBox();
};
