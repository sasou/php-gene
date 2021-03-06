/*
 +----------------------------------------------------------------------+
 | gene                                                                 |
 +----------------------------------------------------------------------+
 | This source file is subject to version 3.01 of the PHP license,      |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.php.net/license/3_01.txt                                  |
 | If you did not receive a copy of the PHP license and are unable to   |
 | obtain it through the world-wide-web, please send a note to          |
 | license@php.net so we can mail you a copy immediately.               |
 +----------------------------------------------------------------------+
 | Author: Sasou  <admin@php-gene.com> web:www.php-gene.com             |
 +----------------------------------------------------------------------+
 */

#ifndef GENE_REQUEST_H
#define GENE_REQUEST_H

#define GENE_REQUEST_IS_METHOD(ce, x) \
PHP_METHOD(ce, is##x) {\
	zval *me;\
	if (!GENE_G(method)) { \
		RETURN_FALSE; \
	} \
	MAKE_STD_ZVAL(me);\
	ZVAL_STRING(me, GENE_G(method), 1);\
	if (strncasecmp(#x, Z_STRVAL_P(me), Z_STRLEN_P(me)) == 0) { \
		zval_ptr_dtor(&me);\
		RETURN_TRUE; \
	} \
	zval_ptr_dtor(&me);\
	RETURN_FALSE; \
}

#define GENE_REQUEST_METHOD(ce, x, type) \
PHP_METHOD(ce, x) { \
	char *name; \
	int  len; \
    zval *ret; \
	zval *def = NULL; \
	if (ZEND_NUM_ARGS() == 0) { \
		ret = request_query(type, NULL, 0 TSRMLS_CC); \
	}else if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &name, &len, &def) == FAILURE) { \
		return; \
	} else { \
		ret = request_query(type, name, len TSRMLS_CC); \
		if (ZVAL_IS_NULL(ret)) { \
			if (def != NULL) { \
				zval_ptr_dtor(&ret); \
				RETURN_ZVAL(def, 1, 0); \
			} \
		} \
	} \
	RETURN_ZVAL(ret, 1, 1); \
}

extern zend_class_entry *gene_request_ce;
zval * request_query(int type, char * name, int len TSRMLS_DC);

GENE_MINIT_FUNCTION (request);

#endif
