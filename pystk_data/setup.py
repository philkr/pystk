# -*- coding: utf-8 -*-
import os
from pathlib import Path
from setuptools import setup, Extension, Command
from setuptools.command.build_py import build_py

ASSET_URL = "http://www.cs.utexas.edu/~philkr/stk-assets20191122-all.zip"
this_directory = Path(__file__).absolute().parent

class FetchDataCommand(Command):
    description = "fetch the supertuxkart assets"
    user_options = [('force', 'r', 'forcibly fetch the data (delete existing assets)')]
    boolean_options = ['force']

    def initialize_options(self):
        self.force = 0

    def finalize_options(self):
        pass

    def run(self):
        import io, requests, zipfile
        assets_dir = this_directory / 'data'
        if not assets_dir.exists() or self.force:
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
                    # done = int(50 * dl / total_length)
                    # sys.stdout.write("\r[%s%s] %3d%%" % ('=' * done, ' ' * (50 - done), 100 * dl / total_length))
                print()
            z = zipfile.ZipFile(io.BytesIO(content))
            import shutil
            try:
                shutil.rmtree(assets_dir)
            except FileNotFoundError:
                pass
            z.extractall(this_directory)
        else:
            print("Using existing assets (overwrite with '--force')")


class BuildAndCopyData(build_py):
    description = "build_py and copy the supertuxkart assets"

    def run(self):
        super().run()
        for cmd_name in self.get_sub_commands():
            self.run_command(cmd_name)
        target_path = Path(self.build_lib) / self.packages[0] / 'data'
        import shutil
        try:
            shutil.rmtree(target_path)
        except FileNotFoundError:
            pass
        data_files = []
        base = this_directory / 'data'
        for p in base.glob('**/*'):
            if p.is_file() and p.suffix != '.py':
                t = target_path / p.relative_to(base)
                t.parent.mkdir(parents=True, exist_ok=True)
                self.copy_file(p, t)

    sub_commands = [('fetch_data', lambda x: True)]


def ignore(base, entries):
    return [e for e in entries if '.py' in e]


setup(
    name='PySuperTuxKartData',
    version='1.0.1',
    author='Philipp Krähenbühl',
    author_email='philkr@utexas.edu',
    description='Python SuperTuxKart interface -- data package',
    long_description="This package contains all the game data for PySTK",
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

    install_requires=['requests'],
    python_requires='>=3.6',
    # add custom build_ext command
    cmdclass=dict(fetch_data=FetchDataCommand, build_py=BuildAndCopyData),
    zip_safe=False,
)
