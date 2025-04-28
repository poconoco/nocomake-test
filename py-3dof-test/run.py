from submodules.py_kinematics.ik3dof import IK3DOF


def main():
    ik = IK3DOF()

    ik.coxa_h_offset = None
    ik.coxa_v_offset = None
    
    ik.femur_length = None
    ik.tibia_length = None

    ik.coxa_sideway_angle = None
    ik.femur_horizontal_angle = None
    ik.tibia_femur_parallel_angle = None


    print("Hello, world!")


if __name__ == "__main__":
    main()
