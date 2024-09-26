let gl = undefined;
let ms = undefined;
let projectionMatrix = undefined;

function clamp(value, minVal, maxVal) {
    return Math.max(minVal, Math.min(value, maxVal));
}

function init() {
    let canvas = document.getElementById("webgl-canvas");
    gl = canvas.getContext("webgl2");
    if (!gl) { alert("Your Web browser doesn't support WebGL 2"); }

    gl.viewport(0, 0, canvas.width, canvas.height);
    aspect_ratio = canvas.width / canvas.height;

    gl.clearColor(0.2, 0.2, 0.2, 1.0);
    gl.enable(gl.DEPTH_TEST);

    ms = new MatrixStack();

    render();
}

function render() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    /*
    ms.push();
    ms.translate(0.8, -0.8, 1.0);
    ms.scale(size);
    sphere.color = vec4(1.0, 0.0, 0.0, 1.0);
    sphere.MV = ms.current();
    sphere.draw();
    ms.pop();
    */

    requestAnimationFrame(render);
}

window.onload = init;

