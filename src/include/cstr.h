#pragma once

// Clone C string into memory allocated using malloc().
// The pointer must be freed using free().
char* cstr_clone_malloc(const char* src);
