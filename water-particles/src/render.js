'use strict;'

let gl = undefined;        // WebGL context
let program = undefined;   // Our shader program
let numVerts = 200;
let lastTime = 0;
let deltaTime = 0.16;
let particleSystem = undefined;

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

    gl.clearColor(0.2, 0.2, 0.2, 1.0);

    // Make particle system
    let numParticles = 2;
    let h = 0.1;
    let k = 1;
    particleSystem = new ParticleSystem(numParticles, h, k);

    // Fill density and pressure values out
    particleSystem.updateDensityPressure(particleSystem.h, particleSystem.k);

    console.log(particleSystem)

    render();
}

function render() {
    let currentTime = performance.now();
    deltaTime = (currentTime - lastTime) / 1000.0; // Current time in seconds
    lastTime = currentTime;

    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.useProgram(program);

    particleSystem.updateDensityPressure(particleSystem.h, particleSystem.k, particleSystem.restDensity);

    for (let i = 0; i < particleSystem.numParticles; i++) {
        console.log(i + ": " + particleSystem.particles[i].toString())
        let neighbors = particleSystem.findNeighbors(i);
        let S = particleSystem.particles[i].update(deltaTime, neighbors, particleSystem.h);
        program.MV(S);
        program.uNumVerts(numVerts);

        gl.drawArrays(gl.TRIANGLE_FAN, 0, numVerts);
    }

    requestAnimationFrame(render);
}

window.onload = init;