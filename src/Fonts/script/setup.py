# _*_ coding: utf-8 _*_
import py2exe
from distutils.core import setup
includes = ['encoding', 'encodings.*']
options = {'py2exe':
        {'compressed': 1,
        'optimize': 2,
        'ascii': 1,
        'includes': includes,
        'bundle_files': 1,
        'dll_excludes': ['MSVCP90.dll'],
        }
      }

setup(version='1.0.0',
   description='Font generation script',
   name='font',
   options=options,
   zipfile=None,
   windows=[{'script': 'test.py'}],
   )