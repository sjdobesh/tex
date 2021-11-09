#ifndef _TEX_H_
#define _TEX_H_
#define uint unsigned int

typedef struct texture {
  int w, h, c;  // width, height, channels
  char* name;   // texture name
  char* pixels; // pixel buffer
  uint gl_ptr;  // openGL texture ptr
} texture;

typedef struct texture_collection {
  texture* textures;
  int n;
} texture_collection;


char* load_pixels(char* path, int w, int h, int c);
texture new_texture(char* path, char* name, int w, int h, int c);
int bind_texture(texture t, uint shader);
#endif
