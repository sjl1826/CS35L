# serial 10
dnl Copyright (C) 2002-2006, 2009-2010 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_USERSPEC],
[
  AC_LIBOBJ([userspec])

  dnl Prerequisites of lib/userspec.c.
  AC_CHECK_HEADERS_ONCE([sys/param.h])
])
