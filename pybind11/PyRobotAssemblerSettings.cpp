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
#include <cnoid/SceneGraph>

#include "../src/RobotAssemblerSettings.h"
#include "../src/RobotAssemblerBody.h"

using namespace cnoid;
namespace ra = cnoid::robot_assembler;
namespace py = pybind11;

namespace cnoid {

void exportPyRobotAssemblerSettings(py::module &m)
{
    m.doc() = "python-binding for RobotAssembler";

    //
    // Geometry
    //
    py::class_< ra::Geometry > geometry_cls(m, "RobotAssemblerGeometry");
    py::enum_<ra::Geometry::Type>(geometry_cls, "Type")
    //'.value("{}", ra::Geometry::Type::{})'
    .value("None", ra::Geometry::Type::None)
    .value("Mesh", ra::Geometry::Type::Mesh)
    .value("Box", ra::Geometry::Type::Box)
    .value("Cylinder", ra::Geometry::Type::Cylinder)
    .value("Sphere", ra::Geometry::Type::Sphere)
    .value("Cone", ra::Geometry::Type::Cone)
    .value("Capsule", ra::Geometry::Type::Capsule)
    .value("Ellipsoid", ra::Geometry::Type::Ellipsoid)
    .value("Dummy", ra::Geometry::Type::Dummy)
    .export_values();
    geometry_cls.def(py::init<>())
    .def_property_readonly("url", [](ra::Geometry &self) { return self.url; })
    .def_property_readonly("coords", [](ra::Geometry &self) { return self.coords; })
    .def_property_readonly("scale", [](ra::Geometry &self) { return self.scale; })
    .def_property_readonly("color", [](ra::Geometry &self) { return self.color; })
    .def_property_readonly("type", [](ra::Geometry &self) { return self.type; })
    .def_property_readonly("parameter", [](ra::Geometry &self) { return self.parameter; })
    .def("isMesh", [](ra::Geometry &self) { return (self.type == ra::Geometry::Mesh); })
    ;
    //
    // ConnectingPoint
    //
    py::class_< ra::ConnectingPoint > connecting_point_cls(m, "RobotAssemblerConnectingPoint");
    py::enum_<ra::ConnectingPoint::PartsType>(connecting_point_cls, "PartsType")
    //'.value("{}", ra::ConnectingPoint::PartsType::{})'
    .value("Parts", ra::ConnectingPoint::PartsType::Parts)
    .value("Rotational", ra::ConnectingPoint::PartsType::Rotational)
    .value("Linear", ra::ConnectingPoint::PartsType::Linear)
    .value("Fixed", ra::ConnectingPoint::PartsType::Fixed)
    .value("Sphere", ra::ConnectingPoint::PartsType::Sphere)
    .value("Plane", ra::ConnectingPoint::PartsType::Plane)
    .value("Spherical", ra::ConnectingPoint::PartsType::Spherical)
    .value("Free", ra::ConnectingPoint::PartsType::Free)
    .value("UNDEFINED", ra::ConnectingPoint::PartsType::UNDEFINED)
    .export_values();
    connecting_point_cls
    .def_property_readonly("name", [](ra::ConnectingPoint &self) { return self.name; })//PointBase
    .def_property_readonly("coords", [](ra::ConnectingPoint &self) { return self.coords; })//PointBase
    .def_property_readonly("description", [](ra::ConnectingPoint &self) { return self.description; })//PointBase
    .def_property_readonly("type", [](ra::ConnectingPoint &self) { return self.getType(); })
    ;
    //
    // Actuator
    //
    py::class_< ra::Actuator, ra::ConnectingPoint > actuator_cls(m, "RobotAssemblerActuator");
    actuator_cls
    .def_property_readonly("axis", [](ra::Actuator &self) { return self.axis; })
    .def_property_readonly("limit", [](ra::Actuator &self) { return self.limit; })
    .def_property_readonly("vlimit", [](ra::Actuator &self) { return self.vlimit; })
    .def_property_readonly("tqlimit", [](ra::Actuator &self) { return self.tqlimit; })
    ;
    //
    // ExtraInfo
    //
    py::class_< ra::ExtraInfo > extra_info_cls(m, "RobotAssemblerExtraInfo");
    py::enum_<ra::ExtraInfo::Type>(extra_info_cls, "Type")
    //'.value("{}", ra::ExtraInfo::Type::{})'.format(nm, nm))
    .value("None", ra::ExtraInfo::Type::None)
    .value("IMU", ra::ExtraInfo::Type::IMU)
    .value("Acceleration", ra::ExtraInfo::Type::Acceleration)
    .value("RateGyro", ra::ExtraInfo::Type::RateGyro)
    .value("Touch", ra::ExtraInfo::Type::Touch)
    .value("Force", ra::ExtraInfo::Type::Force)
    .value("Color", ra::ExtraInfo::Type::Color)
    .value("Distance", ra::ExtraInfo::Type::Distance)
    .value("Camera", ra::ExtraInfo::Type::Camera)
    .value("Depth", ra::ExtraInfo::Type::Depth)
    .value("RGBD", ra::ExtraInfo::Type::RGBD)
    .value("Ray", ra::ExtraInfo::Type::Ray)
    .value("Position", ra::ExtraInfo::Type::Position)
    .value("Light", ra::ExtraInfo::Type::Light)
    .value("PointLight", ra::ExtraInfo::Type::PointLight)
    .value("SpotLight", ra::ExtraInfo::Type::SpotLight)
    .value("DegitalIO", ra::ExtraInfo::Type::DegitalIO)
    .value("AnalogIO", ra::ExtraInfo::Type::AnalogIO)
    .export_values();
    extra_info_cls
    .def_property_readonly("name", [](ra::ExtraInfo &self) { return self.name; })
    .def_property_readonly("type", [](ra::ExtraInfo &self) { return self.type; })
    .def_property_readonly("coords", [](ra::ExtraInfo &self) { return self.coords; })
    .def_property_readonly("description", [](ra::ExtraInfo &self) { return self.description; })
    .def_property_readonly("deviceMapping", [](ra::ExtraInfo &self) { return self.device_mapping; })
    .def_property_readonly("parameters", [](ra::ExtraInfo &self) { return self.parameters; })
    ;
    //
    // Parts
    //
    py::class_< ra::Parts > parts_cls(m, "RobotAssemblerParts");
    parts_cls.def(py::init<>())
    .def_property_readonly("numberOfVisuals", [](ra::Parts &self) { return self.visual.size(); })//
    .def_property_readonly("numberOfCollisions", [](ra::Parts &self) { return self.collision.size(); })//
    .def_property_readonly("numberOfConnectingPoints", [](ra::Parts &self) { return self.connecting_points.size(); })//
    .def_property_readonly("numberOfActuators", [](ra::Parts &self) { return self.actuators.size(); })//
    .def_property_readonly("numberOfExtraData", [](ra::Parts &self) { return self.extra_data.size(); })//
    .def_property_readonly("mass", [](ra::Parts &self) { return self.mass; })
    .def_property_readonly("centerOfMass", [](ra::Parts &self) { return self.COM; })
    .def_property_readonly("inertiaTensor", [](ra::Parts &self) { return self.inertia_tensor; })
    .def_property_readonly("type", [](ra::Parts &self) { return self.type; })
    .def_property_readonly("className", [](ra::Parts &self) { return self.class_name; })
    .def_property_readonly("description", [](ra::Parts &self) { return self.description; })
    .def_property_readonly("visualList", [](ra::Parts &self) {
        py::list _lst;
        for (int i = 0; i < self.visual.size(); i++) _lst.append( py::cast(self.visual[i]) );
        return _lst; })
    .def_property_readonly("collisionList", [](ra::Parts &self) {
        py::list _lst;
        for (int i = 0; i < self.collision.size(); i++) _lst.append( py::cast(self.collision[i]) );
        return _lst; })
    .def_property_readonly("connectingPointList", [](ra::Parts &self) {
        py::list _lst;
        for (int i = 0; i < self.connecting_points.size(); i++) _lst.append( py::cast(self.connecting_points[i]) );
        return _lst; })
    .def_property_readonly("actuatorList", [](ra::Parts &self) {
        py::list _lst;
        for (int i = 0; i < self.actuators.size(); i++) _lst.append( py::cast(self.actuators[i]) );
        return _lst; })
    .def_property_readonly("extraDataList", [](ra::Parts &self) {
        py::list _lst;
        for (int i = 0; i < self.extra_data.size(); i++) _lst.append( py::cast(self.extra_data[i]) );
        return _lst; })
    .def("getVisual", [](ra::Parts &self, int idx) {
        try {  return py::cast(self.visual.at(idx)); } catch ( ... ) { }
        return py::cast(nullptr);
    })
    .def("getCollision", [](ra::Parts &self, int idx) {
        try {  return py::cast(self.collision.at(idx)); } catch ( ... ) { }
        return py::cast(nullptr);
    })
    .def("getConnectingPoint", [](ra::Parts &self, int idx) {
        try {  return py::cast(self.connecting_points.at(idx)); } catch ( ... ) { }
        return py::cast(nullptr);
    })
    .def("getActuators", [](ra::Parts &self, int idx) {
        try {  return py::cast(self.actuators.at(idx)); } catch ( ... ) { }
        return py::cast(nullptr);
    })
    .def("getExtraData", [](ra::Parts &self, int idx) {
        try {  return py::cast(self.extra_data.at(idx)); } catch ( ... ) { }
        return py::cast(nullptr);
    })
    .def("createVisual", [] (ra::Parts &self,
                             const std::string &_dir, const std::vector<double> &_col) {
        SgGroup *ptr = new SgGroup();
        ptr->setName("xxx");
        Vector3f col = Vector3f::Zero();
        for(int i = 0; i < _col.size() && i < 3; i++) col(i) = _col[i];
        ra::createSceneFromGeometry(ptr, self.visual, _dir, col); // Body
        return ptr;
    }, py::arg("projectDir") = std::string(), py::arg("color") = std::vector<double>())
    ;
    //
    // Settings
    //
    py::class_< ra::Settings, ra::SettingsPtr > settings_cls(m, "RobotAssemblerSettings");
    settings_cls.def(py::init<>())
    .def_property_readonly("numberOfParts", [](ra::Settings &self) { return self.mapParts.size(); } )
    .def_property_readonly("partsNames", [](ra::Settings &self) {
        std::vector<std::string> lst_;
        for( auto it = self.mapParts.begin(); it != self.mapParts.end(); it++ ) {
            lst_.push_back(it->first);
        }
        return lst_; })
    .def_property_readonly("partsList", [](ra::Settings &self) {
        py::list _lst;
        for (auto it = self.mapParts.begin(); it != self.mapParts.end(); it++) _lst.append( py::cast(*it) );
        return _lst; })
    .def("getParts", [](ra::Settings &self, const int idx) {
        int index = 0;
        for( auto it = self.mapParts.begin(); it != self.mapParts.end(); it++, index++ ) {
            if (index == idx) return py::cast(it->second);
        }
        return py::cast(nullptr);
    })
    .def("getParts", [](ra::Settings &self, const std::string &name) {
        try {  return py::cast(self.mapParts.at(name));  } catch ( ... ) { }
        return py::cast(nullptr);
    })
    .def("parseYaml", &ra::Settings::parseYaml)
    .def("insertPartsFromString", &ra::Settings::insertPartsFromString)
    .def("insertPartsFromYaml", &ra::Settings::insertPartsFromYaml)
    .def("insertPartsFromNode", &ra::Settings::insertPartsFromNode)
    .def("parsePartsFromString", [](ra::Settings &self, const std::string &settings) {
        py::list _lst; std::vector<ra::Parts> _res;
        if (self.parsePartsFromString(settings, _res)) {
            for (auto it = _res.begin(); it != _res.end(); it++) _lst.append( py::cast(*it) );
        }
        return _lst;
    })
    .def("parsePartsFromYaml", [](ra::Settings &self, const std::string &filename) {
        py::list _lst; std::vector<ra::Parts> _res;
        if (self.parsePartsFromYaml(filename, _res)) {
            for (auto it = _res.begin(); it != _res.end(); it++) _lst.append( py::cast(*it) );
        }
        return _lst;
    })
    .def("parsePartsFromNode", [](ra::Settings &self, ValueNode *val) {
        py::list _lst; std::vector<ra::Parts> _res;
        if (self.parsePartsFromNode(val, _res)) {
            for (auto it = _res.begin(); it != _res.end(); it++) _lst.append( py::cast(*it) );
        }
        return _lst;
    })
    ;
    //
    // RoboasmFile
    //
    py::class_< ra::RoboasmFile > roboasm_cls(m, "RoboasmFile");
    roboasm_cls.def(py::init<>())
    .def(py::init<const std::string &>())
    .def("isValid", &ra::RoboasmFile::isValid)
    .def("parseRoboasm", [](ra::RoboasmFile &self, const std::string &filename, bool parse_config) {
        return self.parseRoboasm(filename, parse_config);
    }, py::arg("filename"), py::arg("parseConfig") = true)
    .def("dumpRoboasm", &ra::RoboasmFile::dumpRoboasm)
    ;
}

} // namespace cnoid
