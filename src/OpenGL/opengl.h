#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#endif

#include <GL/gl.h>

#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

#ifdef __APPLE__
typedef long GLintptr;
typedef long GLsizeiptr;
#else
typedef intptr_t GLintptr;
typedef size_t GLsizeiptr;
#endif

typedef char GLchar;

extern void (APIENTRY * glGenBuffers)(GLsizei, GLuint*);
extern void (APIENTRY * glDeleteBuffers)(GLsizei, GLuint*);
extern void (APIENTRY * glBindBuffer)(GLenum, GLuint);
extern void (APIENTRY * glBufferData)(GLenum, GLsizeiptr, const GLvoid *, GLenum);
extern void (APIENTRY * glBufferSubData)(GLenum, GLintptr, GLsizeiptr, const GLvoid *);
extern void (APIENTRY * glCopyImageSubData)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
extern GLenum(APIENTRY * glCreateShader)(GLenum);
extern void (APIENTRY * glDeleteShader)(GLenum);
extern void (APIENTRY * glShaderSource)(GLenum, GLint, const GLchar **, const GLint *);
extern void (APIENTRY * glGetShaderiv)(GLuint, GLenum, GLint*);
extern void (APIENTRY * glCompileShader)(GLenum);
extern GLenum(APIENTRY * glCreateProgram)(void);
extern void (APIENTRY * glUseProgram)(GLenum);
extern void (APIENTRY * glAttachShader)(GLenum, GLenum);
extern void (APIENTRY * glLinkProgram)(GLenum);
extern void (APIENTRY * glGetProgramiv)(GLuint, GLenum, GLint*);
extern GLboolean(APIENTRY * glIsShader)(GLuint);
extern void (APIENTRY * glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (APIENTRY * glGetProgramInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*);
extern void (APIENTRY * glDeleteProgram)(GLuint);
extern GLint(APIENTRY * glGetUniformLocation)(GLuint program, const GLchar *name);
extern void (APIENTRY * glProgramUniform1f)(GLuint program, GLint location, GLfloat v0);
extern void (APIENTRY * glBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum);
extern void (APIENTRY * glGenerateMipmap)(GLenum);

extern void (APIENTRY * glGenVertexArrays)(GLsizei, GLuint*);
extern void (APIENTRY * glDeleteVertexArrays)(GLsizei, GLuint*);
extern void (APIENTRY * glBindVertexArray)(GLuint);
extern GLint(APIENTRY * glGetAttribLocation)(GLuint, const GLchar *);
extern GLint(APIENTRY * glVertexAttribPointer)(GLuint name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *data);

void OpenGLSG_LoadGLFunctions(void *(*OpenGL_LoadProcAddres)(const char *));
