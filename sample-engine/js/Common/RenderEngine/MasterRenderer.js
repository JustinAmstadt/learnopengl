class MasterRenderer {
    #projectionMatrix;
    #shader;
    #renderer;

    #entities;

    constructor(gl, vertexShaderSrc, fragmentShaderSrc) {
        gl.enable(gl.GL_CULL_FACE);
        gl.cullFace(gl.GL_BACK);
        this.#projectionMatrix = perspective(45, canvas.width / canvas.height, 0.1, 1000);
        this.#shader = new StaticShader(gl, vertexShaderSrc, fragmentShaderSrc);
        this.#renderer = new EntityRenderer(gl, shader, this.#projectionMatrix)
    }

    render(camera) {
        this.prepare();
        this.#shader.start();
        this.#shader.loadViewMatrix(camera);
        this.#renderer.render(this.#entities);
        this.#shader.stop();
        this.#entities = new Map();
    }

    processEntity(entity) {
        let entityModel = entity.model;
        let batch = this.#entities.get(entityModel);
        if (batch !== null) {
            batch.push(entity);
        } else {
            let newBatch = [];
            newBatch.push(entity);
            this.#entities.set(entityModel, newBatch);
        }
    }

    prepare(gl) {
        gl.enable(gl.DEPTH_TEST);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        gl.clearColor(0.2, 0.2, 0.2, 1.0);
    }
}