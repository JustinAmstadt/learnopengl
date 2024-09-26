import * as THREE from 'three';
import { makeTerrain } from './terrain';
import { water } from './water';

// @ts-ignore
import grassTexture from '../textures/texture-grass-field.jpg'; // Import the texture file



function init() {

    const scene = new THREE.Scene();

    const ambientLight = new THREE.AmbientLight(0xffffff, 0.5); // Soft white light
    scene.add(ambientLight);

    const directionalLight = new THREE.DirectionalLight(0xffffff, 1); // White light
    directionalLight.position.set(5, 10, 7.5); // Set light position
    scene.add(directionalLight);

    const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    keyboardInput(camera);

    const renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);
    renderer.setClearColor(0x87CEEB);

    camera.position.z = 5;

    makeTerrain(scene)
    water(scene);

    function animate() {
        requestAnimationFrame(animate);

        // terrain.rotateX(0.01);

        renderer.render(scene, camera);
    }

    animate();
}

const keyboardInput = (camera: THREE.PerspectiveCamera) => {
    document.addEventListener('keydown', (event) => {
        switch(event.key) {
            case 'ArrowUp':
                camera.position.y += 0.1; // Move up
                break;
            case 'ArrowDown':
                camera.position.y -= 0.1; // Move down
                break;
            case 'ArrowLeft':
                camera.position.x -= 0.1; // Move left
                break;
            case 'ArrowRight':
                camera.position.x += 0.1; // Move right
                break;
            case 'w': // Move forward
                camera.position.z -= 0.1;
                break;
            case 's': // Move backward
                camera.position.z += 0.1;
                break;
        }
    });
}

window.onload = init;