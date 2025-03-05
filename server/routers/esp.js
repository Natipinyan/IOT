const express = require("express");
const router = express.Router();



router.get("/", (req, res) => {
    const { temp, linght, moisture } = req.query;

    console.log("req.query");
});

module.exports = router;