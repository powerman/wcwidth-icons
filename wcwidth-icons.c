/*
 * This is an implementation of wrappers for wcwidth() and wcswidth()
 * which explicitly defines double character-cell width for icons.
 *
 * Author: Alex Efros <wcwidth-icons@id.powerman.name>, 2017-2024
 * License: LGPL 2.1+
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <wchar.h>

int
wcwidth (wchar_t ucs)
{
  static int (*next_wcwidth)(wchar_t);

  if (!next_wcwidth)
    next_wcwidth = (int(*)(wchar_t)) dlsym(RTLD_NEXT, "wcwidth");

  /***
   * Nerd Fonts v3.2.1
   ***/
  if ((ucs >= 0x23fb && ucs <= 0x23fe) ||       /* IEC Power Symbols */
    ucs == 0x2665 ||                            /* Octicons */
    ucs == 0x26a1 ||                            /* Octicons */
    ucs == 0x2b58 ||                            /* IEC Power Symbols */
    (ucs >= 0xe000 && ucs <= 0xe00a) ||         /* Pomicons */
    /* e0a0-e0a2    single-width Powerline */
    /* e0a3         single-width Powerline Extra */
    /* e0b0-e0b3    single-width Powerline */
    /* e0b4-e0bf    single-width Powerline Extra */
    (ucs >= 0xe0c0 && ucs <= 0xe0c8) ||         /* Powerline Extra */
    ucs == 0xe0ca ||                            /* Powerline Extra */
    (ucs >= 0xe0cc && ucs <= 0xe0d7) ||         /* Powerline Extra */
    (ucs >= 0xe200 && ucs <= 0xe2a9) ||         /* Font Awesome Extension */
    (ucs >= 0xe300 && ucs <= 0xe3e3) ||         /* Weather Icons */
    (ucs >= 0xe5fa && ucs <= 0xe6b5) ||         /* Seti-UI + Custom */
    (ucs >= 0xe700 && ucs <= 0xe7c5) ||         /* Devicons */
    (ucs >= 0xea60 && ucs <= 0xec1e) ||         /* Codicons */
    (ucs >= 0xed00 && ucs <= 0xefce) ||         /* Font Awesome */
    (ucs >= 0xf000 && ucs <= 0xf2ff) ||         /* Font Awesome */
    (ucs >= 0xf300 && ucs <= 0xf375) ||         /* Font Logos */
    (ucs >= 0xf400 && ucs <= 0xf533) ||         /* Octicons */
    (ucs >= 0xf0001 && ucs <= 0xf1af0))         /* Material Design */
    return 2;
  return next_wcwidth(ucs);
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
