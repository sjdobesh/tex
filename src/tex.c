#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "tex.h"

texture new_texture(char* path, char* name) {
  int w, h, c;
  texture t;
  t.pixels = (char*)stbi_load(path, &w, &h, &c, STB_rgb_alpha);
  t.w = w;
  t.h = h;
  t.c = c;
  t.name = name;
  glGenTextures(1, &(t.gl_ptr));
  return t;
}

int bind_texture(texture t, uint shader) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, t.gl_ptr);
  glTexImage2D(
    GL_TEXTURE_2D,    // target
    0,                // level
    GL_RGBA,          // internal format
    t.w, t.h,         // width, height
    0,                // border
    GL_RGB,           // format
    GL_UNSIGNED_BYTE, // type
    NULL              // data
  );
  // bind it to the uniform
  glUniform1i(glGetUniformLocation(shader, "tex"), 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexSubImage2D(
    GL_TEXTURE_2D,               // target
    0, 0, 0,                     // level, x&y offset
    t.w, t.h,                    // width, height
    GL_RGBA,                     // format
    GL_UNSIGNED_INT_8_8_8_8_REV, // type
    t.pixels                     // pixels
  );
  // blend
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  return 0;
}
