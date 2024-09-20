'use strict;'

let gl = undefined;        // WebGL context
let program = undefined;   // Our shader program
let numVerts = 200;
let rotation = 0;
let positiveSwing = true;
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

    gl.useProgram(lineProgram);

    let S = mult(translate(0.0, 1.0, 0.0), mult(rotate(rotation, vec3(0, 0, 1)), scalem(1, 1, 1)));
    lineProgram.MV(S);

    gl.drawArrays(gl.LINES, 0, 2);

    gl.useProgram(program);

    S = mult(translate(0.0, 1.0, 0.0), mult(rotate(rotation, vec3(0, 0, 1)), mult(translate(0, -1, 0), scalem(0.1, 0.1, 0.1))));
    program.MV(S);
    program.uNumVerts(numVerts);

    gl.drawArrays(gl.TRIANGLE_FAN, 0, numVerts);

    requestAnimationFrame(render);

    if (positiveSwing) {
        rotation += deltaTime * speed;
        if (rotation > rotationMax) { positiveSwing = false; }
    } else {
        rotation -= deltaTime * speed;
        if (rotation < -rotationMax) { positiveSwing = true; }
    }

    console.log(rotation, positiveSwing)
}

window.onload = init;