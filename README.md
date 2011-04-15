# Qasmine

A Qt application to run [Jasmine](http://pivotal.github.com/jasmine/) from command line

## Prerequisites

* [Qt >= 4.7](http://qt.nokia.com/) : Qt Library with Webkit module
* [jasmine](http://pivotal.github.com/jasmine/) : Jasmine BDD


## How to compile

Make sure you have Qt Development environment

After cloning repository, type

    cd src && qmake && make 
    ./qasmine /where/jasmine/SpecRunner.html --verbose
