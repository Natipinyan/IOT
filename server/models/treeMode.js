class Tree{
    constructor(db){
        this.DB = db;
    }

    async readAllTree() {
        try {
            const [sql, t] = await this.DB.execute(`SELECT * FROM threes`);

            return sql;
        } catch (error) {
            console.log("Error fetching trees:", error);
            throw error;
        }
    }

    async createTree(nameTree){
        try {
            console.log(nameTree);
            const date = new Date();
             const formattedDate = date.toISOString().split('T')[0];
             let [sql,t]= await this.DB.execute(`SELECT * FROM plants where name = ?`,[nameTree]);
             if(sql.length > 0){
                 await this.DB.execute(`INSERT INTO threes(id_plants, date) VALUE(?,?);`,[sql[0].id, formattedDate]);
             }else{
                 sql = await this.DB.execute(`INSERT INTO plants(name) VALUE(?);`,[nameTree]);
                 console.log(sql[0].insertId);
                 console.log(formattedDate);
                 let answer =  await this.DB.execute(`INSERT INTO threes(id_plants, date) VALUE(?,?);`,[sql[0].insertId, formattedDate]);
             }

        } catch (error) {
            console.log(error);
        }
    }

    async deleteTreeById(id) {

        const [sql, t] = await this.DB.execute(`DELETE FROM threes WHERE id='${id}'`);

        console.log(sql);
        db_pool.query(sql, function(err, rows, fields){
            if(err){
                res.status(500).json({message: err})
            }else{
                res.status(200).json({message: "OK"});
            }
        });
    }

    async deleteTreeById(id) {
        try {
            const sql = await this.DB.execute(`DELETE FROM threes WHERE id='${id}'`);
        } catch (error) {
            console.log("Error deleting tree:", error);
            throw error;
        }
    }



}

module.exports = Tree;
