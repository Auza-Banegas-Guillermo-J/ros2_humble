import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/daguill/ros2_humble/adv_ws/src/install/p_srv_coms'
