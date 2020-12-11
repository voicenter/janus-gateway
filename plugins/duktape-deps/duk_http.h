#if !defined(DUK_HTTP_H_INCLUDED)
#define DUK_HTTP_H_INCLUDED

#include "debug.h"
#include "duktape.h"

#if defined(__cplusplus)
extern "C" {
#endif

char *handle_url(char* url, char* method, char* body);

void janus_duktape_register_extra_functions(duk_context *ctx);

#if defined(__cplusplus)
}
#endif  /* end 'extern "C"' wrapper */

#endif  /* DUK_MODULE_DUKTAPE_H_INCLUDED */