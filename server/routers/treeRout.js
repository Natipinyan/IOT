const express = require('express');
const router = express.Router();
const Tree  = require('../models/treeMode');

const tree = new Tree(db_pool);

router.post("/add", (req, res) => {
    try {
        const { name } = req.body;
        tree.createTree(name);
        res.status(201).json({message: "ctreate tree success"});

    } catch (error) {
        console.log(error);
    }

});

router.get("/get", async (req, res) => {
    try {
        const trees = await tree.readAllTree();

        res.status(200).json({ message: "Trees fetched successfully", data: trees });
    } catch (error) {
        console.log(error);
        res.status(500).json({ message: "Error fetching trees", error: error.message });
    }
});

router.delete("/Delete/:row_id", async (req, res) => {
    const { row_id } = req.params;  // חילוץ ה-ID מתוך ה-params

    try {
        const result = await tree.deleteTreeById(row_id);
        res.status(200).json(result);
    } catch (error) {
        console.error(error);
        res.status(500).json({
            message: "Error deleting tree",
            error: error.message
        });
    }
});


router.post("/Update", async (req, res) => {
    let name = req.body.name;
    let id = req.body.id;

    try {
        const result = await tree.updateTreeById(name, id);
        res.status(200).json(result);
    } catch (error) {
        console.log(error);
        res.status(500).json({ message: "Error updating tree", error: error.message });
    }
});

module.exports = router;