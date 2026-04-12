/*
 * This is an implementation of wrappers for wcwidth(), wcswidth()
 * and utf8proc_charwidth() which explicitly defines double
 * character-cell width for icons.
 *
 * Author: Alex Efros <wcwidth-icons@id.powerman.name>, 2017-2025
 * License: LGPL 2.1+
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>
#include <wchar.h>

static int
is_nerd_font_icon (long ucs)
{
  return
    (ucs >= 0x23fb && ucs <= 0x23fe) ||
    ucs == 0x2665 ||
    ucs == 0x2b58 ||
    (ucs >= 0xe000 && ucs <= 0xe09f) ||
    (ucs >= 0xe0c0 && ucs <= 0xf8ff) ||
    (ucs >= 0xf0001 && ucs <= 0xfffff);
}

int
wcwidth (wchar_t ucs)
{
  static int (*next_wcwidth)(wchar_t);

  if (!next_wcwidth)
    next_wcwidth = (int(*)(wchar_t)) dlsym(RTLD_NEXT, "wcwidth");

  /***
   * Fix icon width for Nerd Fonts v3 (non-Mono variant).
   ***/
  if (is_nerd_font_icon(ucs))
    return 2;
  return next_wcwidth(ucs);
}

/*
 * Fix icon width for applications using utf8proc library
 * (e.g. foot terminal with grapheme-clustering enabled).
 */
int
utf8proc_charwidth (int32_t ucs)
{
  static int (*next_utf8proc_charwidth)(int32_t);

  if (!next_utf8proc_charwidth)
    next_utf8proc_charwidth = (int(*)(int32_t)) dlsym(RTLD_NEXT, "utf8proc_charwidth");

  if (is_nerd_font_icon(ucs))
    return 2;
  return next_utf8proc_charwidth(ucs);
}

/* This is an unmodified copy from glibc-2.23/wcsmbs/wcswidth.c */
int
wcswidth (const wchar_t *s, size_t n)
{
  int result = 0;

  while (n-- > 0 && *s != L'\0')
    {
      int now = wcwidth (*s);
      if (now == -1)
        return -1;
      result += now;
      ++s;
    }

  return result;
}
