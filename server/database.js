// https://www.npmjs.com/package/mysql2
const mysql = require('mysql2');

//require("./gen_params");
let HOST     =require(".env").HOST     ;
let USER     =require(".env").USER     ;
let PASSWORD =require(".env").PASSWORD ;
let Database =require(".env").DATABASE ;
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
    maxIdle: 10, // max idle connections, the default value is the same as `connectionLimit`
    idleTimeout: 60000, // idle connections timeout, in milliseconds, the default value 60000
    queueLimit: 0,
    enableKeepAlive: true,
    keepAliveInitialDelay: 0
});


module.exports = {
    pool:pool
};