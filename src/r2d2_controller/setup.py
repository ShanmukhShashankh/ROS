from setuptools import setup

package_name = 'r2d2_controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='shanmukh',
    maintainer_email='vemula.shanmukhshashankh@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "test_node = r2d2_controller.my_first_node:main",
            "draw_circle = r2d2_controller.draw_circle:main",
            "pose_subscriber = r2d2_controller.pose_subscriber:main",
            "turtle_controller = r2d2_controller.turtle_controller:main",
            "number_publisher = r2d2_controller.number_publisher:main",
            "number_counter = r2d2_controller.number_counter:main"
        ],
    },
)
