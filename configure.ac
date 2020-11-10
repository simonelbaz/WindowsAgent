#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_PREREQ([2.69])
AC_INIT([OCSWindowsAgent], [0.1], [bug@test.com])
AC_CONFIG_SRCDIR([OcsSystray/OcsSystrayDlg.h])
AC_CONFIG_HEADERS([config.h])

AC_LANG(C++)
LT_INIT
LT_LANG([C++])
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

AC_DEFINE([HAVE_DLFCN_H], [], [Description])
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_RANLIB

#AC_CONFIG_MACRO_DIRS([m4])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lbz2':
AC_CHECK_LIB([bz2], [main])
# FIXME: Replace `main' with a function in `-lcrypto':
AC_CHECK_LIB([crypto], [main])
# FIXME: Replace `main' with a function in `-lssl':
AC_CHECK_LIB([ssl], [main])
# FIXME: Replace `main' with a function in `-lziparch':
AC_CHECK_LIB([ziparch], [main])

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h limits.h malloc.h memory.h netdb.h netinet/in.h sgtty.h stddef.h stdint.h stdlib.h string.h strings.h sys/file.h sys/ioctl.h sys/mount.h sys/param.h sys/socket.h sys/time.h sys/vfs.h syslog.h termio.h termios.h unistd.h utime.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRCOLL
AC_FUNC_STRERROR_R
AC_CHECK_FUNCS([alarm atexit clock_gettime ftruncate getcwd gethostbyaddr gethostbyname gethrtime gettimeofday inet_ntoa isascii memchr memmove memset mkdir munmap pathconf select setenv socket strcasecmp strchr strcspn strdup strerror strncasecmp strpbrk strrchr strspn strstr strtol strtoul strtoumax uname utime])

AC_CONFIG_FILES([Makefile
		 ComHTTP/Makefile
		 OcsNotifyUser/Makefile
		 OcsSystray/Makefile
		 OcsWmi/Makefile
		 OCSInventory_Front/Makefile
		 Download/Makefile
		 Service/Makefile
		 SysInfo/Makefile
		 TestSysInfo/Makefile
		 Agent/Makefile])
#AC_CONFIG_SUBDIRS([External_Deps/Zlib-1.2.11
#                   External_Deps/curl-7.73.0
#                   External_Deps/net-snmp-5.7])
AC_OUTPUT
