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
    const { id_trees, totalIrrigation } = req.body;

    if (!id_trees || !totalIrrigation) {
        return res.status(400).json({ error: "Missing required parameters" });
    }

    console.log(`Received data - ID: ${id_trees}, totalIrrigation: ${totalIrrigation}`);

    const checkSql = `SELECT id_plants FROM trees WHERE id_plants = ?`;

    db_pool.query(checkSql, [id_trees], (err, results) => {
        if (err) {
            console.error("Error checking trees table:", err);
            return res.status(500).json({ error: "Database error" });
        }

        if (results.length === 0) {
            return res.status(400).json({ error: "id_trees does not exist in trees table" });
        }

        const sql = `INSERT INTO datasensors (id_trees, totalirrigation, date) VALUES (?, ?, NOW())`;

        db_pool.query(sql, [id_trees, totalIrrigation], (err, result) => {
            if (err) {
                console.error("Error inserting data into database:", err);
                return res.status(500).json({ error: "Database error" });
            }
            console.log("Data inserted successfully:", result);
            res.json({ message: "Data received and stored successfully" });
        });
    });
});






module.exports = router;

// 1. tempMode
// 2. moistureMode
// 3. shabbatMode
// 4. menualMode

