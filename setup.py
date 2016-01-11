from distutils.core import setup
from distutils.dir_util import remove_tree
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize
import shutil
import sys
import os

def removeBuild():
    print "removing old build..."
    if os.path.isfile('build'):
        remove_tree('build')

def updateLib():
    print "updating lib..."
    lib = open('libgomoku.pyx', 'w')
    for fname in os.listdir('./gomoku'):
        if fname.endswith('.py'):
            print "    parsing " + fname + "..."
            f = open('gomoku/' + fname, 'r')
            for line in iter(f):
                if line.startswith("from ") and not line.startswith("from cython"):
                    continue
                lib.write(line)
            f.close()
    lib.close()

removeBuild()
updateLib()

ext_module = Extension(
        "libgomoku",
        ["libgomoku.pyx"],
        extra_compile_args=['-fopenmp'],
        extra_link_args=['-fopenmp'],
    )

setup(
        cmdclass = {'build_ext': build_ext},
        ext_modules = [ext_module],
 )
