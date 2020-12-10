#if !defined(DUK_JWT_H_INCLUDED)
#define DUK_JWT_H_INCLUDED


#include "duktape.h"

/*! \brief Method to register extra JavaScript functions in the C code
 * @param[in] ctx The Duktape context to register the functions on */
//size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data);

void janus_duktape_register_extra_functions(duk_context *ctx);

#endif