const addon = require("./build/Release/cppInterface")

console.log("wesh");
console.log(addon.init("COM5"));
console.log(addon.getAngle());
console.log(addon.setForce(6.21));
console.log(addon.close());
console.log("fin");