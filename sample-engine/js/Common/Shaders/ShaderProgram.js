class ShaderProgram {
    #programID;

    constructor(gl, vertexShaderSrc, fragmentShaderSrc) {
        if (new.target === ShaderProgram) {
            throw new Error("Cannot make ShaderProgram directly. It is an abstract class.");
        }
        this.compileAndLinkShaders(gl, vertexShaderSrc, fragmentShaderSrc);
        this.getAllUniformLocations(gl);
    }

    getAllUniformLocations(gl) {
        throw new Error("getAllUniformLocations(gl) is an abstract method in ShaderProgram.");
    }

    bindAttributes(gl) {
        throw new Error("bindAttributes(gl) is an abstract method in ShaderProgram.");
    }

    compileAndLinkShaders( gl, vertexShaderSrc, fragmentShaderSrc )
    {
        // Begin by determining which version the OpenGL Shading Language (GLSL)
        //   is supported by the version of WebGL.
        //
        //     WebGL 1.0 supports "GLSL ES 1.0", while
        //     WebGL 2.0 supports "GLSL ES 3.0"
        //
        //  which requires starting the shader with a "#version" line.
        //
        const version = gl.getParameter( gl.SHADING_LANGUAGE_VERSION )
        const es300 = /GLSL ES 3.0/.test( version );

        let vertexShaderId = null;
        let fragmentShaderId = null;

        // Create a local function to create and compile the shader's
        //   source.  The function also inserts the required #version
        //   string if necessary.
        const CompileShader = function( type, src ) {

            // Validate the appropriate shader type, and set up some
            //   diagnostic information.
            let typeStr = undefined;
            let id = undefined;

            switch( type ) {
                case gl.VERTEX_SHADER:
                    typeStr = "Vertex";
                    id = vertexShaderId;
                    break;

                case gl.FRAGMENT_SHADER:
                    typeStr = "Fragment";
                    id = fragmentShaderId;
                    break;

                default:
                    alert( "Invalid shader type passed to CompileShader()" );
                    return -1;
                }

            // Determine if there's a valid GLSL ES 3.0 version string
            //   already present in the shader, and if not, insert a
            //   version string at the start of the shader.
            const versionRegExp = /\s*#version\s+300\s+es/;

            if ( es300 && !versionRegExp.test(src) ) {
                src = "#version 300 es\n" + src;
            }

            // Create a WebGL shader object, load its source, and
            //   compile it.  If the compilation fails, retrieve and
            //   display the error log and shader source, and indicate
            //   the operation failed by passing back a "-1", which is
            //   an invalid shader id (they must be greater than zero)
            const shader = gl.createShader( type );
            gl.shaderSource( shader, src );
            gl.compileShader( shader );
            if ( !gl.getShaderParameter(shader, gl.COMPILE_STATUS) ) {

                const msg = typeStr + " shader '" + id + "' failed to compile." +
                    "  The error log is:\n\n" + gl.getShaderInfoLog( shader ) +
                    "\n-----------------------------------------\n\n" + src;
                alert( msg );
                return -1;
            }

            this.#programID = shader;
        };

        // Attempt to retrieve the vertex shader's source, and compile it.  We
        //   first check to see if the value passed exists in the page's document.
        //   If so, we retrieve the text from that element.  If not, then we see
        //   if we were passed a completed, valid shader string (by testing to
        //   see if it contain "main")
        const vertElem = document.getElementById( vertexShaderSrc );
        if ( vertElem ) {
            vertexShaderId = vertexShaderSrc;
            vertexShaderSrc = vertElem.textContent;
        }
        else if ( typeof vertexShaderSrc === 'string'
            && /main/.test(vertexShaderSrc) ) {
                vertexShaderId = 'inline';
        }
        else {
            alert( "Unable to load vertex shader '" + vertexShaderSrc + "'" );
            return -1;
        }

        const vertShdr = CompileShader( gl.VERTEX_SHADER, vertexShaderSrc );
        if ( vertShdr < 0 ) { return -1; }
        
        // Do the identical operation for the fragment shader, verifying that
        //   the fragment shader also contains an appropriate precision
        //   specification
        const fragElem = document.getElementById( fragmentShaderSrc );
        if ( fragElem ) {
            fragmentShaderId = fragmentShaderSrc;
            fragmentShaderSrc = fragElem.textContent;
        }
        else if ( typeof fragmentShaderSrc === 'string' 
            && /main/.test(fragmentShaderSrc) ) {
                fragmentShaderId = 'inline';
        }
        else {
            alert( "Unable to load fragment shader '" + fragmentShaderSrc + "'" );
            return -1;
        }

        // This test is fairly rudimentary as it only checks on the "precision"
        //   keyword being present in the shader.  
        let src = fragmentShaderSrc;
        if ( !/precision/.test(src) ) { 
            src = "precision highp float; " + src;
        }

        const fragShdr = CompileShader( gl.FRAGMENT_SHADER, src );
        if ( fragShdr < 0 ) { return -1; }

        // Finally, compose the shader program pipeline by attaching shaders
        //   and linking the program.  If the link succeeds, we return the
        //   shader program, otherwise, we report an error and return a "-1"
        //   (an invalid shader program value).
        const program = gl.createProgram();
        gl.attachShader( program, vertShdr );
        gl.attachShader( program, fragShdr );

        // Bind attributes before linking the program
        this.bindAttributes(gl);

        gl.linkProgram( program );

        if ( !gl.getProgramParameter(program, gl.LINK_STATUS) ) {
            const msg = "Shader program failed to link.  The error log is:\n\n"
                + gl.getProgramInfoLog( program );
            alert( msg );
            return -1;
        }

        this.#programID = program;
    }

    /**
     * @param {any} gl 
     * @param {string} uniformName 
     * @returns {number}
     */
    getUniformLocation(gl, uniformName) {
        return gl.getUniformLocation(this.#programID, uniformName);
    }

    /**
     * @param {any} gl 
     */
    start(gl) {
        gl.useProgram(this.#programID);
    }

    /**
     * @param {any} gl 
     */
    stop(gl) {
        gl.useProgram(null);
    }

    /**
     * @param {any} gl 
     * @param {number} attribute 
     * @param {string} name 
     */
    bindAttribute(gl, attribute, name) {
        gl.bindAttribLocation(this.#programID, attribute, name);
    }

    /**
     * @param {any} gl 
     * @param {number} location 
     * @param {number} value 
     */
    loadFloat(gl, location, value) {
        gl.uniform1f(location, value);
    }

    /**
     * @param {any} gl 
     * @param {number} location 
     * @param {vec3} vector 
     */
    loadVector(gl, location, vector) {
        gl.uniform3f(location, vector.x, vector.y, vector.z);
    }

    /**
     * @param {any} gl 
     * @param {number} location 
     * @param {boolean} value 
     */
    loadBoolean(gl, location, value) {
        let toLoad = value ? 1.0 : 0.0;
        gl.uniform1f(location, toLoad);
    }

    /**
     * @param {any} gl 
     * @param {number} location 
     * @param {mat4} matrix 
     */
    loadMatrix(gl, location, matrix) {
        gl.uniformMatrix4fv(location, false, flatten(matrix)); 
    }

}