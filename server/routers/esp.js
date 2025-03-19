const express = require('express');
const router = express.Router();
const fs = require('fs');

router.get('/', (req, res) => {
    const { temp,light, moisture } = req.query;
})
router.get('/state', (req, res) => {
    let data = JSON.parse(fs.readFileSync("state.json", "utf8"));
    let currentDate = new Date();
    data = {
        state: data.state,
        date: currentDate.toLocaleTimeString('he-IL', { hour: '2-digit', minute: '2-digit' })
    }
    res.json(data);
})

router.get('/dataMode', (req,res) =>{
    const { state } = req.query;
    let data = JSON.parse(fs.readFileSync("state.json", "utf8"));
    res.json(data[state]);
})

router.post("/sendData", (req, res) => {
    const { id, light, moisture, temp } = req.body;

    if (!id || !light || !moisture || !temp) {
        return res.status(400).json({ error: "Missing required parameters" });
    }

    console.log(`Received data - ID: ${id}, Light: ${light}, Moisture: ${moisture}, Temp: ${temp}`);

    // כאן אפשר לשמור את הנתונים בבסיס הנתונים

    res.json({ message: "Data received successfully" });
});






module.exports = router;

// 1. tempMode
// 2. moistureMode
// 3. shabbatMode
// 4. menualMode

