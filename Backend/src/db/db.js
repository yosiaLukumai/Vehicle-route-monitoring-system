const mongoose = require("mongoose")



async function checkConnection() {
    const connection = await mongoose.connect('mongodb://localhost/routeManager');
    if (connection) {
        console.log("Connection succeeded")
    }
    else {
        console.log('connection failed');
    }
}




module.exports = {
    checkConnection: checkConnection
};