dnl $Id$
dnl config.m4 for extension xcb

 PHP_ARG_WITH(xcb, whether to enable xcb support,
 [  --with-xcb           Enable xcb support])

if test "$PHP_XCB" != "no"; then
  AC_DEFINE(HAVE_XCB, 1, [Whether you have XCB])
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/xcb/xcb.h"
  if test -r $PHP_XCB/$SEARCH_FOR; then
     XCB_DIR=$PHP_XCB
   else # search default path list
     AC_MSG_CHECKING([for xcb files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         XCB_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
   fi

  if test -z "$XCB_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the xcb distribution])
  fi

PHP_ADD_INCLUDE($XCB_DIR/include)
# for xcb
  LIBNAME=xcb
  LIBSYMBOL=xcb_connect

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, /usr/lib, XCB_SHARED_LIBADD)
     AC_DEFINE(HAVE_XCBLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong xcb lib version or lib not found])
   ],[
     -L/usr/lib -lxcb 
   ])
  
   PHP_SUBST(XCB_SHARED_LIBADD)
# for xcb-util   
  LIBNAME=xcb-icccm
  LIBSYMBOL=xcb_event_get_label

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, /usr/lib, XCB_SHARED_LIBADD)
     AC_DEFINE(HAVE_XCBLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong xcb-util lib version or lib not found])
   ],[
     -L/usr/lib -lxcb 
   ])
  
   PHP_SUBST(XCB_SHARED_LIBADD)
   
      #xcb-aux
  LIBNAME=xcb-aux
  LIBSYMBOL=xcb_aux_parse_color

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, /usr/lib, XCB_SHARED_LIBADD)
     AC_DEFINE(HAVE_XCBLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong xcb-glx lib version or lib not found])
   ],[
     -L/usr/lib -lxcb 
   ])
  
   PHP_SUBST(XCB_SHARED_LIBADD)
   
   #xcb-glx
  LIBNAME=xcb-glx
  LIBSYMBOL=xcb_glx_render_large

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, /usr/lib, XCB_SHARED_LIBADD)
     AC_DEFINE(HAVE_XCBLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong xcb-glx lib version or lib not found])
   ],[
     -L/usr/lib -lxcb 
   ])
  
   PHP_SUBST(XCB_SHARED_LIBADD)


  PHP_NEW_EXTENSION(xcb, xcb.c, $ext_shared)
fi
