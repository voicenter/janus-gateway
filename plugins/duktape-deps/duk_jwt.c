#include "debug.h"
#include "duktape.h"
#include "plugins/plugin.h"
#include "duk_jwt.h"
#include <stdio.h>
#include <jwt.h>
#include <string.h>
#include <stdlib.h>

#define DUK_CASE_STR(type) case type: return #type
static const char *janus_duktape_type_string(int type) {
	switch(type) {
		DUK_CASE_STR(DUK_TYPE_NONE);
		DUK_CASE_STR(DUK_TYPE_UNDEFINED);
		DUK_CASE_STR(DUK_TYPE_NULL);
		DUK_CASE_STR(DUK_TYPE_BOOLEAN);
		DUK_CASE_STR(DUK_TYPE_NUMBER);
		DUK_CASE_STR(DUK_TYPE_STRING);
		DUK_CASE_STR(DUK_TYPE_OBJECT);
		DUK_CASE_STR(DUK_TYPE_BUFFER);
		DUK_CASE_STR(DUK_TYPE_POINTER);
		DUK_CASE_STR(DUK_TYPE_LIGHTFUNC);
		default:
			break;
	}
	return NULL;
}

static duk_ret_t jwt_validate(duk_context *ctx) {
    char* data;
    char* jwt;
    char* secret;
    jwt_t *jwt_dec=NULL;

    if(duk_get_type(ctx, 0) != DUK_TYPE_STRING && duk_get_type(ctx, 0) != DUK_TYPE_UNDEFINED) {
        duk_push_error_object(ctx, DUK_RET_TYPE_ERROR, "Invalid URL argument (expected %s, got %s)\n",
                              janus_duktape_type_string(DUK_TYPE_STRING), janus_duktape_type_string(duk_get_type(ctx, 0)));
        return duk_throw(ctx);
    } else {
        jwt = duk_get_string(ctx, 0);
        secret = duk_get_string(ctx, 1);
    }

    if (jwt_decode(&jwt_dec, jwt,
    (const unsigned char *)secret,strlen(secret)) != 0 || jwt_dec == NULL) {
        duk_push_error_object(ctx, DUK_RET_TYPE_ERROR, "Failed to decode\n");
        return duk_throw(ctx);
    }

    duk_push_string(ctx, jwt_dump_str(jwt_dec,0));
    jwt_free(jwt_dec);

    return 1;
}

void janus_duktape_register_extra_functions(duk_context *ctx) {
	if(ctx == NULL)
		return;
	JANUS_LOG(LOG_VERB, "Registering Duktape JWT functions\n");

    duk_push_c_function(ctx, jwt_validate, 2);
    duk_put_global_string(ctx, "jwt_validate");
}
