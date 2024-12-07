from setuptools import find_packages
from setuptools import setup

setup(
    name='my_cashier_system',
    version='0.0.0',
    packages=find_packages(
        include=('my_cashier_system', 'my_cashier_system.*')),
)
