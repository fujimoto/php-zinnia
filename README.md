# Zinnia PHP Extension

php extension for [Zinnia] (http://zinnia.sourceforge.net/)

## Installation

install Zinnia first (typicall, will be located in /usr/local), and then

```
$ cd php-zinnia
$ phpize
$ ./configure
$ make
$ sudo make install
```

finally, add followings to your php.ini:

```
extension=zinnia.so
```

## Usage

basically php-zinnia simply wraps [Zinnia C++ API] (http://zinnia.sourceforge.net/doxygen/annotated.html). a typical usage will be like this:

```
<?php
$width = 300;
$height = 300;

$train_data = array(
    array(
        'char'      => 'a',
        'signal'    => array(
            // stroke-1
            array(
                array(10, 12),
                array(11, 19),
                array(9, 29),
                // ...
            ),
            // stroke-2
            array(
                // ...
            ),
            // ...
        ),
    ),
    array(
        'char'      => 'a',
        'signal'    => array(
            // stroke-1
            array(
                array(11, 12),
                array(12, 21),
                array(11, 29),
                // ...
            ),
            // stroke-2
            array(
                // ...
            ),
            // ...
        ),
    ),
    array(
        'char'      => 'b',
        'signal'    => array(
            // stroke-1
            array(
                array(30, 12),
                array(29, 19),
                array(31, 29),
                // ...
            ),
            // stroke-2
            array(
                // ...
            ),
            // ...
        ),
    ),
);

$classify_data = array(
    // stroke-1
    array(
        array(10, 12),
        array(11, 19),
        array(9, 29),
        // ...
    ),
    // stroke-2
    array(
        // ...
    ),
    // ...
);

// train
$train = new Zinnia_Trainer();
$char = new Zinnia_Character();

foreach ($train_data as $train_row) {
    $char->clear();
    $char->setWidth($width);
    $char->setHeight($height);
    $char->setValue($train_row['char']);
    foreach ($train_row['signal'] as $i => $s) {
        foreach ($s as $xy) {
            $char->add($i, $xy[0], $xy[1]);
        }
    }
    $train->add($char);
}

$train->train("/tmp/model");    // generates /tmp/model.txt

// classify
$recognizer = new Zinnia_Recognizer();
$recognizer->open("/tmp/model");    // or read() is also available to read from memory

$char = new Zinnia_Character();
$char->clear();

$char->setWidth($width);
$char->setHeight($height);
foreach ($classify_data as $i => $s) {
    foreach ($s as $xy) {
        $char->add($i, $xy[0], $xy[1]);
    }
}
$r = $recognizer->classify($char, 10);

$result = array();
for ($i = 0; $i < $r->size(); $i++) {
    $result[] = array(
        'char' => $r->value($i),
        'score' => $r->score($i),
    );
}
```
