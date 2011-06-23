//Override jasmine before page load by listening interval
var jasmine;
var timer = setInterval(function () {
    if (jasmine) {
        jasmine.Env.prototype.executeQasmine = jasmine.Env.prototype.execute;

        jasmine.Env.prototype.execute = function () {}; //override execute
        jasmine.currentEnv_ = undefined; //unset current env

        clearInterval(timer);
    }
}, 1);

