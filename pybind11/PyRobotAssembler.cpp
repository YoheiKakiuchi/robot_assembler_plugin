/**
   @author YoheiKakiuchi
*/

#include <sstream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../src/irsl_choreonoid/Coordinates.h"
#include <cnoid/PyUtil>
#include <cnoid/PyEigenTypes>
#include <cnoid/Body>
#include <cnoid/Link>

#include "../src/RobotAssembler.h"

using namespace cnoid;
namespace py = pybind11;

//// Coordinates.h
Matrix4RM mid_coords_pos_(const double p, ref_mat4 c1, ref_mat4 c2, const double eps)
{
    Position cnoid_pos;
    Position p_c1(c1), p_c2(c2);
    cnoid_pos.setIdentity();
    mid_coords_pos(cnoid_pos, p, p_c1, p_c2, eps);
    return cnoid_pos.matrix();
}

PYBIND11_MODULE(RobotAssembler, m)
{
    m.doc() = "";

#include "PyIRSLUtil.cpp"

    // Geometry
    py::class_< cnoid::robot_assembler::Geometry > geometry_cls(m, "RobotAssemblerGeometry");
    geometry_cls.def(py::init<>())
    .def_property_readonly("url", [](cnoid::robot_assembler::Geometry &self) { return self.url; } )
    .def_property_readonly("coords", [](cnoid::robot_assembler::Geometry &self) { return self.coords; } )
    .def_property_readonly("scale", [](cnoid::robot_assembler::Geometry &self) { return self.scale; } )
    .def_property_readonly("color", [](cnoid::robot_assembler::Geometry &self) { return self.color; } )      
    .def("is_mesh", [](cnoid::robot_assembler::Geometry &self) { return (self.type == cnoid::robot_assembler::Geometry::Mesh); } )
    ;
    // Parts
    py::class_< cnoid::robot_assembler::Parts > parts_cls(m, "RobotAssemblerParts");
    parts_cls.def(py::init<>())
    .def_property_readonly("number_of_visuals", [](cnoid::robot_assembler::Parts &self) { return self.visual.size(); } )
    .def_property_readonly("number_of_collisions", [](cnoid::robot_assembler::Parts &self) { return self.collision.size(); } )
    .def_property_readonly("mass", [](cnoid::robot_assembler::Parts &self) { return self.mass; } )
    .def_property_readonly("center_of_mass", [](cnoid::robot_assembler::Parts &self) { return self.COM; } )
    .def_property_readonly("inertia_tensor", [](cnoid::robot_assembler::Parts &self) { return self.inertia_tensor; } )
    .def("visual", [](cnoid::robot_assembler::Parts &self, int idx) {
      try {
	return self.visual.at(idx);
      } catch ( ... ) {
      }
      cnoid::robot_assembler::Geometry ret;
      return ret;
    } )
    .def("collision", [](cnoid::robot_assembler::Parts &self, int idx) {
      try {
	return self.collision.at(idx);
      } catch ( ... ) {
      }
      cnoid::robot_assembler::Geometry ret;
      return ret;
    } )
    ;
    // Assembler
    py::class_< cnoid::robot_assembler::Settings, cnoid::robot_assembler::SettingsPtr > settings_cls(m, "RobotAssemblerSettings");
    settings_cls.def(py::init<>())
    .def_property_readonly("number_of_parts", [](cnoid::robot_assembler::Settings &self) { return self.mapParts.size(); } )
    .def_property_readonly("parts_names", [](cnoid::robot_assembler::Settings &self) {
      std::vector<std::string> lst_;
      for( auto it = self.mapParts.begin(); it != self.mapParts.end(); it++ ) {
  	lst_.push_back(it->first);
      }
      return lst_; })
    .def("parts", [](cnoid::robot_assembler::Settings &self, const int idx) {
      int index = 0;
      for( auto it = self.mapParts.begin(); it != self.mapParts.end(); it++, index++ ) {
	if (index == idx) {
	  return it->second;
	}
      }
      cnoid::robot_assembler::Parts ret;
      return ret;
    } )
    .def("parts", [](cnoid::robot_assembler::Settings &self, const std::string &name) {
      try {
	return self.mapParts.at(name);
      } catch ( ... ) {
      }
      cnoid::robot_assembler::Parts ret;
      return ret;
    })
    .def("parseYaml", &cnoid::robot_assembler::Settings::parseYaml)
    ;
    // bounding box from
}
