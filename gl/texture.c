#include "texture.h"
#include <stb/stb_image.h>
#include <GL/glew.h>
#include "err.h"
#include <stdlib.h>

typedef struct{
	unsigned int ID;
} Texture_t;

crpgTexture *crpgTextureNew(const char *filename){
	Texture_t *t = malloc(sizeof(Texture_t));
	unsigned char *data = NULL;
	int w, h, chan;

	data = stbi_load(filename, &w, &h, &chan, 0);
	if(data)
	{
		glGenTextures(1, &t->ID);
		glBindTexture(GL_TEXTURE_2D, t->ID);
		if(chan == 3){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		} else if (chan == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		} else {
			err_output("Error loading texture, images that are not formatted as\
					RGB or RGBA are unsupported!");
			err_output(stbi_failure_reason());

			glBindTexture(GL_TEXTURE_2D, 0);
			glDeleteTextures(1, &t->ID);
			free(t);
			return NULL;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

	} else {
		char out[128];
		snprintf(out, sizeof(out), "failed to load %s texture!\n%s\n",
				filename, stbi_failure_reason());
		err_output(out);
		free(t);
		return NULL;
	}
	crpgTexture *tex = (crpgTexture *)t;
	return tex;
}

unsigned int crpgTextureGetID(crpgTexture *t)
{
	Texture_t *tex = (Texture_t *)t;
	if(t)
		return tex->ID;
	else return 0;
}

void crpgTextureFree(crpgTexture *t)
{
	Texture_t *tex = (Texture_t *)t;
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &tex->ID);
	free(tex);
}
