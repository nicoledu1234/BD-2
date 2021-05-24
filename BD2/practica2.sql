CREATE TABLE alumno(  
	id_alumno INT PRIMARY KEY,  
	nombre_alumno VARCHAR(30)
 );
CREATE TABLE curso(  
	id_curso INT PRIMARY KEY,  
	nombre_curso VARCHAR(30)  
);
CREATE TABLE matricula(  
	id_curso INT ,  
    id_alumno INT ,  
    semestre INT   
);
ALTER TABLE matricula  
	ADD CONSTRAINT matricula_fk1 FOREIGN KEY(id_alumno) 
REFERENCES alumno (id_alumno);

ALTER TABLE matricula  
	ADD CONSTRAINT matricula_fk2 FOREIGN KEY(id_curso) 
REFERENCES curso (id_curso);

INSERT INTO alumno ( id_alumno,nombre_alumno)  VALUES (1,'pepe');
INSERT INTO curso ( id_curso,nombre_curso)  VALUES (100,'mat');
INSERT INTO matricula (id_alumno, id_curso,semestre)  VALUES (1,100,4);

CREATE VIEW alumno_curso AS 
	SELECT alumno.id_alumno, alumno.nombre_alumno, curso.id_curso, curso.nombre_curso
FROM alumno 
	CROSS JOIN curso;
 
SELECT e.nombre_alumno 'NOMBRE' , e.nombre_curso 'CURSO',(case when e.id_alumno=m.id_alumno and
	e.id_curso=m.id_curso then 'Si' else 'No' END) 'Estado de Matricula'
FROM alumno_curso e
	LEFT JOIN matricula m 
		ON e.id_alumno=m.id_alumno and e.id_curso=m.id_curso;



