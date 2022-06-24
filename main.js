const process = require("process");
const addon = require("./build/Release/cppInterface")

addon.init("COM3");
addon.setForce(50);

while (true) {
    val = addon.getMovement();
    val2 = addon.getAngle();
    console.log("val: "+val+" val2: "+val2);
}