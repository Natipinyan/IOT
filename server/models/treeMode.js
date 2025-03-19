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

    async updateTreeById(name, id) {
        try {
            const [rows] = await this.DB.execute('SELECT id_plants FROM threes WHERE id = ?', [id]);

            if (rows.length === 0) {
                throw new Error('Tree with the given ID not found');
            }

            const id_plants = rows[0].id_plants;

            const [result] = await this.DB.execute('UPDATE plants SET name = ? WHERE id = ?', [name, id_plants]);

            if (result.affectedRows === 0) {
                throw new Error('Failed to update plant name');
            }

            console.log('Plant name updated successfully');
            return { message: 'Plant name updated successfully' };
        } catch (error) {
            console.error(error);
            throw new Error(error.message);
        }
    }


    async deleteTreeById(id) {
        try {

            const [result] = await this.DB.execute('DELETE FROM threes WHERE id = ?', [id]);

            if (result.affectedRows === 0) {
                throw new Error("No tree found with the given ID");
            }

            console.log("Tree deleted successfully");
            return { message: "Tree deleted successfully" };
        } catch (error) {
            console.error("Error deleting tree:", error);
            throw new Error(error.message);
        }
    }



}

module.exports = Tree;
