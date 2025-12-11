from setuptools import find_packages
from setuptools import setup

setup(
    name='mpc_car_control',
    version='0.0.0',
    packages=find_packages(
        include=('mpc_car_control', 'mpc_car_control.*')),
)
