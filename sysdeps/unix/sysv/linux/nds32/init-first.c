/* VDSO initialization. Andes Nds32 version
   Copyright (C) 2007-2018 Free Software Foundation, Inc.

   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef SHARED
# include <dl-vdso.h>
# include <libc-vdso.h>

int (*VDSO_SYMBOL(gettimeofday)) (struct timeval *, void *) attribute_hidden;
int (*VDSO_SYMBOL(clock_getres)) (clockid_t, struct timespec *);
int (*VDSO_SYMBOL(clock_gettime)) (clockid_t, struct timespec *);

static inline void
_libc_vdso_platform_setup (void)
{
  PREPARE_VERSION (linux4, "LINUX_4", 14921332);

  void *p = _dl_vdso_vsym ("__vdso_gettimeofday", &linux4);
  PTR_MANGLE (p);
  VDSO_SYMBOL(gettimeofday) = p;

  p = _dl_vdso_vsym ("__vdso_clock_getres", &linux4);
  PTR_MANGLE (p);
  VDSO_SYMBOL(clock_getres) = p;

  p = _dl_vdso_vsym ("__vdso_clock_gettime", &linux4);
  PTR_MANGLE (p);
  VDSO_SYMBOL(clock_gettime) = p;

}

# define VDSO_SETUP _libc_vdso_platform_setup
#endif /* SHARED */

#include <csu/init-first.c>
