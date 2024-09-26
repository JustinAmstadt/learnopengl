class ModelTexture {
    textureID;
    shineDamper;
    reflectivity;

    /**
     * @param {number} texture as int
     */
    constructor(texture) {
        this.textureID = texture;
        this.shineDamper = 1;
        this.reflectivity = 0;
    }
}