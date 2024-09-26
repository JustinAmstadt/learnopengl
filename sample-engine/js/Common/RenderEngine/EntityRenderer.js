class EntityRenderer {
    #shader;

    /**
     * @param {any} gl 
     * @param {StaticShader} shader 
     * @param {mat4} projectionMatrix 
     */
    constructor(gl, shader, projectionMatrix) {
        this.#shader = shader;
        this.#shader.start(gl);
        this.#shader.loadProjectionMatrix(projectionMatrix);
        this.#shader.stop(gl);
    }

    /**
     * @param {any} gl 
     * @param {MatrixStack} ms
     * @param {Map<TexturedModel, Entity[]>} entities 
     */
    render(gl, ms, entities) {
        for (let model of entities.key) {
            this.#prepareTexturedModel(gl, model);
            let batch = entities.get(model);
            for (let entity of batch) {
                this.#prepareInstance(gl, ms, entity);
                gl.drawElements(gl.GL_TRIANGES, model.rawModel.vertexCount,
                        gl.GL_UNSIGNED_INT, 0);
            }
        }
        this.#unbindTexturedModel();
    }

    /**
     * @param {any} gl 
     * @param {TexturedModel} model 
     */
    #prepareTexturedModel(gl, model) {
        let rawModel = model.rawModel;
        gl.bindVertexArray(rawModel.vaoID);
        gl.enableVertexAttribArray(0);
        gl.enableVertexAttribArray(1);
        gl.enableVertexAttribArray(2);
        let texture = model.texture;
        this.#shader.loadShineVariables(gl, texture.shineDamper, texture.reflectivity);
        gl.activeTexture(gl.GL_TEXTURE0);
        gl.bindTexture(gl.GL_TEXTURE_2D, model.texture.textureID);
    }

    /**
     * @param {any} gl 
     */
    #unbindTexturedModel(gl) {
        gl.disableVertexAttribArray(0);
        gl.disableVertexAttribArray(1);
        gl.disableVertexAttribArray(2);
        gl.bindVertexArray(null);
    }

    /**
     * @param {any} gl 
     * @param {MatrixStack} ms 
     * @param {Entity} entity 
     */
    #prepareInstance(gl, ms, entity) {
        let transformationMatrix = entity.getTransformationMatrix(ms);
        this.#shader.loadTransformationMatrix(gl, transformationMatrix);
    }
}