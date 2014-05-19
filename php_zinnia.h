/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Masaki Fujimoto <fujimoto@php.net>                           |
  +----------------------------------------------------------------------+
*/
#ifndef PHP_ZINNIA_H
#define PHP_ZINNIA_H

#define PHP_ZINNIA_EXTNAME  "zinnia"
#define PHP_ZINNIA_EXTVER   "0.0.1"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif 

extern "C" {
#include "php.h"
}

extern zend_module_entry zinnia_module_entry;
#define phpext_zinnia_ptr &zinnia_module_entry;

#endif /* PHP_ZINNIA_H */
