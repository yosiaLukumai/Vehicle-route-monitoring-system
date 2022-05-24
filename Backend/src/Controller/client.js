// const dataModel = require('../Models/dataSent')
const dataModel = require("../Models/RouteManager")

const RenderHomePage = async (req, res ) =>
{
    try{
        const data = await dataModel.findOne().sort({ createdAt: -1 })
        // console.log(data)
        return res.json(data)
        
    }
    catch(err)
    {
        console.log(err.message)
        return res.send(err.message)
    }
}

module.exports = {
    RenderHomePage
}