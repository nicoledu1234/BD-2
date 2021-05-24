
select c.nom_curso, count(m.id_curso) from curso c left join matricula m on m.id_curso = c.id_curso group by c.nom_curso;
select a.nom_alu, c.nom_curso, (CASE WHEN a.id_alu = m.id_alu and c.id_curso = m.id_curso then 'Yes' else 'NO' END)
from alumno a 
    cross join curso c 
    left join matricula m on a.id_alu = m.id_alu and c.id_curso = m.id_curso;