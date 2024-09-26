import * as THREE from 'three';

function vertexShader() {
    return `
      out vec3 vUv; 
  
      void main() {
        vUv = position; 
  
        vec4 modelViewPosition = modelViewMatrix * vec4(position, 1.0);
        gl_Position = projectionMatrix * modelViewPosition; 
      }
    `
}

function fragmentShader() {
    return `
    uniform vec3 colorA; 
    uniform vec3 colorB; 
    in vec3 vUv;

    void main() {
        gl_FragColor = vec4(colorB, 1.0);
    }
`
}
export const makeTerrain = (scene: THREE.Scene) => {
    const width = 200;
    const height = 200;
    const segments = 100;
    const geometry = new THREE.PlaneGeometry(width, height, segments, segments);
    geometry.rotateX(-Math.PI / 2);

    const vertices = geometry.attributes.position.array;
    for (let i = 0; i < vertices.length; i += 3) {
        vertices[i + 1] = Math.random() * -5;
    }

    let uniforms = {
        colorB: {type: 'vec3', value: new THREE.Color(0, 1, 0)},
        colorA: {type: 'vec3', value: new THREE.Color(0, 0, 1)}
    }

    // Create the material and mesh
    const material = new THREE.ShaderMaterial({
        uniforms: uniforms,
        vertexShader: vertexShader(),
        fragmentShader: fragmentShader(),
        side: THREE.DoubleSide
    });
    const terrain = new THREE.Mesh(geometry, material);
    scene.add(terrain);
}