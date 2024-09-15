class Particle {
    velocity;
    position;
    circleScale;

    constructor(v) {
        this.velocity = v;
        this.position = vec2(0.0, 0.0);
        this.circleScale = 0.02;
    }

    update() {
        this.position = add(this.position, this.velocity);

        if (this.position[0] > 1.0 - this.circleScale || this.position[0] < -(1.0 - this.circleScale)) {
            this.velocity[0] = -this.velocity[0];
        }
        if (this.position[1] > 1.0 - this.circleScale || this.position[1] < -(1.0 - this.circleScale)) {
            this.velocity[1] = -this.velocity[1];
        }

        return mult(translate(this.position[0], this.position[1], 0.0), scalem(this.circleScale, this.circleScale, 1));
    }
}

function genParticles(number) {
    let particles = [];
    let max = 0.03;
    let min = 0.0001;

    for (i = 0; i < number; i++) {
        let vX = Math.random() * (max - min) + min;
        let vY = Math.random() * (max - min) + min;

        particles.push(new Particle(vec2(vX, vY)));
    }

    return particles;
}