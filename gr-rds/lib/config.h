/* Minimal config.h for the WASM build. The upstream gr-rds build generates this
 * in its CMake build tree; the impl sources include it but do not use any of its
 * macros (only an unrelated comment references VERSION), so an empty header is
 * sufficient. Kept here so the sources compile out-of-tree without a full
 * gr-rds CMake configure step. */
#ifndef GR_RDS_WASM_CONFIG_H
#define GR_RDS_WASM_CONFIG_H
#endif /* GR_RDS_WASM_CONFIG_H */
