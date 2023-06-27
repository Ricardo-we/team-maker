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

// Función para generar equipos de trabajo
std::vector<std::vector<Student>> generateTeams(std::vector<Student> originalStudents, std::vector<std::vector<Student>> originalGroups)
{
    std::vector<Student> students = originalStudents;
    std::vector<Student> pendingStudents = {};
    std::vector<std::vector<Student>> groups = originalGroups;
    std::vector<int> removeFromStudentsListIndexes = {};

    if (students.size() <= MINIMUM_STUDENTS && students.size() > 2)
    {
        groups.push_back(students);
        return groups;
    }
    else if (students.size() == 1)
    {
        if (groups.empty())
            groups.push_back(std::vector<Student>{});
        int lastIndex = lastIndexOf(groups);
        groups[lastIndex].push_back(students[0]);
        return groups;
    }

    Student student = students[0];
    // students.pop_back();
    students.erase(students.begin());

    // if (students.empty())
    //     return groups;

    for (int i = 0; i < students.size(); i++)
    {
        if (compareStudents(student, students[i]))
        {
            int lastIndex = lastIndexOf(groups);
            if (groups.empty())
                groups.push_back(std::vector<Student>{});
            if (groups[lastIndex].empty())
                groups[lastIndex].push_back(student);
            if (groups.at(lastIndex).size() >= maxGroupSize)
            {
                groups.push_back(std::vector<Student>{});
                break;
                // lastIndex = lastIndexOf(groups);
            }

            removeFromStudentsListIndexes.push_back(i);
            groups[lastIndex].push_back(students[i]);
        }
    }

    for (int i = 0; i < students.size(); i++)
    {
        bool hasEqual = false;
        for (int j = 0; j < removeFromStudentsListIndexes.size(); j++)
        {
            hasEqual = i == removeFromStudentsListIndexes[j];
            if (hasEqual)
                break;
        }

        if (!hasEqual)
            pendingStudents.push_back(students[i]);
    }

    if (pendingStudents.size() > 0)
    {
        return generateTeams(pendingStudents, groups);
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
    std::vector<Student> studentsSample = {
        {"John", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {"Sarah", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
        {"Michael", "tennis", "Hip Hop", "Merengue", "Drums", "Club Z", "Reading"},
        {"Emily", "natación", "Jazz", "Salsa", "No instrument", "Club D", "Cinema"},
        {"David", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {"Jessica", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
        {"Daniel", "tennis", "Hip Hop", "Merengue", "Drums", "Club Z", "Reading"},
        {"Sophia", "natación", "Jazz", "Salsa", "No instrument", "Club D", "Cinema"},
        {"Matthew", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {"Olivia", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
        {"Jacob", "tennis", "Hip Hop", "Merengue", "Drums", "Club Z", "Reading"},
        {"Isabella", "natación", "Jazz", "Salsa", "No instrument", "Club D", "Cinema"},
        {"William", "futbol", "Rock", "Salsa", "Guitar", "Club X", "Video Games"},
        {"Ava", "basquetball", "Pop", "Bachata", "Piano", "Club Y", "Traveling"},
    };

    // while (true)
    // {
    //     Student student = getStudent();
    //     studentsSample.push_back(student);
    //     std::string wantToAddMoreStudents = getStringInput("Desea añadir otro estudiante? (sí o no)");
    //     if (toLowerCase(wantToAddMoreStudents) == "no")
    //         break;
    // }

    // Generar equipos de trabajo
    std::vector<std::vector<Student>> teams = generateTeams(studentsSample, std::vector<std::vector<Student>>{});

    // Mostrar los equipos generados
    for (int i = 0; i < teams.size(); i++)
    {
        std::string totalElementsInTeam = "(" + std::to_string(teams[i].size()) + ")";
        std::cout << "Equipo " << i + 1 << totalElementsInTeam << ":" << std::endl;

        for (const auto &persona : teams[i])
        {
            std::cout << "Nombre: " << persona.name << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}