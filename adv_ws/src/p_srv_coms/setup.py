from setuptools import find_packages, setup

package_name = 'p_srv_coms'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='daguill',
    maintainer_email='guillermo.auza@ucb.edu.bo',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'server = p_srv_coms.server:main',
                'client = p_srv_coms.client:main',
        ],
    },
)
