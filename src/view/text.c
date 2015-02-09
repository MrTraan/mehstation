#include "glib-2.0/glib.h"

#include "text.h"

/*
 * meh_open_font reads the given filename as a font with the given size.
 */
Font* meh_open_font(const char* filename, uint size) {
	Font* font = NULL;

	TTF_Font* sdl_font = TTF_OpenFont(filename, size);
	if (sdl_font == NULL) {
		return NULL;
	}

	font = g_new(Font, 1);

	font->sdl_font = sdl_font;

	return font;
}

/*
 * meh_destroy_font frees the resources of the given font.
 */
void meh_destroy_font(Font* font) {
	g_assert(font != NULL);

	TTF_CloseFont(font->sdl_font);

	g_free(font);
}
