# C AsciiDots Interpreter

This is an AscciDots interpreter written in C.


### Command line options

> Options:  
>   -d or --debug : Enable debug mode  
>   -h or --help : Show a help message  
>   -i or --input : Specify an input filename  
  
Where no input file argument are specified the default file is "samples/bad_apple.dots"

 
### The debug mode

Ths is a mode where you can se the dots moving frame by frame.  
And each dot has a different color and their value indicated at the bottom.


### Samples files

There is some samples AsciiDots file in the "samples" folder.  
There samples have been take from [this repo](https://github.com/aaronjanse/asciidots).


### Missing features

Some features of AsciiDots lang are missing and will be implemented soon:
- The '!' character below an operation
- Comments
- The '@' character
- Operators : ^ G L !
- Libraries
- Warps
- Filters : and ;

Some other features are not planed to be implemented:
- Non buffered print with single quote
- Non ASCII characters

---

Copyright 2022 kolte200
