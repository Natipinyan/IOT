const mysql = require('mysql2/promise');

let HOST ="localhost";
let USER ="root";
let PASSWORD ="";
let DATABASE ="iot";

console.log("database.HOST	=",HOST	);
console.log("database.USER	=",USER	);
console.log("database.PASSWORD=",PASSWORD);
console.log("database.DATABASE=",DATABASE);



const pool = mysql.createPool({
    host:		HOST		,
    user:		USER		,
    password:	PASSWORD	,
    database:	DATABASE	,
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