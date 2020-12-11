#if !defined(DUK_JWT_H_INCLUDED)
#define DUK_JWT_H_INCLUDED

#include "debug.h"
#include "duktape.h"

#if defined(__cplusplus)
extern "C" {
#endif

void janus_duktape_register_extra_functions(duk_context *ctx);

#if defined(__cplusplus)
}
#endif  /* end 'extern "C"' wrapper */

#endif  /* DUK_MODULE_DUKTAPE_H_INCLUDED */