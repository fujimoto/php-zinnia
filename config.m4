PHP_ARG_WITH(zinnia,
  [whether to enable zinnia support],
  [  --with-zinnia=[dir]    enable zinnia support])

if test "$PHP_ZINNIA" != "no"; then
  if test -r "$PHP_ZINNIA/include/zinnia.h"; then
    PHP_ZINNIA_DIR="$PHP_ZINNIA"
  else
    AC_MSG_CHECKING(for zinnia in default path)
    for i in /usr /usr/local /usr/local/zinnia; do
      if test -r "$i/include/zinnia.h"; then
        PHP_ZINNIA_DIR=$i
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
    if test "x" = "x$PHP_ZINNIA_DIR"; then
      AC_MSG_ERROR(not found)
    fi
  fi

  PHP_REQUIRE_CXX()
  PHP_SUBST(ZINNIA_SHARED_LIBADD)
  PHP_ADD_INCLUDE($PHP_ZINNIA_DIR/include)
  PHP_ADD_LIBRARY_WITH_PATH(zinnia, $PHP_ZINNIA_DIR/$PHP_LIBDIR, ZINNIA_SHARED_LIBADD)
  PHP_ADD_LIBRARY(stdc++, 1, ZINNIA_SHARED_LIBADD)
  PHP_NEW_EXTENSION(zinnia, zinnia.cc, $ext_shared)
fi
