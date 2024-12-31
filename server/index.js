const express = require('express');
const app = express();
const morgan = require('morgan');
const path = require("path");
app.set("view engine","ejs");
app.use(express.static(path.join(__dirname)));
let db_M = require('./database');
global.db_pool = db_M.pool;


const port = 6060;
app.use(express.json());
app.listen(port, () => {
    console.log(`Now listening on port http://localhost:${port}`);
    console.log(`Now listening on port http://localhost:${port}/esp`);

});

const espRouter = require('./routers/esp');
app.use('/esp',espRouter);


processDevices();
function processDevices() {
    return new Promise((resolve, reject) => {
        const sql = `SELECT * FROM plants`;
        db_pool.query(sql, (err, results) => {
            if (err) {
                console.error("Error fetching data from arduino:", err);
                reject(err);
            } else {
                console.log("Fetched arduino data:");
                resolve(results);
                console.log(results);
            }
        });
    });
}