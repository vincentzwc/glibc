/* Definitions for signal handling calling conventions, Andes nds32 version.
   Copyright (C) 2000-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <sys/ucontext.h>

#define SIGCONTEXT siginfo_t *_si, struct ucontext_t *
#define SIGCONTEXT_EXTRA_ARGS _si,
#define GET_PC(ctx)	((void *) (ctx)->uc_mcontext.nds32_ipc)
#define GET_FRAME(ctx)	((void *) (ctx)->uc_mcontext.nds32_fp)
#define GET_STACK(ctx)	((void *) (ctx)->uc_mcontext.nds32_sp)

#define CALL_SIGHANDLER(handler, signo, ctx) \
  (handler)((signo), SIGCONTEXT_EXTRA_ARGS (ctx))

/* There is no reliable way to get the sigcontext unless we use a
   three-argument signal handler.  */
#define __sigaction(sig, act, oact) ({ \
  (act)->sa_flags |= SA_SIGINFO; \
  (__sigaction) (sig, act, oact); \
})

#define sigaction(sig, act, oact) ({ \
  (act)->sa_flags |= SA_SIGINFO; \
  (sigaction) (sig, act, oact); \
})
