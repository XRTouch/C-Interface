const addon = require("./build/Release/cppInterface")

console.log("wesh");
console.log(addon.getAngle());
console.log(addon.setForce(6.21));
console.log("fin");