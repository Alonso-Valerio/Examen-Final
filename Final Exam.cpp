#include <iostream>
#include <cstring>
using namespace std;

const int MAX_EMPLEADOS = 10;
const int MAX_PROYECTOS = 10;
const int MAX_ASIGNACIONES = 20;

// Validaciones globales
char nombresProyectosRegistrados[MAX_PROYECTOS][50];
int totalNombresRegistrados = 0;

char correosRegistrados[MAX_EMPLEADOS][50];
int totalCorreosRegistrados = 0;

class Empleado {
private:
    int carnet;
    char nombre[50];
    char nacimiento[11];
    char categoria[15];
    double salario;
    char direccion[50];
    char telefono[15];
    char correo[50];

public:
    void crear() {
        cout << "Carnet: "; cin >> carnet;
        cout << "Nombre: "; cin.ignore(); cin.getline(nombre, 50);
        cout << "Nacimiento (dd/mm/aaaa): "; cin.getline(nacimiento, 11);
        cout << "Categoria (Administrador/Operario/Peon): "; cin.getline(categoria, 15);
        cout << "Salario: "; cin >> salario;
        cin.ignore();
        cout << "Direccion: "; cin.getline(direccion, 50);
        cout << "Telefono: "; cin.getline(telefono, 15);
        cout << "Correo: "; cin.getline(correo, 50);

        // Validar correo unico
        for (int i = 0; i < totalCorreosRegistrados; i++) {
            if (strcmp(correo, correosRegistrados[i]) == 0) {
                cout << "Correo ya registrado. Empleado no agregado.\n\n";
                nombre[0] = '\0'; // Marcar como invalido
                return;
            }
        }

        // Guardar correo en lista de correos usados
        strcpy(correosRegistrados[totalCorreosRegistrados], correo);
        totalCorreosRegistrados++;
    }

    void mostrar() {
        cout << "Carnet: " << carnet << "\nNombre: " << nombre << "\nNacimiento: " << nacimiento
             << "\nCategoria: " << categoria << "\nSalario: " << salario << "\nDireccion: " << direccion
             << "\nTelefono: " << telefono << "\nCorreo: " << correo << "\n\n";
    }

    int getCarnet() {
        return carnet;
    }

    char* getNombre() {
        return nombre;
    }

    char* getCorreo() {
        return correo;
    }
};

class Proyecto {
private:
    int codigo;
    char nombre[50];
    char fechaInicio[11];
    char fechaFin[11];

public:
    void crear() {
        cout << "Codigo: "; cin >> codigo;
        cin.ignore();
        cout << "Nombre: "; cin.getline(nombre, 50);

        // Validar nombre unico
        for (int i = 0; i < totalNombresRegistrados; i++) {
            if (strcmp(nombre, nombresProyectosRegistrados[i]) == 0) {
                cout << "Nombre ya registrado. Proyecto no agregado.\n\n";
                nombre[0] = '\0'; // Marcar como invalido
                return;
            }
        }

        // Guardar nombre en lista de nombres usados
        strcpy(nombresProyectosRegistrados[totalNombresRegistrados], nombre);
        totalNombresRegistrados++;

        cout << "Fecha inicio (dd/mm/aaaa): "; cin.getline(fechaInicio, 11);
        cout << "Fecha fin (dd/mm/aaaa): "; cin.getline(fechaFin, 11);
    }

    void mostrar() {
        cout << "Codigo: " << codigo << "\nNombre: " << nombre << "\nInicio: " << fechaInicio
             << "\nFinalizacion: " << fechaFin << "\n\n";
    }

    int getCodigo() {
        return codigo;
    }

    char* getNombre() {
        return nombre;
    }
};

class Asignacion {
private:
    int carnetEmpleado;
    int codigoProyecto;
    char fechaAsignacion[11];

public:
    void crear(int carnet, int codigo) {
        carnetEmpleado = carnet;
        codigoProyecto = codigo;
        strcpy(fechaAsignacion, "20/08/2025"); 
    }

    int getCarnet() {
        return carnetEmpleado;
    }

    int getCodigo() {
        return codigoProyecto;
    }

    char* getFecha() {
        return fechaAsignacion;
    }
};

class Gestor {
private:
    Empleado empleados[MAX_EMPLEADOS];
    Proyecto proyectos[MAX_PROYECTOS];
    Asignacion asignaciones[MAX_ASIGNACIONES];
    int totalEmpleados = 0;
    int totalProyectos = 0;
    int totalAsignaciones = 0;

public:
    void agregarEmpleado() {
        if (totalEmpleados < MAX_EMPLEADOS) {
            empleados[totalEmpleados].crear();
            if (strlen(empleados[totalEmpleados].getNombre()) > 0) {
                totalEmpleados++;
                cout << "Empleado agregado.\n\n";
            }
        }
    }

    void agregarProyecto() {
        if (totalProyectos < MAX_PROYECTOS) {
            proyectos[totalProyectos].crear();
            if (strlen(proyectos[totalProyectos].getNombre()) > 0) {
                totalProyectos++;
                cout << "Proyecto agregado.\n\n";
            }
        }
    }

    void asignarEmpleadoAProyecto() {
        if (totalAsignaciones < MAX_ASIGNACIONES) {
            int carnet, codigo;
            cout << "Carnet del empleado: "; cin >> carnet;
            cout << "Codigo del proyecto: "; cin >> codigo;

            for (int i = 0; i < totalAsignaciones; i++) {
                if (asignaciones[i].getCarnet() == carnet && asignaciones[i].getCodigo() == codigo) {
                    cout << "Ya esta asignado.\n\n";
                    return;
                }
            }

            asignaciones[totalAsignaciones].crear(carnet, codigo);
            totalAsignaciones++;
            cout << "Asignacion registrada.\n\n";
        }
    }

    void listarEmpleadosPorProyecto() {
        int codigo;
        cout << "Codigo del proyecto: "; cin >> codigo;

        for (int i = 0; i < totalAsignaciones; i++) {
            if (asignaciones[i].getCodigo() == codigo) {
                for (int j = 0; j < totalEmpleados; j++) {
                    if (empleados[j].getCarnet() == asignaciones[i].getCarnet()) {
                        empleados[j].mostrar();
                    }
                }
            }
        }
    }

    void listarProyectosPorEmpleado() {
        int carnet;
        cout << "Carnet del empleado: "; cin >> carnet;

        for (int i = 0; i < totalAsignaciones; i++) {
            if (asignaciones[i].getCarnet() == carnet) {
                for (int j = 0; j < totalProyectos; j++) {
                    if (proyectos[j].getCodigo() == asignaciones[i].getCodigo()) {
                        proyectos[j].mostrar();
                    }
                }
            }
        }
    }
};

int main() {
    Gestor gestor;
    int opcion;

    do {
        cout << "1. Agregar empleado\n";
        cout << "2. Agregar proyecto\n";
        cout << "3. Asignar empleado a proyecto\n";
        cout << "4. Listar empleados por proyecto\n";
        cout << "5. Listar proyectos por empleado\n";
        cout << "0. Salir\n";
        cout << "Opcion: "; cin >> opcion;

        switch (opcion) {
            case 1: gestor.agregarEmpleado(); break;
            case 2: gestor.agregarProyecto(); break;
            case 3: gestor.asignarEmpleadoAProyecto(); break;
            case 4: gestor.listarEmpleadosPorProyecto(); break;
            case 5: gestor.listarProyectosPorEmpleado(); break;
        }
    } while (opcion != 0);

    return 0;
}


