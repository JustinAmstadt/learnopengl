import * as THREE from 'three';

export const water = (scene: THREE.Scene) => {
    const width = 5;
    const height = 5;
    const geometry = new THREE.PlaneGeometry(width, height);
    geometry.rotateX(-Math.PI / 2);

    const material = new THREE.MeshBasicMaterial({ color: 0x0000ff, side: THREE.DoubleSide }); // Set side to DoubleSide to make it visible from both sides

    const quad = new THREE.Mesh(geometry, material);

    scene.add(quad);
}