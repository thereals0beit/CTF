// ==UserScript==
// @name       FreddyWeb v2
// @namespace  http://s0beit.me
// @version    1.0
// @description  fuck off craptcha
// @match      https://wildwildweb.fluxfingers.net:1422/
// @copyright  2014+, s0beit
// @run-at     document-start
// ==/UserScript==

console.log('Loading...');
console.log(HTMLCanvasElement.prototype.getContext);
console.log(CanvasRenderingContext2D.prototype.fillText);

CanvasRenderingContext2D.prototype.fillText2 = CanvasRenderingContext2D.prototype.fillText;
CanvasRenderingContext2D.prototype.fillText = function(text, x, y) {
    canvasCount++;
    console.log('ft[' + x + '][' + canvasCount + ']: ' + text);
    captchaElements.push({n:x, t:text});
    if(canvasCount == 8) { solveCaptcha(); }
    return this.fillText2(text, x, y);
};

console.log('Hook in place...');

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
    
    unsafeWindow.document.getElementsByName('solution')[0].value = captchaString;
    
    if(document.getElementsByTagName('a')[2].getAttribute('href').indexOf('login') != -1) {
        console.log('OK!');
        
        unsafeWindow.document.location = document.getElementsByTagName('a')[2].getAttribute('href');
    } else {
        console.log('Solving...');
        
        unsafeWindow.document.getElementsByName('solution')[0].parentElement.submit();
    }
}
