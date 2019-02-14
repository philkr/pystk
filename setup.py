import os
import shutil
import re
import sys
import sysconfig
import platform
import subprocess
from glob import glob

from distutils.version import LooseVersion
from setuptools import setup, find_packages, Extension
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)',
                                         out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(
                cfg.upper(),
                extdir)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j10']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get('CXXFLAGS', ''),
            self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args,
                              cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args,
                              cwd=self.build_temp)
        print()


with open("README.md", "r") as fh:
    long_description = fh.read()

data = glob('data/**', recursive=True)
stk_assets = glob('stk-assets/**', recursive=True)

def ignore(base, entries):
    print( base )
    return [e for e in entries if '.py' in e]
try:
    shutil.rmtree('pystk/data')
except FileNotFoundError:
    pass
data_files = []
for base in ['data/', 'stk-assets/']:
    for root, dirs, files in os.walk(base):
        target_data_dir = os.path.join('data', root[len(base):])
        target_dir = os.path.join('pystk', target_data_dir)
        try: os.makedirs(target_dir)
        except FileExistsError: pass
        for f in files:
            if '.py' not in f:
                shutil.copy(os.path.join(root,f), os.path.join(target_dir, f))
                data_files.append(os.path.join(target_data_dir, f))

setup(
    name='pystk',
    version='1.0',
    author='Philipp Krähenbühl',
    author_email='philkr@utexas.edu',
    description='Python SuperTuxKart inferface',
    long_description=long_description,
    # tell setuptools to look for any packages under 'src'
    packages=['pystk', 'pystk.gui'],
    # tell setuptools that all packages will be under the 'src' directory
    # and nowhere else
    package_dir={'':'.'},
    package_data={'':['*.md'],'pystk':data_files },
    # TODO: Add more
    # install_requires=['cmake'],
    python_requires='>=3.6',
#    include_package_data=True,
    # add an extension module named 'python_cpp_example' to the package
    # 'python_cpp_example'
    ext_modules=[CMakeExtension('pystk/cpp')],
    # add custom build_ext command
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)

shutil.rmtree('pystk/data')
