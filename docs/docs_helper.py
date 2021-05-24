"""
The aim of this script is to generate fake compiled
source files for PSoC Creator Library, so that
proper names are used instead of `$INSTANCE_NAME`
values. This way, Doxygen will properly generate
XML files and Sphinx will produce the final
HTML files.
"""
import os
import shutil


def create_temp_docs():
    original_cwd = os.getcwd()
    if (os.path.exists(os.path.join('..', 'Sensors.cylib'))):
        os.chdir(os.path.join('..', 'Sensors.cylib'))
    else:
        os.chdir('Sensors.cylib')

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
