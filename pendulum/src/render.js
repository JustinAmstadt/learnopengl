// WebGL code taken from Dave Shreiner
// Pendulum code made by Justin Amstadt

'use strict;'

let gl = undefined;        // WebGL context
let program = undefined;   // Our shader program
let numVerts = 200;
let upperRotation = 0;
let lowerRotation = 0;
let positiveUpperSwing = true;
let positiveLowerSwing = true;
let previousTime = performance.now();
let speed = 50.0;
let rotationMax = 45;


function init() {
    let canvas = document.getElementById("webgl-canvas");

    gl = canvas.getContext("webgl2");
    if (!gl) {
        alert("WebGL doesn't seem to be available."); 
        return;
    }

    gl.viewport(0, 0, canvas.width, canvas.height);

    program = initShaders(gl, "vertex-shader", "fragment-shader");

    program.MV = function() {
        let location = gl.getUniformLocation(program, "MV");

        return function(MV) {
            gl.uniformMatrix4fv(location, false, flatten(MV));
        };
    }();
    
    program.uNumVerts = function() {
        let location = gl.getUniformLocation(program, "uNumVerts");

        return function(uNumVerts) {
            gl.uniform1i(location, uNumVerts);
        };
    }();
    
    lineProgram = initShaders(gl, "line-vertex-shader", "fragment-shader");

    lineProgram.MV = function() {
        let location = gl.getUniformLocation(lineProgram, "MV");

        return function(MV) {
            gl.uniformMatrix4fv(location, false, flatten(MV));
        };
    }();

    gl.clearColor(0.2, 0.2, 0.2, 1.0);

    render();
}

function render() {
    let currentTime = performance.now();
    let deltaTime = (currentTime - previousTime) / 1000; // convert to seconds
    previousTime = currentTime;

    gl.clear(gl.COLOR_BUFFER_BIT);

    // Upper Arm
    gl.useProgram(lineProgram);

    // Yes, this line scales everything down. 
    // The whole pendulum was too big for the screen and this was the easier way to shrink the whole thing.
    let S = mult(translate(0.0, 1.0, 0.0), mult(rotate(upperRotation, vec3(0, 0, 1)), scalem(0.8, 0.8, 0.8)));
    lineProgram.MV(S);

    gl.drawArrays(gl.LINES, 0, 2);

    // Upper Ball
    gl.useProgram(program);

    S = mult(S, translate(0, -1, 0));
    program.MV(mult(S, scalem(0.1, 0.1, 0.1)));
    program.uNumVerts(numVerts);

    gl.drawArrays(gl.TRIANGLE_FAN, 0, numVerts);

    // Lower Arm
    gl.useProgram(lineProgram);

    S = mult(S, rotate(lowerRotation, vec3(0, 0, 1)));
    lineProgram.MV(mult(S, scalem(1, 1, 1)));

    gl.drawArrays(gl.LINES, 0, 2);

    // Lower Ball
    gl.useProgram(program);

    S = mult(S, translate(0, -1, 0));
    program.MV(mult(S, scalem(0.1, 0.1, 0.1)));
    program.uNumVerts(numVerts);

    gl.drawArrays(gl.TRIANGLE_FAN, 0, numVerts);

    requestAnimationFrame(render);

    let { swingBool: upperSwingBool, rotation: upperRotationUpdated } = updateSwing(upperRotation, positiveUpperSwing, deltaTime, speed);
    positiveUpperSwing = upperSwingBool;
    upperRotation = upperRotationUpdated;

    let { swingBool: lowerSwingBool, rotation: lowerRotationUpdated } = updateSwing(lowerRotation, positiveLowerSwing, deltaTime, speed * 3.0);
    positiveLowerSwing = lowerSwingBool;
    lowerRotation = lowerRotationUpdated;
}

function updateSwing(rotation, swingBool, deltaTime, speed) {
    if (swingBool) {
        rotation += deltaTime * speed;
        if (rotation > rotationMax) { swingBool = false; }
    } else {
        rotation -= deltaTime * speed;
        if (rotation < -rotationMax) { swingBool = true; }
    }

    return { swingBool, rotation };
}

window.onload = init;