require 'mkmf'

extension_name = 'xclick'
dir_config(extension_name)
find_header('X11/Xlib.h')
find_library('X11', 'XOpenDisplay')
create_makefile(extension_name)
