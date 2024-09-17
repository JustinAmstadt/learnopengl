// p1: vec2
// p2: vec2
// return: vec2
function distance(p1, p2) {
    return Math.sqrt(Math.pow(p2[0] - p1[0], 2) + Math.pow(p2[1] - p1[1], 2));
}

// p: vec2
// return: vec2
function magnitude(p) {
    return Math.sqrt(p[0] * p[0] + p[1] * p[1]);
}