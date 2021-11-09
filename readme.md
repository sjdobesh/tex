# **Tex**
Texture library for C.

## Usage:
### _Header Only_
```c
#include "tex.h"
```
### _Compile_
```
git clone https://github.com/sjdobesh/tex.git
cd tex/src
make
./tex
```

## Structures:
### _Texture_
```c
struct texture {
  int w, h, c;  // width, height, channels
  char* pixels; // pixel buffer
  char* name;   // texture name
  uint gl_ptr;  // ptr to openGL texture
} texture;
```
### _Texture_Collection_
```c
struct texture_collection {
  texture* textures;
  int n;
} texture_collection;
```

## Functions:
```c
char* load_pixels(char* path, int w, int h, int c);
texture new_texture(char* path, char* name, int w, int h, int c);
int bind_texture(texture t, uint shader);
```
