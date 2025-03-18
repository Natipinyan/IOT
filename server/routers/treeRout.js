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




module.exports = router;