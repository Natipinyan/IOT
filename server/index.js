const express = require('express');
const morgan = require('morgan');
const cors = require('cors');

const dotenv = require('dotenv');

const app = express();
const HTTP_PORT = 3000;

const db_M = require('./database');
global.db_pool = db_M.pool;


dotenv.config();

app.use(express.json());
app.use(cors());
app.use(morgan('dev'));

app.listen(HTTP_PORT, () => {
    console.log(`The server is running on port: ${HTTP_PORT} \nlink: http://localhost:${HTTP_PORT}`);
});


const esp = require('./routers/esp');
app.use('/esp', esp);


const tree = require('./routers/treeRout');
app.use('/tree', tree);


