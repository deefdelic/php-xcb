/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */
#include <xcb/xcb.h>
#ifndef PHP_XCB_H
#define PHP_XCB_H

extern zend_module_entry xcb_module_entry;
#define phpext_xcb_ptr &xcb_module_entry

#ifdef PHP_WIN32
#	define PHP_XCB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_XCB_API __attribute__ ((visibility("default")))
#else
#	define PHP_XCB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

typedef struct _php_xcb_connection {
	xcb_connection_t *connection;
	xcb_screen_t *screen;
} php_xcb_connection;

#define PHP_XCB_CONNECTION_RES_NAME "XCB_CONNECTION"


PHP_MINIT_FUNCTION(xcb);
PHP_MSHUTDOWN_FUNCTION(xcb);
PHP_RINIT_FUNCTION(xcb);
PHP_RSHUTDOWN_FUNCTION(xcb);
PHP_MINFO_FUNCTION(xcb);

PHP_FUNCTION(xcb_init);
PHP_FUNCTION(xcb_root_id);
PHP_FUNCTION(xcb_root_width_in_pixels);
PHP_FUNCTION(xcb_root_height_in_pixels);
PHP_FUNCTION(xcb_generate_id);
PHP_FUNCTION(xcb_create_window);
PHP_FUNCTION(xcb_map_window);
PHP_FUNCTION(xcb_flush);
PHP_FUNCTION(xcb_unmap_window);
PHP_FUNCTION(xcb_configure_window);
PHP_FUNCTION(xcb_configure_window_border);
PHP_FUNCTION(xcb_configure_window_size);
PHP_FUNCTION(xcb_configure_window_pos);
PHP_FUNCTION(xcb_configure_window_lower);
PHP_FUNCTION(xcb_configure_window_raise);
PHP_FUNCTION(xcb_configure_window_events);
PHP_FUNCTION(xcb_configure_window_events_root);
PHP_FUNCTION(xcb_reparent_window);
PHP_FUNCTION(xcb_get_geometry);
PHP_FUNCTION(xcb_query_tree);
PHP_FUNCTION(xcb_wait_for_event);
PHP_FUNCTION(xcb_destroy_window);
PHP_FUNCTION(xcb_list_extensions);
PHP_FUNCTION(xcb_query_extension);
PHP_FUNCTION(xcb_get_default_colormap);
PHP_FUNCTION(xcb_create_colormap);
PHP_FUNCTION(xcb_alloc_color);
PHP_FUNCTION(xcb_alloc_named_color);
PHP_FUNCTION(xcb_create_gc);
PHP_FUNCTION(xcb_poly_fill_rectangle);
PHP_FUNCTION(xcb_create_pixmap);
PHP_FUNCTION(xcb_copy_area);
PHP_FUNCTION(xcb_open_font);
PHP_FUNCTION(xcb_image_text_8);
PHP_FUNCTION(xcb_get_wm_name);
PHP_FUNCTION(xcb_get_atom_name);

ZEND_BEGIN_MODULE_GLOBALS(xcb)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(xcb)


/* In every utility function you add that needs to use variables 
   in php_xcb_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as XCB_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define XCB_G(v) TSRMG(xcb_globals_id, zend_xcb_globals *, v)
#else
#define XCB_G(v) (xcb_globals.v)
#endif

#endif	/* PHP_XCB_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
