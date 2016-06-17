import os
import sys

def EnabledString(that):
    if that:
        return "enabled"
    else:
        return "disabled"

def EnableableOption(name, default):
    AddOption("--enable-" + name,
        action="store_true", dest="en_" + name, default=False,
        help="Enables " + name)
    AddOption("--disable-" + name,
        action="store_true", dest="dis_" + name, default=False,
        help="Disables " + name)
    enable = GetOption("en_" + name)
    disable = GetOption("dis_" + name)
    if enable and disable:
        print("Warning: Both enable and disable " + name + " specified.")
        return default
    if disable:
        return False
    elif enable:
        return True
    else:
        return default

# Gather some environment info to choose which backends to enable/disable by default
environment = Environment(ENV=os.environ)

environment.Append(CXXFLAGS = " -Werror ")

# -O2 works on both Windows CL-style and GCC-style compilers.
environment.Append(CCFLAGS = " -O2 -Wall ")

if os.name == "posix":
    environment.Append(CCFLAGS = " -g ", CXXFLAGS = " -fno-rtti -fno-exceptions ", LINKFLAGS = " -g ")

conf = Configure(environment)

gl_library = []

# Find the OpenGL library
if conf.CheckLib("GL"):
    gl_library += ["GL"]
if conf.CheckLib("OpenGL32"):
    gl_library += ["OpenGL32"]

# A little more is needed on Windows...
if os.name == "nt" or sys.platform == "msys" or sys.platform == "cygwin":
	gl_library += ["GDI32", "user32", "winmm", "imm32", "ole32", "oleaut32"]

if os.name == 'nt' or sys.platform == "msys" or sys.platform == "cygwin":
    # Watcom and TDM/Clang can sometimes fail the Windows.h check.
    has_gl_headers = conf.CheckCHeader("gl/GL.h") and conf.CheckCHeader("Windows.h")
elif sys.platform == 'darwin':
    # We trust that Darwin allows OpenGL.
    has_gl_headers = True
else:
    has_gl_headers = conf.CheckCHeader("GL/gl.h")

has_vulkan_headers = conf.CheckCHeader("vulkan/vulkan.h")

conf.Finish()

# Use the collected header and library info to generate backend data
possible_backends = [
    {"name":"opengl2", "enabled":has_gl_headers}, 
    {"name":"opengl4", "enabled":False}, 
    {"name":"software", "enabled":False}, 
    {"name":"vulkan", "enabled":has_vulkan_headers}
]

backends = []

# If we are building any of the OpenGL backends, build the OpenGLExtra library
build_openglextra = False

# Populate backends
printed = False
for b in possible_backends:
    enable = EnableableOption(b["name"], b["enabled"])
    
    if enable and b["name"].lower().startswith("opengl"):
        build_openglextra = True
    
    backends += [{"name":b["name"], "enabled":enable}]
    if not (enable == b["enabled"]):
        if not printed:
            print("*")
        print("* Backend " + b["name"] + " was " + EnabledString(enable))
        printed = True

if printed:
    print("*")

print("*******************")
print("* Backend Summary *")
print("*******************")

for b in backends:
    print("Backend " + b["name"] + " is " + EnabledString(b["enabled"]))

print("*******************")

# If we are building any of the OpenGL backends, build the OpenGLExtra library
if build_openglextra:
    libopenglextra = SConscript(dirs = ["openglextra"], exports = Split("environment gl_library"))
else:
    libopenglextra = {}

backend_libs = []

main_env = environment.Clone()

for b in backends:
    if b["enabled"]:
        main_env.Append(CPPDEFINES = ["SAPPHIRE_" + b["name"].upper() + "=1"])
        backend_libs += [SConscript(dirs = [b["name"]], exports = Split("environment gl_library libopenglextra"))]

libsapphire = main_env.SharedLibrary(["sapphire.cpp"], LIBS = backend_libs + [libopenglextra, gl_library])

environment.Program(["hello_world.cpp"], LIBS = [libsapphire, "SDL2"], LIBPATH = [os.getcwd()])
