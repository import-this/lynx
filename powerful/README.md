# Powerful numbers

Small C program for identifying
[powerful numbers](http://en.wikipedia.org/wiki/Powerful_number).

## Instructions
* To **compile** the main executable, execute:  
    `$ make`
* To **run** the main executable, execute:  
    `$ ispowerful <number>`
* To create a library/object file:  
    `$ make powerful`
* To remove any files created run:  
    `$ make clean`

## Examples
```
$ ispowerful
Usage: % ispowerful <number>
$ ispowerful 1
1
$ ispowerful 2
0
$ ispowerful 4
1
$ ispowerful 1111
0
$ ispowerful 13068
1
$ ispowerful 0
The number specified should be positive.
$ ispowerful -4
The number specified should be positive.
$ ispowerful 1000000000000
The number specified is too large.
```
