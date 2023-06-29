import random

MAX_GROUP_SIZE = 7
MIN_GROUP_SIZE = 5
POPULATION_SIZE = random.randint(20, 30)

class Student:
    def __init__(self, id, name, sport, music, dancing, instrument, club, hobby, gender):
        self.id = id
        self.name = name
        self.sport = sport
        self.music = music
        self.dancing = dancing
        self.instrument = instrument
        self.club = club
        self.hobby = hobby
        self.gender = gender

def compareStudents(student1, student2):
    equalQualities = 0
    if student1.sport == student2.sport:
        equalQualities += 1
    if student1.music == student2.music:
        equalQualities += 1
    if student1.dancing == student2.dancing:
        equalQualities += 1
    if student1.instrument == student2.instrument:
        equalQualities += 1
    if student1.club == student2.club:
        equalQualities += 1
    if student1.hobby == student2.hobby:
        equalQualities += 1
    return equalQualities >= 2

def generateTeams(students):
    random.shuffle(students)
    teams = []
    while len(students) >= MIN_GROUP_SIZE:
        group = [students.pop(0)]
        for i in range(len(students) - 1, -1, -1):
            if compareStudents(group[0], students[i]):
                group.append(students.pop(i))
            if len(group) >= MAX_GROUP_SIZE:
                break
        teams.append(group)
    return teams

def getStudentInfo(student_number):
    print(f"Ingresa la información del estudiante {student_number}:")
    name = input("Nombre: ")
    sport = input("Deporte favorito: ")
    music = input("Género de música favorito: ")
    dancing = input("Tipo de danza favorita: ")
    instrument = input("Instrumento que toca: ")
    club = input("Club favorito: ")
    hobby = input("Pasatiempo favorito: ")
    gender = input("Género (M/F): ")
    return Student(student_number, name, sport, music, dancing, instrument, club, hobby, gender)

# Generar población de estudiantes
students = []
for i in range(1, POPULATION_SIZE + 1):
    student = getStudentInfo(i)
    students.append(student)

# Generar equipos
teams = generateTeams(students)

# Imprimir equipos
for i, team in enumerate(teams):
    print(f"\nEquipo {i + 1}:")
    for student in team:
        print(f"ID: {student.id}, Nombre: {student.name}, Género: {student.gender}")
