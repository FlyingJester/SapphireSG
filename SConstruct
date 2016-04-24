import os
import sys

environment = Environment(ENV=os.environ)

AddOption('--enable-debug', dest = 'enabledebug', default=True, help=\
"Enables building with debug symbols.\n")

enabledebug = GetOption('enabledebug')

if os.name == "posix":
	environment.Append(CCFLAGS = " -Wall -Werror -fwrapv -fpic -g -O2 ",
		CFLAGS = " -ansi ", LINKFLAGS = " -g ", CXXFLAGS = " -fno-rtti -fno-exceptions ")
	if sys.platform == "msys":
		environment.Append(CCFLAGS = " -mcmodel=medium ", LINKFLAGS = " -mcmodel=medium ")
else:
	environment.Append(CCFLAGS = " /O2 /MD /Zi ", LINKFLAGS = " /DEBUG ", CPPDEFINES=["SAPPHIRESG_EXPORTS"])

libsapphiresg = SConscript("SConscript", exports = ["environment"])

# examples = SConscript(dirs=["examples/SDL2_GL_Example"], exports=["environment", "libsapphiresg"])
