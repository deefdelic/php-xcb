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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xcb.h"
#include <xcb/xcb.h>

int le_xcb_connection;
ZEND_DECLARE_MODULE_GLOBALS( xcb)

/* True global resources - no need for thread safety here */
static int le_xcb;

/* {{{ xcb_functions[]
 *
 * Every user visible function must have an entry in xcb_functions[].
 */
const zend_function_entry xcb_functions[] = {
	PHP_FE(xcb_init, NULL)
	PHP_FE(xcb_root_id, NULL)
	PHP_FE(xcb_root_width_in_pixels, NULL)
	PHP_FE(xcb_root_height_in_pixels, NULL)
	PHP_FE(xcb_generate_id, NULL)
	PHP_FE(xcb_create_window, NULL)
	PHP_FE(xcb_map_window, NULL)
	PHP_FE(xcb_flush, NULL)
	PHP_FE(xcb_unmap_window, NULL)
	PHP_FE(xcb_configure_window, NULL)
	PHP_FE(xcb_configure_window_border, NULL)
	PHP_FE(xcb_configure_window_size, NULL)
	PHP_FE(xcb_configure_window_pos, NULL)
	PHP_FE(xcb_configure_window_lower, NULL)
	PHP_FE(xcb_configure_window_raise, NULL)
	PHP_FE(xcb_configure_window_events, NULL)
	PHP_FE(xcb_configure_window_events_root, NULL)
	PHP_FE(xcb_reparent_window, NULL)
	PHP_FE(xcb_get_geometry, NULL)
	PHP_FE(xcb_query_tree, NULL)
	PHP_FE(xcb_wait_for_event, NULL)
	PHP_FE(xcb_destroy_window, NULL)
	PHP_FE(xcb_list_extensions, NULL)
	PHP_FE(xcb_query_extension, NULL)
	PHP_FE(xcb_get_default_colormap, NULL)
	PHP_FE(xcb_create_colormap, NULL)
	PHP_FE(xcb_alloc_color, NULL)
	PHP_FE(xcb_create_gc, NULL)
	PHP_FE(xcb_poly_fill_rectangle, NULL)
	PHP_FE(xcb_alloc_named_color, NULL)
	{	NULL, NULL, NULL} /* Must be the last line in xcb_functions[] */
};
/* }}} */

/* {{{ xcb_module_entry
 */
zend_module_entry xcb_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
		STANDARD_MODULE_HEADER,
#endif
		"xcb", xcb_functions, PHP_MINIT(xcb), PHP_MSHUTDOWN(xcb), PHP_RINIT(xcb), /* Replace with NULL if there's nothing to do at request start */
		PHP_RSHUTDOWN(xcb), /* Replace with NULL if there's nothing to do at request end */
		PHP_MINFO(xcb),
#if ZEND_MODULE_API_NO >= 20010901
		"0.1", /* Replace with version number for your extension */
#endif
		STANDARD_MODULE_PROPERTIES };
/* }}} */

#ifdef COMPILE_DL_XCB
ZEND_GET_MODULE(xcb)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
 PHP_INI_BEGIN()
 STD_PHP_INI_ENTRY("xcb.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xcb_globals, xcb_globals)
 STD_PHP_INI_ENTRY("xcb.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xcb_globals, xcb_globals)
 PHP_INI_END()
 */
/* }}} */

/* {{{ php_xcb_init_globals
 */
/* Uncomment this function if you have INI entries
 static void php_xcb_init_globals(zend_xcb_globals *xcb_globals)
 {
 xcb_globals->global_value = 0;
 xcb_globals->global_string = NULL;
 }
 */
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION( xcb) {
	/* If you have INI entries, uncomment these lines 
	 REGISTER_INI_ENTRIES();
	 */
	le_xcb_connection = zend_register_list_destructors_ex(NULL, NULL, PHP_XCB_CONNECTION_RES_NAME, module_number);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION( xcb) {
	/* uncomment this line if you have INI entries
	 UNREGISTER_INI_ENTRIES();
	 */
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION( xcb) {
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION( xcb) {
	//TODO: fix this to clean up any resources we opened
	//	if (xconnection) {
	//		xcb_disconnect(xconnection);
	//	}
	//	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION( xcb) {
	php_info_print_table_start();
	php_info_print_table_header(2, "xcb support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	 DISPLAY_INI_ENTRIES();
	 */
}
/* }}} */

//int parseMaskString(char* mask){
//    XCB_EVENT_MASK_BUTTON_RELEASE = 8,
//    XCB_EVENT_MASK_ENTER_WINDOW = 16,
//    XCB_EVENT_MASK_LEAVE_WINDOW = 32,
//    XCB_EVENT_MASK_POINTER_MOTION = 64,
//    XCB_EVENT_MASK_POINTER_MOTION_HINT = 128,
//    XCB_EVENT_MASK_BUTTON_1_MOTION = 256,
//    XCB_EVENT_MASK_BUTTON_2_MOTION = 512,
//    XCB_EVENT_MASK_BUTTON_3_MOTION = 1024,
//    XCB_EVENT_MASK_BUTTON_4_MOTION = 2048,
//    XCB_EVENT_MASK_BUTTON_5_MOTION = 4096,
//    XCB_EVENT_MASK_BUTTON_MOTION = 8192,
//    XCB_EVENT_MASK_KEYMAP_STATE = 16384,
//    XCB_EVENT_MASK_EXPOSURE = 32768,
//    XCB_EVENT_MASK_VISIBILITY_CHANGE = 65536,
//    XCB_EVENT_MASK_STRUCTURE_NOTIFY = 131072,
//    XCB_EVENT_MASK_RESIZE_REDIRECT = 262144,
//    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY = 524288,
//    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT = 1048576,
//    XCB_EVENT_MASK_FOCUS_CHANGE = 2097152,
//    XCB_EVENT_MASK_PROPERTY_CHANGE = 4194304,
//    XCB_EVENT_MASK_COLOR_MAP_CHANGE = 8388608,
//    XCB_EVENT_MASK_OWNER_GRAB_BUTTON = 16777216
//
//}

ZEND_BEGIN_ARG_INFO_EX(arginfo_xcb_init, 0, 0, 0)
		ZEND_ARG_INFO(0, displaynum)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_init) {
	char *dispnum = NULL;
	int dispnum_len;
	xcb_connection_t *xconnection; // The connection to the X server.
	xcb_screen_t *screen; //The active Screen
	php_xcb_connection *c;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &dispnum, &dispnum_len) == SUCCESS) {
		xconnection = xcb_connect(dispnum, NULL);
		//		atom_desktop = xcb_atom_get(xconnection, "_NET_WM_DESKTOP");
		//		wm_delete_window = xcb_atom_get(xconnection, "WM_DELETE_WINDOW");
		//		wm_protocols = xcb_atom_get(xconnection, "WM_PROTOCOLS");
	} else {
		xconnection = xcb_connect(NULL, NULL);
	}

	if (xconnection == 0) {
		RETURN_BOOL(1);
	} else {
		if (xcb_connection_has_error(xconnection)) {
			RETURN_BOOL(1);
		} else {
			c = emalloc(sizeof(php_xcb_connection));
			c->connection = xconnection;
			c->screen = xcb_setup_roots_iterator(xcb_get_setup(xconnection)).data;
			ZEND_REGISTER_RESOURCE(return_value, c, le_xcb_connection);
		}
	}
}
ZEND_BEGIN_ARG_INFO(arginfo_xcb_root_width_in_pixels, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_root_width_in_pixels) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	if (c->screen) {
		RETURN_LONG(c->screen->width_in_pixels);
	} else {
		RETURN_LONG(0);
	}
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_root_id, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_root_id) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	if (c->screen) {
		RETURN_LONG((int) c->screen->root);
	} else {
		RETURN_LONG(0);
	}
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_root_height_in_pixels, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_root_height_in_pixels) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	if (c->screen) {
		RETURN_LONG(c->screen->height_in_pixels);
	} else {
		RETURN_LONG(0);
	}
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_generate_id, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_generate_id) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	xcb_window_t newID = xcb_generate_id(c->connection);
	RETURN_LONG(newID);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_create_window, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, parent_window_id)
		ZEND_ARG_INFO(0, width)
		ZEND_ARG_INFO(0, height)
		ZEND_ARG_INFO(0, x)
		ZEND_ARG_INFO(0, y)
		ZEND_ARG_INFO(0, border_width)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_create_window) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, parentId, width, height, x, y, border;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlllllll", &zconnection, &windowId, &parentId, &width, &height, &x, &y, &border) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_create_window(c->connection, XCB_COPY_FROM_PARENT, windowId, parentId, x, y, width, height, border, XCB_WINDOW_CLASS_INPUT_OUTPUT, c->screen->root_visual, 0, NULL);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_map_window, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_map_window) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	xcb_map_window(c->connection, (xcb_window_t) windowId);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_flush, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_flush) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_flush(c->connection);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_unmap_window, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_unmap_window) {
	int windowId;
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_unmap_window(c->connection, (xcb_window_t) windowId);
	RETURN_NULL();
}

void zval_to_mask(zval* mask, uint32_t* retPtr) {
	zval **data;
	HashTable* mask_hash;
	HashPosition pointer;
	uint32_t realmask;
	realmask = 0;
	mask_hash = Z_ARRVAL_P(mask);
	for (zend_hash_internal_pointer_reset_ex(mask_hash, &pointer); zend_hash_get_current_data_ex(mask_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(
			mask_hash, &pointer)) {
		if (Z_TYPE_PP(data) == IS_LONG) {
			zval temp;
			temp = **data;
			zval_copy_ctor(&temp);
			if (realmask == 0) {
				//php_printf("adding mask: %d \n", (int) Z_LVAL(temp));
				realmask = (uint32_t) Z_LVAL(temp);
			} else {
				//php_printf("adding mask: %d \n", (int) Z_LVAL(temp));
				realmask |= (uint32_t) Z_LVAL(temp);
			}
		}
	}
	php_printf("final mask: %d \n", realmask);
	*retPtr = realmask;
}
/**
 void zval_to_uint32_tarr(zval* vals, uint32_t** retPtr) {
 zval **data;
 int i;
 HashTable* val_hash;
 HashPosition pointer;
 val_hash = Z_ARRVAL_P(vals);
 uint32_t retval[zend_hash_num_elements(val_hash)];
 i = 0;
 for (zend_hash_internal_pointer_reset_ex(val_hash, &pointer); zend_hash_get_current_data_ex(val_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(val_hash,
 &pointer)) {
 if (Z_TYPE_PP(data) == IS_LONG) {
 zval temp;
 int val;
 temp = **data;
 zval_copy_ctor(&temp);
 val = Z_LVAL(temp);
 php_printf("Adding %d to array at possition %d \n", val, i);
 retval[i] = (uint32_t) val;
 i++;
 } else {
 php_printf("unknown type");
 }
 }
 retPtr =(const uint32_t*) retval;
 //	return (const uint32_t) retval;
 }
 **/
ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, arr_mask)
		ZEND_ARG_INFO(0, arr_mask_values)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window) {
	int windowId, i;
	php_xcb_connection *c;
	zval *zconnection;
	zval *zmask, *zvals, **data;
	uint32_t intMask;
	uint32_t* intVals;
	HashTable* val_hash;
	HashPosition pointer;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlaa", &zconnection, &windowId, &zmask, &zvals) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	//convert the mask;
	zval_to_mask(zmask, &intMask);

	val_hash = Z_ARRVAL_P(zvals);
	uint32_t retval[zend_hash_num_elements(val_hash)];
	i = 0;
	for (zend_hash_internal_pointer_reset_ex(val_hash, &pointer); zend_hash_get_current_data_ex(val_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(val_hash,
			&pointer)) {
		if (Z_TYPE_PP(data) == IS_LONG) {
			zval temp;
			int val;
			temp = **data;
			zval_copy_ctor(&temp);
			val = Z_LVAL(temp);
			//php_printf("Adding %d to array at possition %d \n", val, i);
			retval[i] = (uint32_t) val;
			i++;
		} else {
			php_printf("unknown type");
		}
	}

	//php_printf("xcb_configure_window mask value: %d  \n", intMask);
	xcb_configure_window(c->connection, (xcb_window_t) windowId, intMask, (const uint32_t *) retval);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_events, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, arr_mask_values)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_events) {
	int windowId;
	zval *zvals;
	php_xcb_connection *c;
	zval *zconnection;
	uint32_t values[1];
	xcb_void_cookie_t cookie;
	xcb_generic_error_t *error;
	uint32_t intMask;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rla", &zconnection, &windowId, &zvals) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	zval_to_mask(zvals, &intMask);
	values[0] = intMask;
	//php_printf("our mask value: %d or intMask: %d \n", values[0], intMask);
	//	php_printf("their values: %d \n", XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY);
	cookie = xcb_change_window_attributes_checked(c->connection, (xcb_window_t) windowId, XCB_CW_EVENT_MASK, values);
	error = xcb_request_check(c->connection, cookie);
	//TODO: raise an error
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_events_root, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_events_root) {
	//TODO:  Remove this now that masks are working properly
	int windowId;
	uint32_t values[1];
	php_xcb_connection *c;
	zval *zconnection;
	xcb_void_cookie_t cookie;
	xcb_generic_error_t *error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	values[0] = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY;
	cookie = xcb_change_window_attributes_checked(c->connection, (xcb_window_t) windowId, XCB_CW_EVENT_MASK, values);
	error = xcb_request_check(c->connection, cookie);
	//TODO: raise an error
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_border, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, border_width)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_border) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, width;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zconnection, &windowId, &width) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	const uint32_t values[] = { width };
	xcb_configure_window(c->connection, (xcb_window_t) windowId, XCB_CONFIG_WINDOW_BORDER_WIDTH, values);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_size, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, width)
		ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_size) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, width, height;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlll", &zconnection, &windowId, &width, &height) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	const uint32_t values[] = { width, height };
	xcb_configure_window(c->connection, (xcb_window_t) windowId, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_pos, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, x)
		ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_pos) {
	int windowId, x, y;
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlll", &zconnection, &windowId, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	const uint32_t values[] = { x, y };
	xcb_configure_window(c->connection, (xcb_window_t) windowId, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_raise, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_raise) {
	int windowId;
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	uint32_t values[] = { XCB_STACK_MODE_ABOVE };
	xcb_configure_window(c->connection, (xcb_window_t) windowId, XCB_CONFIG_WINDOW_STACK_MODE, values);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_configure_window_lower, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_configure_window_lower) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	uint32_t values[] = { XCB_STACK_MODE_BELOW };
	xcb_configure_window(c->connection, (xcb_window_t) windowId, XCB_CONFIG_WINDOW_STACK_MODE, values);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_reparent_window, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, new_parent_id)
		ZEND_ARG_INFO(0, x)
		ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_reparent_window) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, newParentId, x, y;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllll",&zconnection, &windowId, &newParentId, &x, &y) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_reparent_window(c->connection, (xcb_window_t) windowId, (xcb_window_t) newParentId, x, y);
RETURN_NULL()
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_get_geometry, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_get_geometry) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_get_geometry_reply_t* geom = xcb_get_geometry_reply(c->connection, xcb_get_geometry(c->connection, (xcb_drawable_t) windowId), NULL);
	array_init(return_value);
	add_assoc_long(return_value, "depth", geom->depth);
	add_assoc_long(return_value, "root", geom->root);
	add_assoc_long(return_value, "x", geom->x);
	add_assoc_long(return_value, "y", geom->y);
	add_assoc_long(return_value, "width", geom->width);
	add_assoc_long(return_value, "height", geom->height);
	add_assoc_long(return_value, "border_width", geom->border_width);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_query_tree, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_query_tree) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, len, i;
	xcb_window_t *children;
	xcb_query_tree_reply_t *reply;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	reply = xcb_query_tree_reply(c->connection, xcb_query_tree(c->connection, windowId), 0);
	len = xcb_query_tree_children_length(reply);
	children = xcb_query_tree_children(reply);
	array_init(return_value);
	for (i = 0; i < len; i++) {
		add_next_index_long(return_value, (int) children[i]);
	}
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_destroy_window, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_destroy_window) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zconnection, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_destroy_window(c->connection, windowId);
	RETURN_NULL();
}
PHP_FUNCTION( test_mask) {
	//	uint32_t mask = 0;
	//	uint32_t values[2];
	//	mask = XCB_CW_EVENT_MASK;
	//	values[0] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_ENTER_WINDOW
	//			| XCB_EVENT_MASK_LEAVE_WINDOW | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;
	////	RETURN_LONG()
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_list_extensions, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_list_extensions) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_list_extensions_cookie_t cookie = xcb_list_extensions(c->connection);
	xcb_list_extensions_reply_t *r = xcb_list_extensions_reply(c->connection, cookie, NULL);
	int i = xcb_list_extensions_names_length(r);
	xcb_str_iterator_t iter = xcb_list_extensions_names_iterator(r);
	array_init(return_value);
	if (iter.data) {
		for (; iter.rem; xcb_str_next(&iter)) {
			xcb_str_t *str = iter.data;
			char *cstr = strndup(xcb_str_name(str), xcb_str_name_length(str));
			//php_printf("%2d %s\n", xcb_str_name_length(str), cstr);
			add_next_index_stringl(return_value, cstr, xcb_str_name_length(str), 1);
			free(cstr);
		}
	}
	free(r);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_query_extension, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, extension_name)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_query_extension) {
	//TODO: Something is segfaulting here, dont use!
	php_xcb_connection *c;
	zval *zconnection;
	char* name;
	int namelen;
	xcb_generic_error_t *error;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &zconnection, &name, &namelen) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);
	xcb_query_extension_reply_t *rep = xcb_query_extension_reply(c->connection, xcb_query_extension(c->connection, namelen, name), &error);
	if (NULL != error) {
		php_printf("Unable to query extension %s\n", name);
		RETURN_LONG(0);
	}
	array_init(return_value);
	add_assoc_long(return_value, "present", rep->present);
	add_assoc_long(return_value, "major_opcode", rep->major_opcode);
	add_assoc_long(return_value, "first_event", rep->first_event);
	add_assoc_long(return_value, "first_error", rep->first_error);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_get_default_colormap, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_get_default_colormap) {
	php_xcb_connection *c;
	zval *zconnection;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	RETURN_LONG(c->screen->default_colormap);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_create_colormap, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, colormap_id)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_create_colormap) {
	php_xcb_connection *c;
	zval *zconnection;
	int mapId, windowId;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &zconnection, &mapId, &windowId) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_create_colormap(c->connection, XCB_COLORMAP_ALLOC_NONE, mapId, windowId, c->screen->root_visual);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_alloc_color, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, colormap_id)
		ZEND_ARG_INFO(0, red)
		ZEND_ARG_INFO(0, green)
		ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_alloc_color) {
	php_xcb_connection *c;
	zval *zconnection;
	int mapId, red, blue, green;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllll", &zconnection, &mapId,  &red, &blue, &green) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	//	// copy
	//	if (!xcb_aux_parse_color(name, &red, &green, &blue)) {
	//		xcb_lookup_color_cookie_t c = xcb_lookup_color(xconnection, mapId, 3, name);
	//		xcb_lookup_color_reply_t *reply = xcb_lookup_color_reply(xconnection, c, NULL);
	//		red = reply->exact_red;
	//		green = reply->exact_green;
	//		blue = reply->exact_blue;
	//		free(reply);
	//	} else {
	//		xcb_alloc_color_cookie_t c = xcb_alloc_color(xconnection, mapId, red, green, blue);
	//		xcb_alloc_color_reply_t *r = xcb_alloc_color_reply(xconnection, c, NULL);
	//		red = r->red;
	//		green = r->green;
	//		blue = r->blue;
	//		pixel = r->pixel;
	//		free(r);
	//	}
	// end copy
	xcb_alloc_color_reply_t *reply = xcb_alloc_color_reply(c->connection, xcb_alloc_color(c->connection, mapId, red, blue, green), NULL);
	RETURN_LONG(reply->pixel);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_alloc_named_color, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, colormap_id)
		ZEND_ARG_INFO(0, color_name)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_alloc_named_color) {
	php_xcb_connection *c;
	zval *zconnection;
	char* colstr;
	int mapId, colstrlen;
	xcb_generic_error_t *error;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rls", &zconnection, &mapId,  &colstr, &colstrlen) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_alloc_named_color_reply_t *col_reply = xcb_alloc_named_color_reply(c->connection, xcb_alloc_named_color(c->connection, (xcb_colormap_t) mapId, colstrlen, colstr), &error);
	if (NULL != error) {
		php_printf("Unable to allocate color %s\n", colstr);
		RETURN_LONG(0);
	}

	RETURN_LONG(col_reply->pixel);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_create_gc, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, gc_id)
		ZEND_ARG_INFO(0, arr_mask)
		ZEND_ARG_INFO(0, arr_vals)
ZEND_END_ARG_INFO();


PHP_FUNCTION( xcb_create_gc) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, gcId, i;
	zval *zmask, *zvals, **data;
	HashTable* val_hash;
	HashPosition pointer;
	uint32_t intMask;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllaa", &zconnection, &windowId, &gcId, &zmask, &zvals) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	zval_to_mask(zmask, &intMask);

	val_hash = Z_ARRVAL_P(zvals);
	uint32_t retval[zend_hash_num_elements(val_hash)];
	i = 0;
	for (zend_hash_internal_pointer_reset_ex(val_hash, &pointer); zend_hash_get_current_data_ex(val_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(val_hash,
			&pointer)) {
		if (Z_TYPE_PP(data) == IS_LONG) {
			zval temp;
			int val;
			temp = **data;
			zval_copy_ctor(&temp);
			val = Z_LVAL(temp);
			//php_printf("Adding %d to array at possition %d \n", val, i);
			retval[i] = (uint32_t) val;
			i++;
		} else {
			//php_printf("unknown type");
		}
	}
	//    uint32_t        values[3]  = {screen->black_pixel, 0, screen->black_pixel};
	xcb_create_gc(c->connection, gcId, windowId, intMask, (const uint32_t *) retval);
	RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_poly_fill_rectangle, 0)
		ZEND_ARG_INFO(0, xcb_resource)
		ZEND_ARG_INFO(0, window_id)
		ZEND_ARG_INFO(0, gc_id)
		ZEND_ARG_INFO(0, x1)
		ZEND_ARG_INFO(0, y1)
		ZEND_ARG_INFO(0, x2)
		ZEND_ARG_INFO(0, y2)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_poly_fill_rectangle) {
	php_xcb_connection *c;
	zval *zconnection;
	int windowId, gcId, x1, y1, x2, y2;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rllllll", &zconnection, &windowId, &gcId, &x1, &y1, &x2, &y2) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	xcb_rectangle_t rectangles[] = { { x1, y1, x2, y2 } };
	xcb_poly_fill_rectangle(c->connection, windowId, gcId, 1, rectangles);
	//xcb_flush(c->connection);
}

event_xcb_button_press(xcb_generic_event_t* evt, zval* return_value) {
	xcb_button_press_event_t *e = (xcb_button_press_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "same_screen", e->same_screen);
}

event_xcb_button_release(xcb_generic_event_t* evt, zval* return_value) {
	xcb_button_release_event_t *e = (xcb_button_release_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "same_screen", e->same_screen);
}

event_xcb_key_press(xcb_generic_event_t* evt, zval* return_value) {
	xcb_key_press_event_t *e = (xcb_key_press_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "same_screen", e->same_screen);
}

event_xcb_key_release(xcb_generic_event_t* evt, zval* return_value) {
	xcb_key_release_event_t *e = (xcb_key_release_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "same_screen", e->same_screen);
}

event_xcb_configure_request(xcb_generic_event_t* evt, zval* return_value) {
	xcb_configure_request_event_t *e = (xcb_configure_request_event_t *) evt;
	add_assoc_long(return_value, "stack_mode", e->stack_mode);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "parent", e->parent);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "sibling", e->sibling);
	add_assoc_long(return_value, "x", e->x);
	add_assoc_long(return_value, "y", e->y);
	add_assoc_long(return_value, "width", e->width);
	add_assoc_long(return_value, "height", e->height);
	add_assoc_long(return_value, "border_width", e->border_width);
	add_assoc_long(return_value, "value_mask", e->value_mask);
}

event_xcb_map_request(xcb_generic_event_t* evt, zval* return_value) {
	xcb_map_request_event_t *e = (xcb_map_request_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "parent", e->parent);
	add_assoc_long(return_value, "window", e->window);
}

event_xcb_configure_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_configure_notify_event_t *e = (xcb_configure_notify_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "above_sibling", e->above_sibling);
	add_assoc_long(return_value, "x", e->x);
	add_assoc_long(return_value, "y", e->y);
	add_assoc_long(return_value, "width", e->width);
	add_assoc_long(return_value, "height", e->height);
	add_assoc_long(return_value, "border_width", e->border_width);
	add_assoc_long(return_value, "override_redirect", e->override_redirect);
}

event_xcb_create_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_create_notify_event_t *e = (xcb_create_notify_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "parent", e->parent);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "x", e->x);
	add_assoc_long(return_value, "y", e->y);
	add_assoc_long(return_value, "width", e->width);
	add_assoc_long(return_value, "height", e->height);
	add_assoc_long(return_value, "border_width", e->border_width);
	add_assoc_long(return_value, "override_redirect", e->override_redirect);
}

event_xcb_map_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_map_notify_event_t *e = (xcb_map_notify_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "override_redirect", e->override_redirect);
}

event_xcb_unmap_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_unmap_notify_event_t *e = (xcb_unmap_notify_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "from_configure", e->from_configure);
}

event_xcb_destroy_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_destroy_notify_event_t *e = (xcb_destroy_notify_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "window", e->window);
}

event_xcb_leave_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_leave_notify_event_t *e = (xcb_leave_notify_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "mode", e->mode);
	add_assoc_long(return_value, "same_screen_focus", e->same_screen_focus);
}
event_xcb_motion_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_motion_notify_event_t *e = (xcb_motion_notify_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "same_screen", e->same_screen);
}
event_xcb_enter_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_enter_notify_event_t *e = (xcb_enter_notify_event_t *) evt;
	add_assoc_long(return_value, "detail", e->detail);
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "time", e->time);
	add_assoc_long(return_value, "root", e->root);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "child", e->child);
	add_assoc_long(return_value, "root_x", e->root_x);
	add_assoc_long(return_value, "root_y", e->root_y);
	add_assoc_long(return_value, "event_x", e->event_x);
	add_assoc_long(return_value, "event_y", e->event_y);
	add_assoc_long(return_value, "state", e->state);
	add_assoc_long(return_value, "mode", e->mode);
	add_assoc_long(return_value, "same_screen_focus", e->same_screen_focus);
}

event_xcb_reparent_notify(xcb_generic_event_t* evt, zval* return_value) {
	xcb_reparent_notify_event_t *e = (xcb_reparent_notify_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "event", e->event);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "parent", e->parent);
	add_assoc_long(return_value, "x", e->x);
	add_assoc_long(return_value, "y", e->y);
	add_assoc_long(return_value, "override_redirect", e->override_redirect);
}

event_xcb_expose(xcb_generic_event_t* evt, zval* return_value) {
	xcb_expose_event_t *e = (xcb_expose_event_t *) evt;
	add_assoc_long(return_value, "sequence", e->sequence);
	add_assoc_long(return_value, "window", e->window);
	add_assoc_long(return_value, "x", e->x);
	add_assoc_long(return_value, "y", e->y);
	add_assoc_long(return_value, "width", e->width);
	add_assoc_long(return_value, "height", e->height);
	add_assoc_long(return_value, "count", e->count);
}

event_generic(xcb_generic_event_t* evt, zval* return_value) {
	//	php_printf("here");
}

event_error(xcb_generic_event_t* evt, zval* return_value) {
	xcb_generic_error_t *e = (xcb_generic_error_t *) evt;
	add_assoc_long(return_value, "error_code", e->error_code);
	add_assoc_string(return_value, "url", "http://xcb.freedesktop.org/XcbUtil/api/group__xcb____event__t.html", 0);
}

ZEND_BEGIN_ARG_INFO(arginfo_xcb_wait_for_event, 0)
		ZEND_ARG_INFO(0, xcb_resource)
ZEND_END_ARG_INFO();

PHP_FUNCTION( xcb_wait_for_event) {
	php_xcb_connection *c;
	zval *zconnection;
	xcb_generic_event_t *evt;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zconnection) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(c, php_xcb_connection*, &zconnection, -1, PHP_XCB_CONNECTION_RES_NAME, le_xcb_connection);

	evt = xcb_wait_for_event(c->connection);
	if (xcb_event_get_label(evt->response_type)) {
		php_printf("php_xcb: event %s \n", (char*) xcb_event_get_label(evt->response_type));
		array_init(return_value);
		add_get_assoc_string_ex(return_value, "response_type", strlen("response_type") + 1, (const char *) xcb_event_get_label(evt->response_type), NULL, 1);
		switch (evt->response_type & ~0x80) {
		case XCB_BUTTON_PRESS:
			event_xcb_button_press(evt, return_value);
			break;
		case XCB_BUTTON_RELEASE:
			event_xcb_button_release(evt, return_value);
			break;
		case XCB_KEY_PRESS:
			event_xcb_key_press(evt, return_value);
			break;
		case XCB_KEY_RELEASE:
			event_xcb_key_release(evt, return_value);
			break;
		case XCB_CONFIGURE_REQUEST:
			event_xcb_configure_request(evt, return_value);
			break;
		case XCB_MAP_REQUEST:
			event_xcb_map_request(evt, return_value);
			break;
		case XCB_CONFIGURE_NOTIFY:
			event_xcb_configure_notify(evt, return_value);
			break;
		case XCB_CREATE_NOTIFY:
			event_xcb_create_notify(evt, return_value);
			break;
		case XCB_MAP_NOTIFY:
			event_xcb_map_notify(evt, return_value);
			break;
		case XCB_UNMAP_NOTIFY:
			event_xcb_unmap_notify(evt, return_value);
			break;
		case XCB_DESTROY_NOTIFY:
			event_xcb_destroy_notify(evt, return_value);
			break;
		case XCB_LEAVE_NOTIFY:
			event_xcb_leave_notify(evt, return_value);
			break;
		case XCB_MOTION_NOTIFY:
			event_xcb_motion_notify(evt, return_value);
			break;
		case XCB_ENTER_NOTIFY:
			event_xcb_enter_notify(evt, return_value);
			break;
		case XCB_REPARENT_NOTIFY:
			event_xcb_reparent_notify(evt, return_value);
			break;
		case XCB_EXPOSE:
			event_xcb_expose(evt, return_value);
			break;
		case 0:
			event_error(evt, return_value);
			break;
		default:
			php_printf("php_xcb: Unknown Event '%s' Recieved\n", (char*) xcb_event_get_label(evt->response_type));
			break;
		}
	} else {
		php_printf("php_xcb: Unknown Event type '%d' Recieved (%s) \n", evt->response_type, (char*) xcb_event_get_label(evt->response_type & 0x7f));
		array_init(return_value);
		add_assoc_long(return_value, "response_type", evt->response_type);

		switch (evt->response_type) {
		case 146:
			event_generic(evt, return_value);
			//add_assoc_long(return_value, "response_type", evt->first_event);
			break;
		case 150:
			event_generic(evt, return_value);
			//add_assoc_long(return_value, "response_type", evt->first_event);
			break;
		default:

			break;
		}
	}
}
