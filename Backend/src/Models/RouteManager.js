const mongoose = require("mongoose")
const routeManager = new mongoose.Schema({
    velocity:{
        type: String
    }, 
    long:{
        type: String
    },
    lati:
    {
        type: String
    },
    createdAt: 
    {
        type: Date,
        immutable: true,
        default: () =>Date.now()
    },
    updatedAt:
    {
        type: Date,
        default: () => Date.now()

    }
  });


  routeManager.pre('save', function(next){
    this.updatedAt = Date.now()
    next()
})


module.exports = mongoose.model("routeManager", routeManager);


