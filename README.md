# berry_arduino
berrylang for arduino
Current berry version 1.0.0 latest at the time writing. 
Thanks to s-hadinger one of Tasmota contributors for his work on berry tasmota, this library was based and mostly a copy from his works.

# Gotchas
```
Note: be_modtab.c and be_port.c should be place on the src or on the sketch root alongside .ino to be auto discovered
Copy this to arduino libraries:
https://github.com/rjjrbatarao/berry_mapping
To generate mapping:
chmod u+x generate.sh
./generate.sh
```

# Adding custom modules
```
create folder for modules with src ext berry_nxtfi/src
create your custom module ie. be_gpio_lib.c inside custom folder
chmod u+x generate.sh
./generate.sh
copy the custom .c module to src check the path of the include if correctly specified
create new tab in your sketch as ino ie berry_gpio
and create the function logic inside extern "c" { your custom functions here }
```

# Todo
* ``fix bug on gpio PULLUP PULLDOWN amd LOW not working`` not a bug it should be alphabetically ordered

# Source
https://github.com/Skiars/berry/tree/fddb25b2c58f9824862eafd37f6f0df2b0907e02
