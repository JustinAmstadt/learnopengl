class Camera {
    position = vec3(0.0, 0.0, 5.0);
    rotation = vec3(0.0, 0.0, 0.0);

    constructor() {
        document.addEventListener('keydown', function(event) {
            switch (event.key) {
                case 'w':
                case 'W':
                    move(vec3(0.0, 0.0, -0.2));
                    break;
                case 'a':
                case 'A':
                    move(vec3(-0.2, 0.0, 0.0));
                    break;
                case 's':
                case 'S':
                    move(vec3(0.0, 0.0, 0.2));
                    break;
                case 'd':
                case 'D':
                    move(vec3(0.2, 0.0, 0.0));
                    break;
                case 'Shift':
                    move(vec3(0.0, -0.2, 0.0));
                    break;
                case ' ':
                    move(vec3(0.0, 0.2, 0.0));
                    break;
            }
        });
    }

    /**
     * @param {vec3} direction 
     */
    move(direction) {
        position = add(this.position, direction);
    }
}