class StaticShader extends ShaderProgram {
    #location_transformationMatrix;
    #location_projectionMatrix;
    #location_viewMatrix;
    #location_lightPosition;
    #location_lightColour;
    #location_shineDamper;
    #location_reflectivity;

    constructor(gl, vertexShaderSrc, fragmentShaderSrc) {
        super(gl, vertexShaderSrc, fragmentShaderSrc);
    }

    bindAttributes() {
        super.bindAttribute(0, "position");
		super.bindAttribute(1, "textureCoordinates");
		super.bindAttribute(2, "normal");
    }

    getAllUniformLocations() {
        this.#location_transformationMatrix = super.getUniformLocation("transformationMatrix");
		this.#location_projectionMatrix = super.getUniformLocation("projectionMatrix");
		this.#location_viewMatrix = super.getUniformLocation("viewMatrix");
		this.#location_lightPosition = super.getUniformLocation("lightPosition");
		this.#location_lightColour = super.getUniformLocation("lightColour");
		this.#location_shineDamper = super.getUniformLocation("shineDamper");
		this.#location_reflectivity = super.getUniformLocation("reflectivity");
    }

    /**
     * @param {number} damper 
     * @param {number} reflectivity 
     */
    loadShineVariables(gl, damper, reflectivity){
		super.loadFloat(gl, this.#location_shineDamper, damper);
		super.loadFloat(gl, this.#location_reflectivity, reflectivity);
	}
	
    /**
     * @param {mat4} matrix 
     */
	loadTransformationMatrix(gl, matrix){
		super.loadMatrix(gl, this.#location_transformationMatrix, matrix);
	}
	
    /*
	loadLight(Light light){
		super.loadVector(this.#location_lightPosition, light.getPosition());
		super.loadVector(this.#location_lightColour, light.getColour());
	}*/
	
	loadViewMatrix(gl, camera){
		const viewMatrix = lookAt(camera.position, vec3(0.0, 0.0, -1.0), vec3(0.0, 1.0, 0.0));
		super.loadMatrix(gl, this.#location_viewMatrix, viewMatrix);
	}
	
	loadProjectionMatrix(gl, projection){
		super.loadMatrix(gl, this.#location_projectionMatrix, projection);
	}
}