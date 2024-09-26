class Entity {
    model;
    position;
    rotationOrientation;
    rotationAngle;
    scale;

    /**
     * @param {TexturedModel} model 
     * @param {vec3} position 
     * @param {vec3} rotationOrientation 
     * @param {number} rotationAngle
     * @param {number} scale 
     */
    constructor(model, position, rotationOrientation, rotationAngle, scale) {
        this.model = model;
        this.position = position;
        this.rotationOrientation = rotationOrientation;
        this.rotationAngle = rotationAngle;
        this.scale = scale;
    }

    /**
     * @param {number} dx 
     * @param {number} dy 
     * @param {number} dz 
     */
    incrementPosition(dx, dy, dz) {
        this.position = add(this.position, vec3(dx, dy, dz));
    }

    /**
     * @param {number} dx 
     * @param {number} dy 
     * @param {number} dz 
     */
    incrementRotationOrientation(dx, dy, dz) {
        this.rotationOrientation = add(this.rotationOrientation, vec3(dx, dy, dz));
    }

    /**
     * @param {number} angle 
     */
    incrementRotationAngle(angle) {
        this.rotationAngle += angle;
    }

    /**
     * @param {MatrixStack} ms
     * @return {mat4}
     */
    getTransformationMatrix(ms) {
        ms.push();
        ms.translate(position);
        ms.rotate(this.rotationAngle, this.rotationOrientation);
        ms.scale(this.scale);
        let transformationMatrix = ms.current();
        ms.pop();

        return transformationMatrix;
    }
}