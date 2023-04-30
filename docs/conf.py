# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

import os
import shutil
import subprocess
import sys

import breathe

project = 'PSoC Sensors Library'
copyright = '2021, Davide Marzorati'
author = 'Davide Marzorati'

# The full version, including alpha/beta/rc tags
release = '0.1'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.mathjax',
    'sphinx.ext.viewcode',
    'sphinx.ext.imgmath',
    'sphinx.ext.todo',
    'breathe',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# -- Extension configuration -------------------------------------------------


def create_temp_docs():
    original_cwd = os.getcwd()
    if (os.path.exists(os.path.join('..', 'Library.cylib'))):
        os.chdir(os.path.join('..', 'Library.cylib'))
    else:
        os.chdir('Library.cylib')

    library_wd = os.getcwd()

    for component in os.listdir(library_wd):
        if (os.path.isdir(component)):
            api_folder = os.path.join(component, 'API')
            if (os.path.exists(api_folder) and os.path.isdir(api_folder)):
                # All files, replace `$INSTANCE_NAME` with component name
                for api_file in os.listdir(api_folder):
                    if ((api_file[-1] == 'c') or (api_file[-1] == 'h')):
                        with open(os.path.join(api_folder, api_file), 'r') as f_r:
                            data = f_r.read()
                            data = data.replace("`$INSTANCE_NAME`", component)
                            output_dir = os.path.join(
                                '..', 'docs', 'doxygen', 'src', component)
                            if (not os.path.exists(output_dir)):
                                os.makedirs(output_dir)
                            with open(os.path.join(output_dir, api_file), 'w') as f_w:
                                f_w.write(data)
    os.chdir(original_cwd)


def remove_temp_docs():
    original_cwd = os.getcwd()
    if (os.path.exists('docs')):
        os.chdir('docs')
    shutil.rmtree(os.path.join('doxygen', 'src'))
    os.chdir(original_cwd)


subprocess.call('make clean', shell=True)
create_temp_docs()
if os.name == 'nt':
    original_cwd = os.getcwd()
    if (os.path.exists('doxygen')):
        os.chdir('doxygen')
    subprocess.call('doxygen.exe', shell=True)
    os.chdir(original_cwd)
else:
    subprocess.call('cd doxygen ; doxygen', shell=True)
remove_temp_docs()

breathe_projects = {"PSoC Sensors Library": "doxygen/build/xml/"}
breathe_default_project = "PSoC Sensors Library"
