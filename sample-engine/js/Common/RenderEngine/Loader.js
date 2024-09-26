class Loader {
    #vaos;
    #vbos;
    #textures;

    /**
     * @param {any} gl 
     * @param {number[]} positions 
     * @param {number[]} textureCoords 
     * @param {number[]} normals 
     * @param {number[]} indices 
     * @returns {RawModel}
     */
    loadToVAO(gl, positions, textureCoords, normals, indices) {
        const vaoID = this.#createVAO(gl);
        this.#bindIndicesBuffer(gl, indices);
        this.#storeDataInAttributeList(gl, 0, 3, positions);
        this.#storeDataInAttributeList(gl, 1, 2, textureCoords);
        this.#storeDataInAttributeList(gl, 2, 3, normals);
        this.#unbindVAO(gl);
        return new RawModel(vaoID, indices.length);
    }

    /**
     * @param {any} gl 
     * @param {string} filePath 
     * @returns {number}
     */
    loadTexture(gl, filePath) {
        const texture = gl.createTexture();
        gl.bindTexture(gl.TEXTURE_2D, texture);

        // Set up a temporary 1x1 pixel texture while waiting for the image to load
        gl.texImage2D(
            gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0,
            gl.RGBA, gl.UNSIGNED_BYTE, new Uint8Array([255, 0, 0, 255])
        );

        const image = new Image();
        image.src = filePath;

        image.onload = function() {
            // Bind the texture again (in case other textures were bound in between)
            gl.bindTexture(gl.TEXTURE_2D, texture);
        
            // Upload the image data to the GPU
            gl.texImage2D(
                gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,
                gl.UNSIGNED_BYTE, image
            );
        
            // Set texture wrapping
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
        
            // Set texture filtering
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        
            gl.generateMipmap(gl.TEXTURE_2D);
        };
        
        gl.bindTexture(gl.TEXTURE_2D, null);
        this.#textures.push(texture);

        return texture;
    }

    /**
     * @param {any} gl 
     * @param {number} attributeNumber 
     * @param {number} coordinateSize 
     * @param {number[]} data of floats
     */
    #storeDataInAttributeList(gl, attributeNumber, coordinateSize, data) {
        let vboID = gl.createBuffer();
        this.#vbos.push(vboID);
        let convertedData = this.#convertArrayFloat32(data);
        gl.bufferData(gl.ARRAY_BUFFER, convertedData, gl.STATIC_DRAW);
        gl.vertexAttribPointer(attributeNumber, coordinateSize, gl.FLOAT, false, 0, 0);
        gl.bindBuffer(gl.ARRAY_BUFFER, null);
    }

    /**
     * @param {any} gl 
     * @param {number[]} indices 
     */
    #bindIndicesBuffer(gl, indices) {
        let vboID = gl.createBuffer();
        this.#vbos.push(vboID);
        let convertedData = this.#convertArrayUint16(indices);
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, vboID);
        gl.bufferData(gl.ARRAY_BUFFER, convertedData, gl.STATIC_DRAW);
    }

    /**
     * @param {any} gl 
     * @return {number}
     */
    #createVAO(gl) {
        let vaoID = gl.createVertexArray();
        this.#vaos.push(vaoID);
        gl.bindVertexArray(vaoID);
        return vaoID;
    }

    /**
     * @param {any} gl 
     */
    #unbindVAO(gl) {
        gl.bindVertexArray(null);
    }

    /**
     * @param {number[]} data of floats
     * @returns {Float32Array}
     */
    #convertArrayFloat32(data) {
        return new Float32Array(data);
    }

    /**
     * 
     * @param {number[]} data of ints
     * @returns {Uint16Array}
     */
    #convertArrayUint16(data) {
        return new Uint16Array(data);
    }
}