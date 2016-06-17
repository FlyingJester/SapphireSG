#pragma once

#if defined _WIN32 || defined __CYGWIN__ || defined __MSYS__
#include <Windows.h>
#endif

#include <GL/gl.h>

#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif

#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif

#ifndef GL_CURRENT_PROGRAM
#ifdef GL_ACTIVE_PROGRAM

#define GL_CURRENT_PROGRAM GL_ACTIVE_PROGRAM
#else
#define GL_CURRENT_PROGRAM 0x8B8D
#endif
#endif

#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif

#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif

#ifndef GL_GEOMETRY_SHADER
#define GL_GEOMETRY_SHADER 0x8DD9
#endif

#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif

#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif

#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH 0x8B84
#endif

#ifdef __APPLE__
typedef long GLintptr;
typedef long GLsizeiptr;
#elif defined _WIN32 || defined __CYGWIN__ || defined __MSYS__

#include <stdint.h>

typedef intptr_t GLintptr;
typedef size_t GLsizeiptr;
#endif

typedef char GLchar;

#ifdef __cplusplus
extern "C" {
#endif

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
extern void (APIENTRY * glEnableVertexAttribArray)(GLuint);
extern void (APIENTRY * glUniform1f)(GLint loc, GLfloat v0);
extern void (APIENTRY * glUniform2f)(GLint loc, GLfloat v0, GLfloat v1);
extern void (APIENTRY * glUniform3f)(GLint loc, GLfloat v0, GLfloat v1, GLfloat v2);
extern void (APIENTRY * glProgramUniform1f)(GLuint prog, GLint loc, GLfloat v0);
extern void (APIENTRY * glProgramUniform2f)(GLuint prog, GLint loc, GLfloat v0, GLfloat v1);
extern void (APIENTRY * glProgramUniform3f)(GLuint prog, GLint loc, GLfloat v0, GLfloat v1, GLfloat v2);

void OpenGLExtra_LoadGLFunctions(void *(*OpenGL_LoadProcAddres)(const char *));

#ifdef __cplusplus
}
#endif
