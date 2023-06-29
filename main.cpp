#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <cctype>
#include <cstring>
#include <Windows.h>

const int maxGroupSize = 7;
const int MINIMUM_STUDENTS = 5;

struct Student
{
    int id;
    std::string name;
    std::string sport;
    std::string music;
    std::string dancing;
    std::string instrument;
    std::string club;
    std::string hobbie;
};

std::string toLowerCase(std::string word)
{
    std::string result = "";
    for (int i = 0; i < word.length(); i++)
        result += tolower(word[i]);
    return result;
}

std::string getStringInput(std::string label)
{
    std::cout << label << std::endl;
    std::string name;
    std::cin >> name;
    return name;
}

template <typename T>
int lastIndexOf(std::vector<T> arr)
{
    int lastIndex = 0;
    if (arr.size() > 0)
        lastIndex = arr.size() - 1;
    return lastIndex;
}

bool compareStudents(Student student1, Student student2)
{
    int equalQualities = 0;
    if (student1.club == student2.club)
        equalQualities++;
    if (student1.dancing == student2.dancing)
        equalQualities++;
    if (student1.hobbie == student2.hobbie)
        equalQualities++;
    if (student1.instrument == student2.instrument)
        equalQualities++;
    if (student1.sport == student2.sport)
        equalQualities++;

    return equalQualities >= 2;
}

std::vector<std::vector<Student>> generateTeams(std::vector<Student> students, int minGroupSize, int maxGroupSize) {
    std::vector<std::vector<Student>> groups;

    // Reordenar aleatoriamente los estudiantes
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(students.begin(), students.end(), generator);

    while (!students.empty()) {
        std::vector<Student> currentGroup;
        currentGroup.push_back(students.back()); // Agregar el último estudiante a un nuevo grupo
        students.pop_back(); // Eliminar el último estudiante del vector principal

        for (int i = students.size() - 1; i >= 0; i--) {
            if (compareStudents(currentGroup.front(), students[i])) {
                currentGroup.push_back(students[i]); // Agregar al estudiante al grupo
                students.erase(students.begin() + i); // Eliminar al estudiante del vector principal
                
                if (currentGroup.size() == maxGroupSize) // Si el grupo alcanza el tamaño máximo, terminar de agregar estudiantes
                    break;
            }
        }

        groups.push_back(currentGroup); // Agregar el grupo completo a la lista de grupos
    }

    return groups;
}

Student getStudent()
{
    Student student = {};
    student.name = getStringInput("Introduce tu nombre: ");
    student.sport = getStringInput("¿Cuál es su deporte favorito? (futbol,basquet,voley,natacion,karate,otros): ");
    student.music = getStringInput("¿Qué música le gusta ? (salsa,rock,bachata,regaetton,merengue,technocumbia,folklorica,otros): ");
    student.dancing = getStringInput("¿Qué danza le gusta de preferencia? (salsa,rock,bachata,regaetton,merengue,technocumbia,folklorica,otros): ");
    student.instrument = getStringInput("¿Toca algún instrumento? (guitarra,bateria,piano,saxo,no toca, otros)");
    student.club = getStringInput("¿Cuál es su club favorito? (x,y,z,d,p)");
    student.hobbie = getStringInput("¿Cuál es su hobbie favorito? (cine,visitar museos,viajar,oratoria,videojuegos,conciertos,otros)");

    return student;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // Población de personas a escoger
    // TODO Dejar vacío si es necesario
    std::vector<Student> studentsSample = {
        {1, "John", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {2, "Sarah", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
        {3, "Michael", "tennis", "Hip Hop", "Merengue", "Drums", "Club Z", "Reading"},
        {4, "Emily", "natación", "Jazz", "Salsa", "No instrument", "Club D", "Cinema"},
        {5, "David", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {6, "Jessica", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
        {7, "Daniel", "tennis", "Hip Hop", "Merengue", "Drums", "Club Z", "Reading"},
        {8, "Sophia", "natación", "Jazz", "Salsa", "No instrument", "Club D", "Cinema"},
        {9, "Matthew", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {10, "Olivia", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
        {11, "Jacob", "tennis", "Hip Hop", "Merengue", "Drums", "Club Z", "Reading"},
        {12, "Isabella", "natación", "Jazz", "Salsa", "No instrument", "Club D", "Cinema"},
        {13, "William", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {14, "Ava", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
    };

    while (true)
    {
        Student student = getStudent();
        studentsSample.push_back(student);
        std::string wantToAddMoreStudents = getStringInput("Desea añadir otro estudiante? (sí o no)");
        if (toLowerCase(wantToAddMoreStudents) == "no")
            break;
    }

    // Generar equipos de trabajo
    // std::vector<std::vector<Student>> teams = generateTeams(studentsSample, std::vector<std::vector<Student>>{});
    std::vector<std::vector<Student>> teams = generateTeams(studentsSample,MINIMUM_STUDENTS, maxGroupSize);
    // Mostrar los equipos generados
    for (int i = 0; i < teams.size(); i++)
    {
        std::string totalElementsInTeam = "(" + std::to_string(teams[i].size()) + ")";
        std::cout << "Equipo " << i + 1 << totalElementsInTeam << ":" << std::endl;

        for (Student student : teams[i])
        {
            std::cout << "id: " << student.id << " Nombre: " << student.name << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}