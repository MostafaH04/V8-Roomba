from setuptools import find_packages, setup
from glob import glob

package_name = 'roomba_simulator'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name, glob('launch/*.launch.py')),
        ('share/' + package_name +"/description", glob('description/*.xacro')),
        ('share/' + package_name + "/config",glob('config/*.yaml'))

    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Mostafa Hussein',
    maintainer_email='mahussein04@gmail.com',
    description='V8-Roomba Autonomous Cleaning Robot',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
