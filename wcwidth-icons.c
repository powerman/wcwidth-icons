/*
 * This is an implementation of wrappers for wcwidth() and wcswidth()
 * which explicitly defines double character-cell width for icons.
 *
 * Author: Alex Efros <powerman-asdf@ya.ru>, 2017
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

  if ((ucs >= 0x23fb && ucs <= 0x23fe) ||       /* IEC Power Symbols */
    ucs == 0x2665 ||                            /* Octicons */
    ucs == 0x26a1 ||                            /* Octicons */
    ucs == 0x2b58 ||                            /* IEC Power Symbols */
    (ucs >= 0xe000 && ucs <= 0xe09f) ||
    /* e0a0-e0a3,e0b0-e0b7 is single-width Powerline Extra Symbols */
    (ucs >= 0xe0b8 && ucs <= 0xf8ff))
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

/*
 * Avoid using LD_PRELOAD by a child process
 */
int  __attribute__((constructor))
main_init(void)
{
  unsetenv("LD_PRELOAD");
  return 0;
}
