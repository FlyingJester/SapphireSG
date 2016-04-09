SapphireSG
==========

What is SapphireSG?
-------------------

SapphireSG is a high-performance 2D rendering engine. It performs rendering 
asynchronously using hardware acceleration, exposing a simple scenegraph API
that maps well to OpenGL 4.1 while still being simple to use in procedural or
object oriented systems.

Sapphire is released under the 2-clause BSD license. The public API is
documented in doc/html/index.html, under the sapphire_sg.h file (the public
header).

It is based on the Sapphire graphics plugin from TurboSphere, and is used as
the main graphics plugin in the Turbo game engine. You can also see a proof
of concept for queueing OpenGL commands for threaded rendering at 
https://github.com/FlyingJester/GL_On_A_Stick/ which was the original tech-demo
that Sapphire in TurboSphere was based on.

What Backends Work?
-------------------

The OpenGL backend is the main backend, although there are experimental Vulkan
and software backends.

Other backends are welcome.

What Platforms Does SapphireSG Work On?
---------------------------------------

SapphireSG is intended to work well on Windows, Linux, OS X, and FreeBSD.

Ideally, any platform with a C compiler should work, although not all backends
will work on all platforms. On platforms that lack both OpenGL and Vulkan, the
software backend should still function. The asynchronous command queueing 
requires either Windows or a Posix Threads implementation (pthreads). On 
platforms lacking pthreads, it is still possible to call the graphics API
without it.
