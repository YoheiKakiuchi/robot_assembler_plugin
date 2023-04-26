/**
   @author YoheiKakiuchi
*/

#include <sstream>
#include <pybind11/pybind11.h>

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
    py::class_< cnoid::robot_assembler::Geometry, cnoid::robot_assembler::GeometryPtr > geometry_cls(m, "RobotAssemblerGeometry");
    geometry_cls.def(py::init<>())
    .def_property_readonly("url", [](cnoid::robot_assembler::Geometry &self) { return self.url; } )
    .def_property_readonly("coords", [](cnoid::robot_assembler::Geometry &self) { return self.coords; } )
    .def("is_mesh", [](cnoid::robot_assembler::Geometry &self) { return self.type == cnoid::robot_assembler::Geometry::Mesh; } )
    ;

    // Parts
    py::class_< cnoid::robot_assembler::Parts, cnoid::robot_assembler::PartsPtr > parts_cls(m, "RobotAssemblerParts");
    parts_cls.def(py::init<>())
    .def_property_readonly("number_of_visuals", [](cnoid::robot_assembler::Parts &self) { return 0; } )
    .def_property_readonly("number_of_collisions", [](cnoid::robot_assembler::Parts &self) { return 0; } )
    .def_property_readonly("mass", [](cnoid::robot_assembler::Parts &self) { return 0.0; } )
    .def_property_readonly("center_of_mass", [](cnoid::robot_assembler::Parts &self) { return 0; } )
    .def_property_readonly("inertia_tensor", [](cnoid::robot_assembler::Parts &self) { return 0; } )
    .def("visual", [](cnoid::robot_assembler::Parts &self, int idx) { return 0; } )
    .def("collision", [](cnoid::robot_assembler::Parts &self, int idx) { return 0; } )
    ;

    // Assembler
    py::class_< cnoid::robot_assembler::Settings, cnoid::robot_assembler::SettingsPtr > settings_cls(m, "RobotAssemblerSettings");
    settings_cls.def(py::init<>())
    .def_property_readonly("number_of_parts", [](cnoid::robot_assembler::Settings &self) { return 0; } )
    .def_property_readonly("parts_names", [](cnoid::robot_assembler::Settings &self) { return 0; } )
    .def("parts", [](cnoid::robot_assembler::Settings &self, const int idx) { return 0; } )
    .def("parts", [](cnoid::robot_assembler::Settings &self, const std::string &name) { return 0; } )
    ;

    // bounding box from
}
