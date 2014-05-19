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
#include "php_zinnia.h"
#include "zinnia.h"

/*
 *  Zend class entry defs
 */
zend_class_entry* zinnia_recognizer_ce;
zend_object_handlers zinnia_recognizer_object_handlers;
struct zinnia_recognizer_object {
  zend_object std;
  zinnia::Recognizer* zinnia_recognizer;
};

zend_class_entry* zinnia_character_ce;
zend_object_handlers zinnia_character_object_handlers;
struct zinnia_character_object {
  zend_object std;
  zinnia::Character* zinnia_character;
};

zend_class_entry* zinnia_result_ce;
zend_object_handlers zinnia_result_object_handlers;
struct zinnia_result_object {
  zend_object std;
  zinnia::Result* zinnia_result;
};

zend_class_entry* zinnia_trainer_ce;
zend_object_handlers zinnia_trainer_object_handlers;
struct zinnia_trainer_object {
  zend_object std;
  zinnia::Trainer* zinnia_trainer;
};

/*
 *  Implementation of zinnia::Recognizer Class
 */
void zinnia_recognizer_free_storage(void *object TSRMLS_DC) {
  zinnia_recognizer_object *obj = (zinnia_recognizer_object*)object;
  delete obj->zinnia_recognizer; 

  zend_hash_destroy(obj->std.properties);
  FREE_HASHTABLE(obj->std.properties);

  efree(obj);
}

zend_object_value zinnia_recognizer_create_handler(zend_class_entry *type TSRMLS_DC) {
  zval *tmp;
  zend_object_value retval;

  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)emalloc(sizeof(zinnia_recognizer_object));
  memset(obj, 0, sizeof(zinnia_recognizer_object));
  obj->std.ce = type;

  ALLOC_HASHTABLE(obj->std.properties);
  zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
  zend_hash_copy(obj->std.properties, &type->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

  retval.handle = zend_objects_store_put(obj, NULL, zinnia_recognizer_free_storage, NULL TSRMLS_CC);
  retval.handlers = &zinnia_recognizer_object_handlers;

  return retval;
}

PHP_METHOD(Zinnia_Recognizer, __construct) {
  zinnia::Recognizer* zinnia_recognizer = NULL;
  zval *object = getThis();

  zinnia_recognizer = zinnia::Recognizer::create();
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(object TSRMLS_CC);
  obj->zinnia_recognizer = zinnia_recognizer;
}

PHP_METHOD(Zinnia_Recognizer, __destruct) {
}

PHP_METHOD(Zinnia_Recognizer, open) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  char* filename;
  int filename_len;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("s"), &filename, &filename_len) == FAILURE) {
    RETURN_FALSE;
  }

  bool r = zinnia_recognizer->open(filename);
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Recognizer, read) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  char* model_data;
  int model_data_len;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("s"), &model_data, &model_data_len) == FAILURE) {
    RETURN_FALSE;
  }

  bool r = zinnia_recognizer->open(model_data, model_data_len);
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Recognizer, close) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  bool r = zinnia_recognizer->close();
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Recognizer, size) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  size_t r = zinnia_recognizer->size();
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Recognizer, value) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  long i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("l"), &i) == FAILURE) {
    RETURN_FALSE;
  }

  const char* r = zinnia_recognizer->value(i);
  RETVAL_STRING(r, 1);
}

PHP_METHOD(Zinnia_Recognizer, classify) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  zval* character_zval_obj;
  long best;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("Ol"), &character_zval_obj, zinnia_character_ce, &best) == FAILURE) {
    RETURN_FALSE;
  }
  zinnia_character_object* character_obj = (zinnia_character_object*)zend_object_store_get_object(character_zval_obj TSRMLS_CC);
  zinnia::Character* zinnia_character = character_obj->zinnia_character;

  zinnia::Result* zinnia_result = zinnia_recognizer->classify(*zinnia_character, best);
  Z_TYPE_P(return_value) = IS_OBJECT;
  object_init_ex(return_value, zinnia_result_ce);

  zinnia_result_object *result_obj = (zinnia_result_object*)zend_object_store_get_object(return_value TSRMLS_CC);
  result_obj->zinnia_result = zinnia_result;
}

PHP_METHOD(Zinnia_Recognizer, what) {
  zinnia::Recognizer* zinnia_recognizer;
  zinnia_recognizer_object* obj = (zinnia_recognizer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_recognizer = obj->zinnia_recognizer;
  if (zinnia_recognizer == NULL) {
    RETURN_NULL();
  }

  const char* r = zinnia_recognizer->what();
  RETVAL_STRING(r, 1);
}

function_entry zinnia_recognizer_methods[] = {
  PHP_ME(Zinnia_Recognizer, __construct,    NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(Zinnia_Recognizer, __destruct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Recognizer, open,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Recognizer, read,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Recognizer, close,          NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Recognizer, size,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Recognizer, value,          NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Recognizer, classify,       NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Recognizer, what,           NULL, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

/*
 *  Implementation of zinnia::Character Class
 */
void zinnia_character_free_storage(void *object TSRMLS_DC) {
  zinnia_character_object *obj = (zinnia_character_object*)object;
  delete obj->zinnia_character; 

  zend_hash_destroy(obj->std.properties);
  FREE_HASHTABLE(obj->std.properties);

  efree(obj);
}

zend_object_value zinnia_character_create_handler(zend_class_entry *type TSRMLS_DC) {
  zval *tmp;
  zend_object_value retval;

  zinnia_character_object* obj = (zinnia_character_object*)emalloc(sizeof(zinnia_character_object));
  memset(obj, 0, sizeof(zinnia_character_object));
  obj->std.ce = type;

  ALLOC_HASHTABLE(obj->std.properties);
  zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
  zend_hash_copy(obj->std.properties, &type->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

  retval.handle = zend_objects_store_put(obj, NULL, zinnia_character_free_storage, NULL TSRMLS_CC);
  retval.handlers = &zinnia_character_object_handlers;

  return retval;
}

PHP_METHOD(Zinnia_Character, __construct) {
  zinnia::Character* zinnia_character = NULL;
  zval *object = getThis();

  zinnia_character = zinnia::Character::create();
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(object TSRMLS_CC);
  obj->zinnia_character = zinnia_character;
}

PHP_METHOD(Zinnia_Character, __destruct) {
}

PHP_METHOD(Zinnia_Character, __toString) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  int buf_len = 0xffff;
  char* buf = (char*)emalloc(buf_len);
  zinnia_character->toString(buf, buf_len);

  RETVAL_STRINGL(buf, strlen(buf), 0);
}

PHP_METHOD(Zinnia_Character, setValue) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  char* value;
  int value_len;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("s"), &value, &value_len) == FAILURE) {
    RETURN_FALSE;
  }

  zinnia_character->set_value(value, value_len);
}

PHP_METHOD(Zinnia_Character, value) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  const char* r = zinnia_character->value();
  RETVAL_STRING(r, 1);
}

PHP_METHOD(Zinnia_Character, setWidth) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  long width;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("l"), &width) == FAILURE) {
    RETURN_FALSE;
  }

  zinnia_character->set_width(width);
}

PHP_METHOD(Zinnia_Character, setHeight) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  long height;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("l"), &height) == FAILURE) {
    RETURN_FALSE;
  }

  zinnia_character->set_height(height);
}

PHP_METHOD(Zinnia_Character, width) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  size_t r = zinnia_character->width();
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Character, height) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  size_t r = zinnia_character->height();
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Character, clear) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  zinnia_character->clear();
}

PHP_METHOD(Zinnia_Character, add) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  long id, x, y;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("lll"), &id, &x, &y) == FAILURE) {
    RETURN_FALSE;
  }

  bool r = zinnia_character->add(id, x, y);
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Character, strokesSize) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  size_t r = zinnia_character->strokes_size();
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Character, strokeSize) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  long id;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("l"), &id) == FAILURE) {
    RETURN_FALSE;
  }

  size_t r = zinnia_character->stroke_size(id);
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Character, x) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  long id, i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("ll"), &id, &i) == FAILURE) {
    RETURN_FALSE;
  }

  int r = zinnia_character->x(id, i);
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Character, y) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  long id, i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("ll"), &id, &i) == FAILURE) {
    RETURN_FALSE;
  }

  int r = zinnia_character->y(id, i);
  RETVAL_LONG(r);
}

PHP_METHOD(Zinnia_Character, parse) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  char* data;
  long data_len;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("s"), &data, &data_len) == FAILURE) {
    RETURN_FALSE;
  }

  bool r = zinnia_character->parse(data);
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Character, what) {
  zinnia::Character* zinnia_character;
  zinnia_character_object* obj = (zinnia_character_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_character = obj->zinnia_character;
  if (zinnia_character == NULL) {
    RETURN_NULL();
  }

  const char* r = zinnia_character->what();
  RETVAL_STRING(r, 1);
}

function_entry zinnia_character_methods[] = {
  PHP_ME(Zinnia_Character, __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(Zinnia_Character, __destruct,      NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Character, __toString,      NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, setValue,        NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, value,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, setWidth,        NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, setHeight,       NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, width,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, height,          NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, clear,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, add,             NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, strokesSize,     NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, strokeSize,      NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, x,               NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, y,               NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, parse,           NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Character, what,            NULL, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

/*
 *  Implementation of zinnia::Result Class
 */
void zinnia_result_free_storage(void *object TSRMLS_DC) {
  zinnia_result_object *obj = (zinnia_result_object*)object;
  delete obj->zinnia_result; 

  zend_hash_destroy(obj->std.properties);
  FREE_HASHTABLE(obj->std.properties);

  efree(obj);
}

zend_object_value zinnia_result_create_handler(zend_class_entry *type TSRMLS_DC) {
  zval *tmp;
  zend_object_value retval;

  zinnia_result_object* obj = (zinnia_result_object*)emalloc(sizeof(zinnia_result_object));
  memset(obj, 0, sizeof(zinnia_result_object));
  obj->std.ce = type;

  ALLOC_HASHTABLE(obj->std.properties);
  zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
  zend_hash_copy(obj->std.properties, &type->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

  retval.handle = zend_objects_store_put(obj, NULL, zinnia_result_free_storage, NULL TSRMLS_CC);
  retval.handlers = &zinnia_result_object_handlers;

  return retval;
}

PHP_METHOD(Zinnia_Result, __construct) {
}

PHP_METHOD(Zinnia_Result, __destruct) {
}

PHP_METHOD(Zinnia_Result, value) {
  zinnia::Result* zinnia_result;
  zinnia_result_object* obj = (zinnia_result_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_result = obj->zinnia_result;
  if (zinnia_result == NULL) {
    RETURN_NULL();
  }

  long i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("l"), &i) == FAILURE) {
    RETURN_FALSE;
  }

  const char* r = zinnia_result->value(i);
  RETVAL_STRING(r, 1);
}

PHP_METHOD(Zinnia_Result, score) {
  zinnia::Result* zinnia_result;
  zinnia_result_object* obj = (zinnia_result_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_result = obj->zinnia_result;
  if (zinnia_result == NULL) {
    RETURN_NULL();
  }

  long i;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("l"), &i) == FAILURE) {
    RETURN_FALSE;
  }

  float r = zinnia_result->score(i);
  RETVAL_DOUBLE(r);
}

PHP_METHOD(Zinnia_Result, size) {
  zinnia::Result* zinnia_result;
  zinnia_result_object* obj = (zinnia_result_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_result = obj->zinnia_result;
  if (zinnia_result == NULL) {
    RETURN_NULL();
  }

  size_t r = zinnia_result->size();
  RETVAL_LONG(r);
}

function_entry zinnia_result_methods[] = {
  PHP_ME(Zinnia_Result, __construct,        NULL, ZEND_ACC_PRIVATE | ZEND_ACC_CTOR)
  PHP_ME(Zinnia_Result, __destruct,         NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Result, value,              NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Result, score,              NULL, ZEND_ACC_PUBLIC)
  PHP_ME(Zinnia_Result, size,               NULL, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

/*
 *  Implementation of zinnia::Trainer Class
 */
void zinnia_trainer_free_storage(void *object TSRMLS_DC) {
  zinnia_trainer_object *obj = (zinnia_trainer_object*)object;
  delete obj->zinnia_trainer; 

  zend_hash_destroy(obj->std.properties);
  FREE_HASHTABLE(obj->std.properties);

  efree(obj);
}

zend_object_value zinnia_trainer_create_handler(zend_class_entry *type TSRMLS_DC) {
  zval *tmp;
  zend_object_value retval;

  zinnia_trainer_object* obj = (zinnia_trainer_object*)emalloc(sizeof(zinnia_trainer_object));
  memset(obj, 0, sizeof(zinnia_trainer_object));
  obj->std.ce = type;

  ALLOC_HASHTABLE(obj->std.properties);
  zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
  zend_hash_copy(obj->std.properties, &type->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

  retval.handle = zend_objects_store_put(obj, NULL, zinnia_trainer_free_storage, NULL TSRMLS_CC);
  retval.handlers = &zinnia_trainer_object_handlers;

  return retval;
}

PHP_METHOD(Zinnia_Trainer, __construct) {
  zinnia::Trainer* zinnia_trainer = NULL;
  zval *object = getThis();

  zinnia_trainer = zinnia::Trainer::create();
  zinnia_trainer_object* obj = (zinnia_trainer_object*)zend_object_store_get_object(object TSRMLS_CC);
  obj->zinnia_trainer = zinnia_trainer;
}

PHP_METHOD(Zinnia_Trainer, __destruct) {
}

PHP_METHOD(Zinnia_Trainer, add) {
  zinnia::Trainer* zinnia_trainer;
  zinnia_trainer_object* obj = (zinnia_trainer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_trainer = obj->zinnia_trainer;
  if (zinnia_trainer == NULL) {
    RETURN_NULL();
  }

  zval* character_zval_obj;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("O"), &character_zval_obj, zinnia_character_ce) == FAILURE) {
    RETURN_FALSE;
  }
  zinnia_character_object* character_obj = (zinnia_character_object*)zend_object_store_get_object(character_zval_obj TSRMLS_CC);
  zinnia::Character* zinnia_character = character_obj->zinnia_character;

  bool r = zinnia_trainer->add(*zinnia_character);
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Trainer, clear) {
  zinnia::Trainer* zinnia_trainer;
  zinnia_trainer_object* obj = (zinnia_trainer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_trainer = obj->zinnia_trainer;
  if (zinnia_trainer == NULL) {
    RETURN_NULL();
  }

  zinnia_trainer->clear();
}

PHP_METHOD(Zinnia_Trainer, train) {
  zinnia::Trainer* zinnia_trainer;
  zinnia_trainer_object* obj = (zinnia_trainer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_trainer = obj->zinnia_trainer;
  if (zinnia_trainer == NULL) {
    RETURN_NULL();
  }

  char* filename;
  int filename_len;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, const_cast<char*>("s"), &filename, &filename_len) == FAILURE) {
    RETURN_FALSE;
  }

  bool r = zinnia_trainer->train(filename);
  RETVAL_BOOL(r);
}

PHP_METHOD(Zinnia_Trainer, what) {
  zinnia::Trainer* zinnia_trainer;
  zinnia_trainer_object* obj = (zinnia_trainer_object*)zend_object_store_get_object(getThis() TSRMLS_CC);
  zinnia_trainer = obj->zinnia_trainer;
  if (zinnia_trainer == NULL) {
    RETURN_NULL();
  }

  const char* r = zinnia_trainer->what();
  RETVAL_STRING(r, 1);
}

function_entry zinnia_trainer_methods[] = {
  PHP_ME(Zinnia_Trainer, __construct,       NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(Zinnia_Trainer, __destruct,        NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Trainer, add,               NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Trainer, clear,             NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Trainer, train,             NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  PHP_ME(Zinnia_Trainer, what,              NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
  {NULL, NULL, NULL}
};

/*
 *  Module Defs
 */
PHP_MINIT_FUNCTION(zinnia) {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, "Zinnia_Recognizer", zinnia_recognizer_methods);
  zinnia_recognizer_ce = zend_register_internal_class(&ce TSRMLS_CC);
  zinnia_recognizer_ce->create_object = zinnia_recognizer_create_handler;
  memcpy(&zinnia_recognizer_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  zinnia_recognizer_object_handlers.clone_obj = NULL;

  INIT_CLASS_ENTRY(ce, "Zinnia_Character", zinnia_character_methods);
  zinnia_character_ce = zend_register_internal_class(&ce TSRMLS_CC);
  zinnia_character_ce->create_object = zinnia_character_create_handler;
  memcpy(&zinnia_character_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  zinnia_character_object_handlers.clone_obj = NULL;

  INIT_CLASS_ENTRY(ce, "Zinnia_Result", zinnia_result_methods);
  zinnia_result_ce = zend_register_internal_class(&ce TSRMLS_CC);
  zinnia_result_ce->create_object = zinnia_result_create_handler;
  memcpy(&zinnia_result_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  zinnia_result_object_handlers.clone_obj = NULL;

  INIT_CLASS_ENTRY(ce, "Zinnia_Trainer", zinnia_trainer_methods);
  zinnia_trainer_ce = zend_register_internal_class(&ce TSRMLS_CC);
  zinnia_trainer_ce->create_object = zinnia_trainer_create_handler;
  memcpy(&zinnia_trainer_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  zinnia_trainer_object_handlers.clone_obj = NULL;

  return SUCCESS;
}

zend_module_entry zinnia_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_ZINNIA_EXTNAME,
    NULL,                  /* Functions */
    PHP_MINIT(zinnia),
    NULL,                  /* MSHUTDOWN */
    NULL,                  /* RINIT */
    NULL,                  /* RSHUTDOWN */
    NULL,                  /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_ZINNIA_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZINNIA
extern "C" {
ZEND_GET_MODULE(zinnia)
}
#endif
