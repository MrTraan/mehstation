#include "SDL2/SDL.h"
#include "glib-2.0/glib.h"

#include "view/image.h"
#include "view/text.h"
#include "view/window.h"
#include "system/settings.h"
#include "system/app.h"

int main(int argc, char* argv[]) {
	/* create and init the app. */
	App* app = meh_app_create();
	meh_app_init(app);

	/* entering the main loop. */
	meh_app_main_loop(app);

	/* clean behind us. */
	meh_app_destroy(app);
	return 0;
}
