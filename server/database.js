const mysql = require('mysql2');
require('dotenv').config();

let HOST = process.env.HOST;
let USER  = process.env.USER;
let PASSWORD = process.env.PASSWORD;
let Database = process.env.DATABASE;

console.log("database.HOST	=",HOST	);
console.log("database.USER	=",USER	);
console.log("database.PASSWORD=",PASSWORD);
console.log("database.Database=",Database);



const pool = mysql.createPool({
    host:		HOST		,
    user:		USER		,
    password:	PASSWORD	,
    database:	Database	,
    waitForConnections: true,
    connectionLimit: 10,
    maxIdle: 10,
    idleTimeout: 60000,
    queueLimit: 0,
    enableKeepAlive: true,
    keepAliveInitialDelay: 0
});


module.exports = {
    pool:pool
};