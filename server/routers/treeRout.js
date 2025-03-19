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


router.delete("/Delete/:row_id",(req, res) => {
    try {
        let id = req.params.row_id;
        const trees =  tree.deleteTreeById(id);

        res.status(200).json({ message: "Trees deleting successfully" });
    } catch (error) {
        console.log(error);
        res.status(500).json({ message: "Error deleting tree", error: error.message });
    }
});


module.exports = router;