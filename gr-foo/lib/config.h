/* Minimal config.h for the WASM build. The upstream gr-foo build generates this
 * in its CMake build tree; the impl sources include it but do not use any of its
 * macros, so an empty header is sufficient. Kept here so the sources compile
 * out-of-tree without a full gr-foo CMake configure step. */
#ifndef GR_FOO_WASM_CONFIG_H
#define GR_FOO_WASM_CONFIG_H
#endif /* GR_FOO_WASM_CONFIG_H */
