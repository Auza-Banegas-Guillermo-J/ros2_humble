from setuptools import find_packages, setup

import os
from glob import glob

package_name = 'p_pckg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='daguill',
    maintainer_email='daguill@todo.todo',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'talker = p_pckg.publisher_member_function:main',
            'listener = p_pckg.subscriber_member_function:main',
            'tranceiver = p_pckg.tranceiver_member_function:main',
        ],
    },
)
