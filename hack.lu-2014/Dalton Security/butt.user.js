// ==UserScript==
// @name       FreddyWeb
// @namespace  http://s0beit.me
// @version    1.0
// @description  fuck off craptcha
// @match      https://wildwildweb.fluxfingers.net:1422/
// @copyright  2014+, s0beit
// @require    http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js
// @run-at     document-start
// ==/UserScript==

HTMLCanvasElement.prototype.getContext2 = HTMLCanvasElement.prototype.getContext;

var canvasCount = 0;
var captchaElements = [];

function solveCaptcha() {
    captchaElements.sort(function(a, b) {
        return a.n > b.n;
    });
    
    var captchaString = '';
    for(var i = 0; i < captchaElements.length; i++) {
        captchaString += captchaElements[i].t;
    }
    
    console.log(captchaString);
    
    $('input[name="solution"]').val(captchaString);
    $('form').submit();
}

HTMLCanvasElement.prototype.getContext = function(type) {
    console.log('getContext(' + type + ')');
    var returnValue = this.getContext2(type);
    console.log('returnValue.fillText = ' + returnValue.fillText);
    returnValue.fillText2 = returnValue.fillText;
    returnValue.fillText = function(text, x, y) {
        canvasCount++;
        console.log('ft[' + x + '][' + canvasCount + ']: ' + text);
        captchaElements.push({n:x, t:text});
        
        if(canvasCount == 8) {
            solveCaptcha();
        }
        
        return this.fillText2(text, x, y);
    };
    
    return returnValue;
};