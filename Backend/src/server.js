const express = require('express');
const cors = require('cors')
const port = 3400;
const db = require("./db/db");
db.checkConnection();

const app = express();
app.use(cors())

// let load the json

app.use(express.urlencoded({extended: true}))
app.use(express.json())

// loading the routes
const routesForData = require("./routes/postDataRoutes")
const clientRoutes = require('./routes/clientroutes')
routesForData.sendData(app)
clientRoutes.clientRoutes(app)



app.get("/", (req, res)=>
{
    res.send('okk')
})


app.listen(port, ()=>
{
    console.log(`app has been aired on port ${port}`)
})