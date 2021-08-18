# -*- coding: utf-8 -*-
import os
import re
import subprocess
import sys

from setuptools import setup, Extension, Command
from setuptools.command.build_ext import build_ext
from setuptools.command.build_py import build_py

ASSET_URL = "http://www.cs.utexas.edu/~philkr/stk-assets20191122.zip"
this_directory = os.path.dirname(os.path.abspath(__file__))

# Convert distutils Windows platform specifiers to CMake -A arguments
PLAT_TO_CMAKE = {
    "win32": "Win32",
    "win-amd64": "x64",
    "win-arm32": "ARM",
    "win-arm64": "ARM64",
}


# A CMakeExtension needs a sourcedir instead of a file list.
# The name must be the _single_ output extension from the CMake build.
# If you need multiple extensions, see scikit-build.
class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        # required for auto-detection & inclusion of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        debug = int(os.environ.get("DEBUG", 0)) if self.debug is None else self.debug
        cfg = "Debug" if debug else "Release"

        # CMake lets you override the generator - we need to check this.
        # Can be set with Conda-Build, for example.
        cmake_generator = os.environ.get("CMAKE_GENERATOR", "")

        # Set Python_EXECUTABLE instead if you use PYBIND11_FINDPYTHON
        # EXAMPLE_VERSION_INFO shows you how to pass a value into the C++ code
        # from Python.
        cmake_args = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(extdir),
            "-DPYTHON_EXECUTABLE={}".format(sys.executable),
            "-DCMAKE_BUILD_TYPE={}".format(cfg),  # not used on MSVC, but no harm
            "-DPYSTK_VERSION={}".format(self.distribution.get_version())
        ]
        build_args = []

        if self.compiler.compiler_type != "msvc":
            # Using Ninja-build since it a) is available as a wheel and b)
            # multithreads automatically. MSVC would require all variables be
            # exported for Ninja to pick it up, which is a little tricky to do.
            # Users can override the generator with CMAKE_GENERATOR in CMake
            # 3.15+.
            if not cmake_generator:
                try:
                    import ninja  # noqa: F401

                    cmake_args += ["-GNinja"]
                except ImportError:
                    pass

        else:

            # Single config generators are handled "normally"
            single_config = any(x in cmake_generator for x in {"NMake", "Ninja"})

            # CMake allows an arch-in-generator style for backward compatibility
            contains_arch = any(x in cmake_generator for x in {"ARM", "Win64"})

            # Specify the arch if using MSVC generator, but only if it doesn't
            # contain a backward-compatibility arch spec already in the
            # generator name.
            if not single_config and not contains_arch:
                cmake_args += ["-A", PLAT_TO_CMAKE[self.plat_name]]

            # Multi-config generators have a different way to specify configs
            if not single_config:
                cmake_args += [
                    "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}".format(cfg.upper(), extdir)
                ]
                build_args += ["--config", cfg]

        if sys.platform.startswith("darwin"):
            # Cross-compile support for macOS - respect ARCHFLAGS if set
            archs = re.findall(r"-arch (\S+)", os.environ.get("ARCHFLAGS", ""))
            if archs:
                cmake_args += ["-DCMAKE_OSX_ARCHITECTURES={}".format(";".join(archs))]

        # Set CMAKE_BUILD_PARALLEL_LEVEL to control the parallel build level
        # across all generators.
        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            # self.parallel is a Python 3 only way to set parallel jobs by hand
            # using -j in the build_ext call, not supported by pip or PyPA-build.
            if hasattr(self, "parallel") and self.parallel:
                # CMake 3.12+ only.
                build_args += ["-j{}".format(self.parallel)]

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(
            ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp
        )
        subprocess.check_call(
            ["cmake", "--build", "."] + build_args, cwd=self.build_temp
        )


class FetchDataCommand(Command):
    description = "fetch the supertuxkart assets"
    user_options = [('force', 'r', 'forcibly fetch the data (delete existing assets)')]
    boolean_options = ['force']

    def initialize_options(self):
        self.force = 0

    def finalize_options(self, ):
        pass

    def run(self):
        import io, requests, zipfile
        assets_dir = os.path.join(this_directory, 'stk-assets')
        if not os.path.exists(assets_dir) or self.force:
            r = requests.get(ASSET_URL, stream=True)
            total_length = r.headers.get('content-length')
            content = b''
            if total_length is None:
                content = r.content
            else:
                dl = 0
                total_length = int(total_length)
                print("Fetching assets")
                for data in r.iter_content(1 << 20):
                    dl += len(data)
                    content += data
                    done = int(50 * dl / total_length)
                    sys.stdout.write("\r[%s%s] %3d%%" % ('=' * done, ' ' * (50 - done), 100 * dl / total_length))
                print()
            z = zipfile.ZipFile(io.BytesIO(content))
            try:
                shutil.rmtree(assets_dir)
            except FileNotFoundError:
                pass
            z.extractall(assets_dir)
        else:
            print("Using existing assets (overwrite with '--force')")


class BuildAndCopyData(build_py):
    description = "build_py and copy the supertuxkart assets"

    def run(self):
        super().run()
        for cmd_name in self.get_sub_commands():
            self.run_command(cmd_name)
        import shutil
        try:
            shutil.rmtree(os.path.join(self.build_lib, 'data'))
        except FileNotFoundError:
            pass
        data_files = []
        for base in ['data/', 'stk-assets/']:
            base = os.path.join(this_directory, base)
            for root, dirs, files in os.walk(base):
                target_dir = os.path.join(self.build_lib, self.packages[0], 'data', root[len(base):])
                try:
                    os.makedirs(target_dir)
                except FileExistsError:
                    pass
                for f in files:
                    if '.py' not in f:
                        self.copy_file(os.path.join(root, f), os.path.join(target_dir, f))

    sub_commands = [('fetch_data', lambda x: True)]


with open("README.md", "r") as fh:
    long_description = fh.read()


def ignore(base, entries):
    return [e for e in entries if '.py' in e]


setup(
    name='PySuperTuxKart',
    version='1.1.0',
    author='Philipp Krähenbühl',
    author_email='philkr@utexas.edu',
    description='Python SuperTuxKart inferface',
    long_description=long_description,
    url="https://github.com/philkr/pystk",
    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Console',
        'Intended Audience :: Education',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Artificial Intelligence',
    ],
 
    # tell setuptools that all packages will be under the 'src' directory
    # and nowhere else
    packages=['pystk_data'],
    package_dir={'pystk_data': '.'},
    package_data={'pystk_data': ['*.md', 'docs/*', 'examples/*.py']},
    # TODO: Add more
    install_requires=['requests'],
    python_requires='>=3.6',
    ext_modules=[CMakeExtension('pystk_cpp')],
    # add custom build_ext command
    cmdclass=dict(fetch_data=FetchDataCommand, build_py=BuildAndCopyData, build_ext=CMakeBuild),
    zip_safe=False,
)
