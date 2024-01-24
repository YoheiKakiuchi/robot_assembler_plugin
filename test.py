# jupyter console --kernel=choreonoid

exec(open('/choreonoid_ws/install/share/irsl_choreonoid/sample/irsl_import.py').read())
import cnoid.RobotAssembler as ra

#proj_dir = '/choreonoid_ws/install/share/choreonoid-2.0/robot_assembler/irsl'
proj_dir = '/home/irsl/src/robot_assembler_config_IRSL'
di = DrawInterface()

ras = ra.RobotAssemblerSettings()
ras.parseYaml(proj_dir + '/irsl_assembler_config.yaml')
ras.insertPartsFromYaml('sample.yaml')

f=ra.RoboasmFile('gripper.roboasm')
rasu=ra.RoboasmUtil(ras)
rb=rasu.makeRobot(f)

cr=ra.RoboasmBodyCreator(proj_dir)

bd=cr.createBody(rb)

iu.exportBody('/tmp/hoge.body', bd)
