#pragma once

#include <glib.h>

#define MEH_EXEC_RES_COVER "cover"
#define MEH_EXEC_RES_FANART "fanart" 
#define MEH_EXEC_RES_SCREENSHOT "screenshot" 

typedef struct ExecutableResource {
	int id;
	int executable_id;
	gchar* type;
	gchar* filepath;
} ExecutableResource;

ExecutableResource* meh_model_exec_res_new(int id, int executable_id, const gchar* display_name, const gchar* filepath);
void meh_model_exec_res_destroy(ExecutableResource* exec_res);
void meh_model_exec_res_list_destroy(GSList* exec_resources);
