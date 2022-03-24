const process = require("process");
const addon = require("./build/Release/cppInterface")

addon.init("COM3");
addon.setForce(50);

while (true) {
    val = addon.getMovement() + 20;
    for (let i = 0; i < 40-val; i++) {
        process.stdout.write(" ");
    }
    console.log("+");
}