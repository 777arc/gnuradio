/* Minimal config.h for the WASM build. The upstream gr-dvbs2 build generates this
 * in its CMake build tree; the impl sources include it but do not use any of its
 * macros, so an empty header is sufficient. Kept here so the sources compile
 * out-of-tree without a full gr-dvbs2 CMake configure step. (The DVB-S2 constants
 * live in the separate, checked-in include/dvbs2/dvbs2_config.h.) */
#ifndef GR_DVBS2_WASM_CONFIG_H
#define GR_DVBS2_WASM_CONFIG_H
#endif /* GR_DVBS2_WASM_CONFIG_H */
