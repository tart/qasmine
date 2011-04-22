# Qasmine

A Qt application to run [Jasmine](http://pivotal.github.com/jasmine/) from command line

## Prerequisites

* [Qt >= 4.7](http://qt.nokia.com/) : Qt Library with Webkit module
* [jasmine](http://pivotal.github.com/jasmine/) : Jasmine BDD


## How to compile

Make sure you have Qt Development environment

After cloning repository, type

<code>
cd src && qmake && make 
./qasmine /where/jasmine/SpecRunner.html --verbose
</code>

You can check exit code to get number of errors, so you can write some other scripts (like git hooks) with such an example
<code>
./qasmine /where/jasmine/SpecRunner.html > /dev/null ; echo $?
</code>

## Exit codes
* 255 : File not found or cannot be loaded
* 0 : Success
* > 0 : number of errors of specs
