#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct {} crpgTexture;
crpgTexture *crpgTextureNew(const char *filename);
unsigned int crpgTextureGetID(crpgTexture *t);
void crpgTextureFree(crpgTexture *t);
#endif//TEXTURE_H
