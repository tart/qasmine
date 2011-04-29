# Qasmine

A Qt application to run [Jasmine](http://pivotal.github.com/jasmine/) from command line

## Prerequisites

* [Qt >= 4.7](http://qt.nokia.com/) : Qt Library with Webkit module
* [jasmine](http://pivotal.github.com/jasmine/) : Jasmine BDD


## How to compile

Make sure you have Qt Development environment

After cloning repository, type

<pre>
cd src && qmake && make 
./qasmine /where/jasmine/SpecRunner.html --verbose
</pre>

You can check exit code to get number of errors, so you can write some other scripts (like git hooks) with such an example
<pre>
./qasmine /where/jasmine/SpecRunner.html > /dev/null ; echo $?
</pre>

Those, who want to run qasmine in an environment which doesnt have X, they can use [xvfb-run](http://en.wikipedia.org/wiki/Xvfb)
<pre>
xvfb-run ./qasmine /where/jasmine/SpecRunner.html
</pre>

## Exit codes
* 255 : File not found or cannot be loaded
* 0 : Success
* > 0 : number of errors of specs
