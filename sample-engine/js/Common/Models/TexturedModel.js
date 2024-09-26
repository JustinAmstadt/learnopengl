class TexturedModel {
    rawModel;
    texture;

    /**
     * @param {RawModel} rawModel 
     * @param {ModelTexture} texture 
     */
    constructor(rawModel, texture) {
        this.rawModel = rawModel;
        this.texture = texture;
    }
}