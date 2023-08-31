from setuptools import find_packages
from setuptools import setup

setup(
    name='more_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('more_interfaces', 'more_interfaces.*')),
)
