# berry_arduino
berrylang for arduino
Current berry version 1.0.0

# Gotchas
be_modtab.c and be_port.c should be place on the src or on the sketch root alongside .ino to be auto discovered


# Adding custom modules
create folder for modules with src ext berry_nxtfi/src
create your custom module be_gpio_lib.c add the #include be_mapping.h and the be_extern_native_module(gpio) and your be_extern_native_class(gpio) next
./map_build.exe -o ../../generate -i ../../src ../../berry_nxtfi/src ../../default -c ../../inc/berry_conf.h

specify this on

# todo 

# Source
https://github.com/Skiars/berry/tree/fddb25b2c58f9824862eafd37f6f0df2b0907e02
