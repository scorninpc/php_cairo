/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth Smith <auroraeosrose@php.net>                      |
  |         Michael Maclean <mgdm@php.net>                               |
  |         Akshat Gupta <g.akshat@gmail.com>                            |
  +----------------------------------------------------------------------+
*/

/* $Id: cairo_path.c 310358 2011-04-19 14:53:26Z mgdm $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cairo.h"

zend_class_entry *cairo_ce_cairopath;

static void cairo_path_object_destroy(void *object TSRMLS_DC)
{
	cairo_path_object *path = (cairo_path_object *)object;
	zend_hash_destroy(path->std.properties);
	FREE_HASHTABLE(path->std.properties);

	if(path->path){
		cairo_path_destroy(path->path);
	}
	efree(object);
}

static zend_object cairo_path_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object retval;
	cairo_path_object *path;
	zval *temp;

	path = ecalloc(1, sizeof(cairo_path_object));

	path->std.ce = ce;
	path->path = NULL;

	ALLOC_HASHTABLE(path->std.properties);
	zend_hash_init(path->std.properties, 0, NULL, ZVAL_PTR_DTOR,0);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(path->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &temp, sizeof(zval *));
#else
	object_properties_init(&path->std, ce);
#endif
	retval.handlers = &cairo_std_object_handlers;
	return retval;
}

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(cairo_path)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "CairoPath", NULL);
	cairo_ce_cairopath = zend_register_internal_class(&ce TSRMLS_CC);
	cairo_ce_cairopath->create_object = cairo_path_object_new;

	return SUCCESS;

}

PHP_CAIRO_API zend_class_entry* php_cairo_get_path_ce()
{
	return cairo_ce_cairopath;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
