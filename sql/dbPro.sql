CREATE TABLE IF NOT EXISTS `Sensors` (
                                         `id` int AUTO_INCREMENT NOT NULL UNIQUE,
                                         `name` varchar(255) NOT NULL,
                                         `isRunning` int NOT NULL,
                                         PRIMARY KEY (`id`)
    );

CREATE TABLE IF NOT EXISTS `Trees` (
                                       `id` int AUTO_INCREMENT NOT NULL UNIQUE,
                                       `id_plants` int NOT NULL,
                                       `max_temp` int NOT NULL,
                                       `max_soil_moisture` int NOT NULL,
                                       `date` date NOT NULL,
                                       PRIMARY KEY (`id`)
    );

CREATE TABLE IF NOT EXISTS `Plants` (
                                        `id` int AUTO_INCREMENT NOT NULL UNIQUE,
                                        `name` varchar(255) NOT NULL,
    PRIMARY KEY (`id`)
    );

CREATE TABLE IF NOT EXISTS `DataSensors` (
                                             `id` int AUTO_INCREMENT NOT NULL UNIQUE,
                                             `id_trees` int NOT NULL,
                                             `id_sensors` int NOT NULL,
                                             `avg` double NOT NULL,
                                             `date` date NOT NULL,
                                             PRIMARY KEY (`id`)
    );

ALTER TABLE `Trees` ADD CONSTRAINT `Trees_fk1` FOREIGN KEY (`id_plants`) REFERENCES `Plants`(`id`);

ALTER TABLE `DataSensors` ADD CONSTRAINT `DataSensors_fk1` FOREIGN KEY (`id_trees`) REFERENCES `Trees`(`id`);

ALTER TABLE `DataSensors` ADD CONSTRAINT `DataSensors_fk2` FOREIGN KEY (`id_sensors`) REFERENCES `Sensors`(`id`);