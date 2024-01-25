# jupyter console --kernel=choreonoid

exec(open('/choreonoid_ws/install/share/irsl_choreonoid/sample/irsl_import.py').read())
import cnoid.RobotAssembler as ra

#proj_dir = '/choreonoid_ws/install/share/choreonoid-2.0/robot_assembler/irsl'
proj_dir = '/home/irsl/src/robot_assembler_config_IRSL'
di = DrawInterface()

ras = ra.RobotAssemblerSettings()
ras.parseYaml(proj_dir + '/irsl_assembler_config.yaml')
ras.insertPartsFromYaml('sample.yaml')
rasu=ra.RoboasmUtil(ras)

f=ra.RoboasmFile('gripper.roboasm')
rb=rasu.makeRobot(f)

cr=ra.RoboasmBodyCreator(proj_dir)

bd=cr.createBodyRaw(rb)

iu.exportBody('/tmp/hoge.body', bd)

# ---

rau=ra.RoboasmUtil(proj_dir + '/irsl_assembler_config.yaml')
rau.settings.insertPartsFromYaml('sample.yaml')
#f=ra.RoboasmFile('gripper.roboasm')
#rb=rasu.makeRobot(f)

raf=ra.cnoidRAFile('gripper.roboasm')
rb=raf.makeRobot(rau)

cr=ra.RoboasmBodyCreator(proj_dir)
bd=cr.createBody(rb, raf)

'/home/irsl/temp/make_parts/fixed_finger_mm.stl'
'/home/irsl/temp/make_parts/move_plate_with_hole.stl'

aa=mkshapes.loadMesh('/home/irsl/temp/make_parts/move_plate_with_hole.stl', scale=0.001)
bb=mkshapes.loadMesh('/home/irsl/temp/make_parts/fixed_finger_mm.stl', scale=0.001)
